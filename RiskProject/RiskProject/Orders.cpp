#include "Orders.h"
#include <iostream>
#include<string>
#include <list>
#include <string>
using namespace std;


//-----------------------ORDERS FUNCTION IMPLEMENTATION----------------------//

Order::Order() {
	//cout << "Empty order constructor called. \n";
	orderName = "";
	orderEffect = "";
	orderExecutionFlag = false;
	
}

Order::Order(string x) {
	//cout << "Order constructor with string called. \n";
	orderName = x;
	orderEffect = "";
	orderExecutionFlag = false;
	
}

//copy constructor
Order::Order(const Order& originalOrder) {
	//cout << "Order Copy constructor called. \n";
	this->orderName = originalOrder.orderName;
	this->orderExecutionFlag = originalOrder.orderExecutionFlag;
	this->orderEffect = originalOrder.orderEffect;
	
}

//assignment operator
Order& Order::operator= (const Order& order) {
	//cout << "Order Assignment operator called. \n";
	orderName = order.orderName;
	orderEffect = order.orderEffect;
	orderExecutionFlag = order.orderExecutionFlag;
	return *this;
}

bool Order::validate(string order) {return false;}

void Order::execute() {}

string Order::getOrderName() { return orderName; }

void Order::setOrderName(string name) { this->orderName = name; }

string Order::getOrderEffect() { return orderEffect; }

void Order::setOrderEffect(string orderEffect){	this->orderEffect = orderEffect;}

bool Order::getOrderExecutionFlag() { return orderExecutionFlag; }

void Order::setOrderExecutionFlag(bool flag) {orderExecutionFlag = flag;}

ostream& operator <<(ostream& input, Order order) {
	input << order.getOrderName() << endl;
	input << order.getOrderEffect() << endl;
	/*
	if (order.getOrderExecutionFlag())
	{
		input << "This order has been executed. \n";
		input << order.getOrderEffect() << endl;
	}
	else
		input << "This order has not been executed.\n";
	*/
	return input;

}

string Order::stringToLog() {
	return "unspecified order";
}

//destructor
Order::~Order() {
	//cout <<"Order will now be destroyed. \n";
}


//-----------------------DEPLOY FUNCTION IMPLEMENTATION----------------------//

Deploy::Deploy() {/* cout << "Empty deploy constructor called. \n";*/ }

Deploy::Deploy(string name) {
	//cout << "Deploy constructor with string called. \n";
	orderName = name;
	orderEffect = "Move a certain number of army units from the current player’s reinforcement pool to one of the current player’s territories.";
}

Deploy::Deploy(int au, Territory* t, Player* p) {
	orderName = "deploy";
	orderEffect = "Move a certain number of army units from the current player’s reinforcement pool to one of the current player’s territories.";
	armyUnits = au;
	territory = t;
	player = p;
}

Deploy::Deploy(const Deploy& d): Order(d) {
	//cout << "deploy copy constructor called. \n";
	this->orderName = d.orderName;
	this->orderEffect = d.orderEffect;
	this->orderExecutionFlag = d.orderExecutionFlag;
}

Deploy& Deploy:: operator= (const Deploy& d) {
	//cout << "deploy assignment operator called. \n";
	orderName = d.orderName;
	orderEffect = d.orderEffect;
	orderExecutionFlag = d.orderExecutionFlag;

	return *this;
}

bool Deploy::validate(Territory* territoryBeingValidated, Player* p){	
	//looping through player's list of defendable territories
	//if territory exists in their defend list, then return true
	vector<Territory*> defendList = p->availableTerritoriesToDefend();
	for (Territory* territory : defendList) {
		if (territory->getTName() == territoryBeingValidated->getTName())
		{
			return true;
		}
	}

	return false;
}

void Deploy::execute() {
	if (validate(this->territory, this->player)) {
		this->setOrderExecutionFlag(true);
		//add army units to territory selected

		//get territory's original army size	
		int territoryOriginalArmySize = this->territory->getArmyAmount();
		
		//set territory's army units 
		this->territory->setArmyAmount(this->armyUnits + territoryOriginalArmySize);

		Notify(this);
	}
		
}


//DeployOrder logging function.
string Deploy::stringToLog() {
	return "Order Executed: Deploy\nDeploy: " + getOrderEffect();
}

Deploy::~Deploy() {
	//cout << this->getOrderName() << " in derived class will now be destroyed. \n";
}




//-----------------------ADVANCE FUNCTION IMPLEMENTATION----------------------//
Advance::Advance() {}

Advance::Advance(string name) {
	//cout << "Advance constructor with string called. \n";
	orderName = name;
	orderEffect = "Move a certain number of army units from one territory (source territory) to another territory (target territory)";
}

Advance::Advance(const Advance& a): Order(a) {
	//cout << "Advance copy constructor called. \n";
	this->orderName = a.orderName;
	this->orderEffect = a.orderEffect;
	this->orderExecutionFlag = a.orderExecutionFlag;

}

Advance::Advance(Player* p, Territory* src, Territory* dest, int armyNum) {
	orderName = "advance";
	orderEffect = "Move a certain number of army units from one territory (source territory) to another territory (target territory)";
	player = p;
	srcTerritory = src;
	dstnTerritory = dest;
	armyUnits = armyNum;
}

Advance& Advance:: operator= (const Advance& a) {
	//cout << "Advance assignment operator called. \n";
	orderName = a.orderName;
	orderEffect = a.orderEffect;
	orderExecutionFlag = a.orderExecutionFlag;

	return *this;

}

Advance::~Advance() {
	//cout << this->getOrderName() << " in derived class will now be destroyed. \n";
}

bool Advance::validate(Player* p, Territory* src, Territory* dest, int armyNum) {
	
	for (Territory* playerTerritories : p->getTerritory()) {
		//check if source territory belongs to player
		if (playerTerritories->getTName() == src->getTName()) {

			//check if dstn territory is adj to src territory
			for(Territory* adjTerritories: src->getAdjTerritories())
				if (adjTerritories->getTName() == dest->getTName())
				{
					//if (dest->getOwner() == p) //put in execute code
					//check that army amount isn't more than whats available
					if(armyNum < src->getArmyAmount())
						return true;
						
				}
		}
	}

	return false;
}

void Advance::execute() {
	if (validate(this->player, this->srcTerritory, this->dstnTerritory, armyUnits))
	{
		int originalsrcTerritoryArmyNum = srcTerritory->getArmyAmount();
		int originalDestTerritoryArmyNum = dstnTerritory->getArmyAmount();
		int finalSrcTerritoryArmyNum = 0;
		int finalDestTerritoryArmyNum = 0;

		this->setOrderExecutionFlag(true);

		//if src and destination territory both belong to player, then just move the army units
		if (dstnTerritory->getOwner() == player)
		{
			finalSrcTerritoryArmyNum = originalsrcTerritoryArmyNum - armyUnits;
			finalDestTerritoryArmyNum = originalDestTerritoryArmyNum + armyUnits;
			srcTerritory->setArmyAmount(finalSrcTerritoryArmyNum);
			dstnTerritory->setArmyAmount(finalDestTerritoryArmyNum);
		}
		else //src and destination territory belong to different players
		{
			//simulate an attack
			Player* enemyPlayer = dstnTerritory->getOwner();
			//ASK FOR HELP HERE
		}

		Notify(this);
	}
}

string Advance::stringToLog() {
	return "Order Advance: Advance\nAdvance: " + getOrderEffect();
}

//-----------------------BOMB FUNCTION IMPLEMENTATION----------------------//

Bomb::Bomb() {}

Bomb::Bomb(string name) {
	//cout << "Bomb constructor with string called. \n";
	orderName = name;
	orderEffect = "Destroy half of the army units located on an opponent’s territory that is adjacent to one of the current player’s territories.";
}

Bomb::Bomb(const Bomb& b):Order(b) {
	//cout << "Bomb copy constructor called. \n";
	this->orderName = b.orderName;
	this->orderEffect = b.orderEffect;
	this->orderExecutionFlag = b.orderExecutionFlag;

}

Bomb::Bomb(Player* p, Territory* t)
{
	orderName = "bomb";
	orderEffect = "Destroy half of the army units located on an opponent’s territory that is adjacent to one of the current player’s territories.";
	player = p;
	territory = t;
}
Bomb& Bomb::operator= (const Bomb& b) {
	//cout << "Bomb assignment operator called. \n";
	orderName = b.orderName;
	orderEffect = b.orderEffect;
	orderExecutionFlag = b.orderExecutionFlag;
	return *this;
}

Bomb::~Bomb() {
	//cout << this->getOrderName() << " in derived class will now be destroyed. \n";
}

bool Bomb::validate(Player* p, Territory* territoryToBeBombed) {
	
	//check if territory's owner isn't the one that issued it
	if (territoryToBeBombed->getOwner() != p) {
		for (Territory* territoryOfPlayer : p->getTerritory())
		{
			for (Territory* territoryAdj : territoryOfPlayer->getAdjTerritories())
			{
				if (territoryToBeBombed = territoryAdj)
					return true;
			}
		}
	}

	return false;
}

void Bomb::execute() {
	if (validate(this->player, this->territory))
	{
		this->setOrderExecutionFlag(true);
		int armyAmount = territory->getArmyAmount();
		territory->setArmyAmount(armyAmount / 2);
		Notify(this);
	}
}

//BombOrder logging function.
string Bomb::stringToLog() {
	return "Order Executed: Bomb\nBomb: " + getOrderEffect();
}

//-----------------------BlOCKADE FUNCTION IMPLEMENTATION----------------------//

Blockade::Blockade() {}

Blockade::Blockade(string name) {
	//cout << "Blockade constructor with string called. \n";
	orderName = name;
	orderEffect = "Triple the number of army units on one of the current player’s territories and make it a neutral	territory";
}

Blockade::Blockade(const Blockade& b): Order(b) {
	//cout << "Blockade copy constructor called. \n";
	this->orderName = b.orderName;
	this->orderEffect = b.orderEffect;
	this->orderExecutionFlag = b.orderExecutionFlag;

}

Blockade::Blockade(Territory* t, Player* p, Player* np)
{
	orderName = "blockade";
	orderEffect = "Triple the number of army units on one of the current player’s territories and make it a neutral	territory";
	territory = t;
	player = p;	
	neutralPlayer = np;

}

Blockade& Blockade:: operator= (const Blockade& b) {
	//cout << "Blockade assignment operator called. \n";
	orderName = b.orderName;
	orderEffect = b.orderEffect;
	orderExecutionFlag = b.orderExecutionFlag;
	return *this;
}

Blockade::~Blockade() {
	//cout << this->getOrderName() << " in derived class will now be destroyed. \n";
}

bool Blockade::validate(Territory* t, Player* p) {

	//if territory's owner belongs to the one that issued the blockade order
	if (t->getOwner() == p)
		return true;

	return false;
}

void Blockade::execute() {
	if (validate(this->territory, this->player))
	{
		this->setOrderExecutionFlag(true);
		int originalArmyAmount = territory->getArmyAmount();
		int finalArmyAmount = originalArmyAmount * 2;
		territory->setOwner(neutralPlayer);
		territory->setArmyAmount(finalArmyAmount);
		Notify(this);
	}
		
}

//BlockadeOrder logging function.
string Blockade::stringToLog() {
	return "Order Executed: Blockade\nBlockade: " + getOrderEffect();
}


//-----------------------AIRLIFT FUNCTION IMPLEMENTATION----------------------//

Airlift::Airlift() {}

Airlift::Airlift(string name) {
	//cout << "Airlift constructor with string called. \n";
	orderName = name;
	orderEffect = "Advance a certain number of army units from one of the current player’s territories to any another yerritory ";
}

Airlift::Airlift(const Airlift& a) :Order(a) {
	//cout << "Airlift copy constructor called. \n";
	this->orderName = a.orderName;
	this->orderEffect = a.orderEffect;
	this->orderExecutionFlag = a.orderExecutionFlag;

}

Airlift::Airlift(Player* p, Territory* src, Territory* dstn, int armyNum)
{
	orderName = "airlift";
	orderEffect = "Advance a certain number of army units from one of the current player’s territories to any another yerritory ";
	player = p;
	srcTerritory = src;
	dstnTerritory = dstn;
	armyUnits = armyNum;
}

Airlift& Airlift:: operator= (const Airlift& a) {
	//cout << "Airlift assignment operator called. \n";
	orderName = a.orderName;
	orderEffect = a.orderEffect;
	orderExecutionFlag = a.orderExecutionFlag;
	return *this;
}
Airlift::~Airlift() {
	//cout << this->getOrderName() << " in derived class will now be destroyed. \n";
}

bool Airlift::validate(Player* p, Territory* src, Territory* dstn, int armyNum) {
	
	if (src->getOwner() == p && dstn->getOwner() == p) //to debug to make sure it works
		return true;

	return false;
}


void Airlift::execute() {
	if (validate(this->player, this->srcTerritory, this->dstnTerritory, armyUnits))
	{

		this->setOrderExecutionFlag(true);

		int originalsrcTerritoryArmyNum = srcTerritory->getArmyAmount();
		int originalDestTerritoryArmyNum = dstnTerritory->getArmyAmount();
		int finalSrcTerritoryArmyNum = 0;
		int finalDestTerritoryArmyNum = 0;

		finalSrcTerritoryArmyNum = originalsrcTerritoryArmyNum - armyUnits;
		finalDestTerritoryArmyNum = originalDestTerritoryArmyNum + armyUnits;
		srcTerritory->setArmyAmount(finalSrcTerritoryArmyNum);
		dstnTerritory->setArmyAmount(finalDestTerritoryArmyNum);
		
		Notify(this);
	}
}


//AirliftOrder logging function.
string Airlift::stringToLog() {
	return "Order Executed: Airlift\nAirlift: " + getOrderEffect();
}

//-----------------------NEGOTIATE FUNCTION IMPLEMENTATION----------------------//

Negotiate::Negotiate() {}

Negotiate::Negotiate(string name) {
	//cout << "Negotiate constructor with string called. \n";
	orderName = name;
	orderEffect = "Prevent attacks between the current player and the player targeted by the negotiate order until the end of the turn";
}

Negotiate::Negotiate(const Negotiate& n):Order(n) {
	//cout << "Negotiate copy constructor called. \n";
	this->orderName = n.orderName;
	this->orderEffect = n.orderEffect;
	this->orderExecutionFlag = n.orderExecutionFlag;

}

Negotiate::Negotiate(Player* p1, Player* enemy)
{
	orderName = "negotiate";
	orderEffect = "Prevent attacks between the current player and the player targeted by the negotiate order until the end of the turn";
	player = p1;
	enemyPlayer = enemy;

}

Negotiate& Negotiate::operator= (const Negotiate& n) {
	//cout << "Negotiate assignment operator called. \n";
	orderName = n.orderName;
	orderEffect = n.orderEffect;
	orderExecutionFlag = n.orderExecutionFlag;
	return *this;

}
Negotiate::~Negotiate() {
	//cout << this->getOrderName() << " in derived class will now be destroyed. \n";
}

bool Negotiate::validate(Player* p1, Player* enemy) {
	//check the chosen player is an adversary
	if (p1 != enemy)
		return true;
	return false;
}

void Negotiate::execute() {
	if (validate(this->player, this->enemyPlayer))

	{
		this->setOrderExecutionFlag(true);
		Notify(this);
	}
}


//NegotiateOrder logging function.
string Negotiate::stringToLog() {
	return "Order Executed: Negotiate\nNegotiate: " + getOrderEffect();
}

//----------------------ORDERSLIST FUNCTION IMPLEMENTATION----------------------//

OrdersList::OrdersList() {
	//cout << "OrdersList constructor called. \n";

}

OrdersList::OrdersList(const OrdersList& originalOrdersList) {
	//cout << "OrdersList copy constructor called. \n";
	for (auto x : originalOrdersList.ordersList) {
		if (x->getOrderName().compare("deploy") == 0)
		{
			Deploy* temp = new Deploy("deploy");
			addOrder(temp);
			
		}
		else if (x->getOrderName().compare("advance") == 0)
		{
			Advance* temp = new Advance("advance");
			addOrder(temp);
		}
		else if (x->getOrderName().compare("bomb") == 0)
		{
			Bomb* temp = new Bomb("bomb");
			addOrder(temp);
		}			
		else if (x->getOrderName().compare("blockade") == 0)
		{
			Blockade* temp = new Blockade("blockade");
			addOrder(temp);
		}
		else if (x->getOrderName().compare("airlift") == 0)
		{
			Airlift* temp = new Airlift("airlift");
			addOrder(temp);
		}
		else if (x->getOrderName().compare("negotiate") == 0)
		{
			Blockade* temp = new Blockade("negotiate");
			addOrder(temp);
		}		
	}
}

//assignment operator
OrdersList& OrdersList:: operator= (const OrdersList& ol) {
	//cout << "OrdersList assignment operator called. \n";
	for (auto x : ol.ordersList) {
		if (x->getOrderName().compare("deploy") == 0)
		{
			Deploy* temp = new Deploy("deploy");
			addOrder(temp);
		}
		else if (x->getOrderName().compare("advance") == 0)
		{
			Advance* temp = new Advance("advance");
			addOrder(temp);
		}
		else if (x->getOrderName().compare("bomb") == 0)
		{
			Bomb* temp = new Bomb("bomb");
			addOrder(temp);
		}
		else if (x->getOrderName().compare("blockade") == 0)
		{
			Blockade* temp = new Blockade("blockade");
			addOrder(temp);
		}
		else if (x->getOrderName().compare("airlift") == 0)
		{
			Airlift* temp = new Airlift("airlift");
			addOrder(temp);
		}
		else if (x->getOrderName().compare("negotiate") == 0)
		{
			Blockade* temp = new Blockade("negotiate");
			addOrder(temp);
		}
	}
	return *this;
}

list<Order*> OrdersList::getOrdersList()
{
	return ordersList;
}
void OrdersList::addOrder(Order* orderToBeAdded)
{
	ordersList.push_back(orderToBeAdded);
	stringToBeLogged = "Order Added: " + orderToBeAdded->getOrderName();
	Notify(this);
}


//OrdersList logging function.
string OrdersList::stringToLog() {
	return stringToBeLogged;
}

void OrdersList::move(int sourceIndex, int destinationIndex) {
	//sourceIndex - order to be moved from
	//destinationIndex - index order is to be moved to
	list<Order*> tempList;
	list<Order*>::iterator iterator2 = ordersList.begin();
	advance(iterator2, sourceIndex - 1);
	tempList.push_back(*iterator2);
	list<Order*>::iterator iterator1 = ordersList.begin();
	advance(iterator1, destinationIndex - 1);
	ordersList.splice(iterator1, tempList);
	ordersList.erase(iterator2);
}

void OrdersList::remove(int indexOfOrder) {
	list<Order*>::iterator iterator = ordersList.begin();
	advance(iterator, indexOfOrder - 1);
	iterator = ordersList.erase(iterator);
}

//stream insertion
ostream& operator << (ostream& out, OrdersList ordersList) {
	list<Order*> orders = ordersList.getOrdersList();
	for (auto x : orders) {
		out << *x << endl;
	}
	return out;
}

void OrdersList::showOrdersList() {
	int index = 1;
	cout << "show orders list: \n";
	for (auto x : ordersList)
	{
		cout << index << ": " << x->getOrderName() << endl;
		index++;
	}
}

void OrdersList::clearList() {
	ordersList.clear();
}

//destructor
OrdersList::~OrdersList() {
	//cout << "OrdersList will now be destroyed \n";

	//release memory
	ordersList.clear();
}