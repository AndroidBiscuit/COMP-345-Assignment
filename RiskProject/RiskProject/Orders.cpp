#include "Orders.h"
#include <iostream>
#include<string>
#include <list>
#include <string>
using namespace std;


//-----------------------ORDERS FUNCTION IMPLEMENTATION----------------------//

Order::Order() {
	orderName = "";
	orderEffect = "";
	orderExecutionFlag = false;
}

Order::Order(string x) {
	orderName = x;
	orderEffect = "";
	orderExecutionFlag = false;
}

//copy constructor
Order::Order(const Order& originalOrder) {
	this->orderName = originalOrder.orderName;
	this->orderExecutionFlag = originalOrder.orderExecutionFlag;
	this->orderEffect = originalOrder.orderEffect;
}

//assignment operator
Order& Order::operator= (const Order& order) {
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
	input << "Order is: " << order.getOrderName() << endl;
	if (order.getOrderExecutionFlag())
	{
		input << "This order has been executed. \n";
		input << order.getOrderEffect() << endl;
	}
	else
		input << "This order has not been executed. \n";
	
	return input;

}

//destructor
Order::~Order() {
	cout << this->getOrderName() << " will now be destroyed. \n";
}


//-----------------------DEPLOY FUNCTION IMPLEMENTATION----------------------//

Deploy::Deploy() {}

Deploy::Deploy(string name) {
	orderName = name;
	orderEffect = "Move a certain number of army units from the current player’s reinforcement pool to one of the current player’s territories.";
}

Deploy::Deploy(const Deploy& d): Order(d) {
	this->orderName = d.orderName;
	this->orderEffect = d.orderEffect;
	this->orderExecutionFlag = d.orderExecutionFlag;
}

Deploy& Deploy:: operator= (const Deploy& d) {
	orderName = d.orderName;
	orderEffect = d.orderEffect;
	orderExecutionFlag = d.orderExecutionFlag;

	return *this;
}

bool Deploy::validate(string order){
	//for now: if string matches with the name of order, then its validated
	string deploy = "deploy";
	if (deploy.compare(order) == 0)
		return true;

	return false;
}

void Deploy::execute() {
	if (validate(getOrderName()))
		this->setOrderExecutionFlag(true);
}

Deploy::~Deploy() {
	cout << this->getOrderName() << " will now be destroyed!!!!AHHHH \n";
}


//-----------------------ADVANCE FUNCTION IMPLEMENTATION----------------------//
Advance::Advance() {}

Advance::Advance(string name) {
	orderName = name;
	orderEffect = "Move a certain number of army units from one territory (source territory) to another territory (target territory)";
}

bool Advance::validate(string order) {
	//for now: if string matches with the name of order, then its validated
	string deploy = "advance";
	if (deploy.compare(order) == 0)
		return true;

	return false;
}

void Advance::execute() {
	if (validate(getOrderName()))
		this->setOrderExecutionFlag(true);
}

//-----------------------BOMB FUNCTION IMPLEMENTATION----------------------//

Bomb::Bomb() {}

Bomb::Bomb(string name) {
	orderName = name;
	orderEffect = "Destroy half of the army units located on an opponent’s territory that is adjacent to one of the current player’s territories.";
}

bool Bomb::validate(string order) {
	//for now: if string matches with the name of order, then its validated
	string deploy = "bomb";
	if (deploy.compare(order) == 0)
		return true;

	return false;
}

void Bomb::execute() {
	if (validate(getOrderName()))
		this->setOrderExecutionFlag(true);
}

//-----------------------BlOCKADE FUNCTION IMPLEMENTATION----------------------//

Blockade::Blockade() {}

Blockade::Blockade(string name) {
	orderName = name;
	orderEffect = "Triple the number of army units on one of the current player’s territories and make it a neutral	territory";
}

bool Blockade::validate(string order) {
	//for now: if string matches with the name of order, then its validated
	string deploy = "blockade";
	if (deploy.compare(order) == 0)
		return true;

	return false;
}

void Blockade::execute() {
	if (validate(getOrderName()))
		this->setOrderExecutionFlag(true);
}

//-----------------------AIRLIFT FUNCTION IMPLEMENTATION----------------------//

Airlift::Airlift() {}

Airlift::Airlift(string name) {
	orderName = name;
	orderEffect = "Advance a certain number of army units from one of the current player’s territories to any another yerritory ";
}

bool Airlift::validate(string order) {
	//for now: if string matches with the name of order, then its validated
	string deploy = "airlift";
	if (deploy.compare(order) == 0)
		return true;

	return false;
}


void Airlift::execute() {
	if (validate(getOrderName()))
		this->setOrderExecutionFlag(true);
}

//-----------------------NEGOTIATE FUNCTION IMPLEMENTATION----------------------//

Negotiate::Negotiate() {}

Negotiate::Negotiate(string name) {
	orderName = name;
	orderEffect = "Prevent attacks between the current player and the player targeted by the negotiate order until the end of the turn";
}

bool Negotiate::validate(string order) {
	//for now: if string matches with the name of order, then its validated
	string deploy = "negotiate";
	if (deploy.compare(order) == 0)
		return true;

	return false;
}

void Negotiate::execute() {
	if (validate(getOrderName()))
		this->setOrderExecutionFlag(true);
}



//----------------------ORDERSLIST FUNCTION IMPLEMENTATION----------------------//

OrdersList::OrdersList() {

}

OrdersList::OrdersList(const OrdersList& originalOrdersList) {

}

//assignment operator
OrdersList& OrdersList:: operator= (const OrdersList& ol) {

	return *this;
}

void OrdersList::addOrder(Order* orderToBeAdded)
{
	ordersList.push_back(orderToBeAdded);
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

void OrdersList::showOrdersList() {
	int index = 1;
	for (auto x : ordersList)
	{
		cout << index << ": " << x->getOrderName() << endl;
		index++;
	}
}

//destructor
OrdersList::~OrdersList() {
	cout << "OrdersList will now be destroyed \n";

	//release memory
	ordersList.clear();
}