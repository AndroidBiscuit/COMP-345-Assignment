#include "Player.h"
#include <string>
using std::string;
using std::endl;
using std::cout;
using std::cin;
using std::remove;


class Cards;
class Order;
class OrderList;
class Territroy;

//Static variable initialer:
int Player::createdPlayers = 0;

//constructors:
Player::Player() {
	cout << "Player with ID-" << createdPlayers << " was created." << endl;
	createdPlayers++;
	name = "default";
	armiesAmount = 0;
	playerID = createdPlayers;
	ordersList = new OrdersList();
	hand = new Hand();
	intelligent = false;
	ordersToIssueFlag = true;
}

Player::Player(const Player& p) {
	cout << "Player with ID-:" << createdPlayers << " was created." << endl;
	createdPlayers++;
	this->name = p.name;
	this->armiesAmount = p.armiesAmount;
	this->playerID = p.playerID;
	this->ordersToIssueFlag = p.ordersToIssueFlag;
	for (auto p : p.territory) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);

	}
	for (auto p : p.toAttack) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);
	}
	for (auto p : p.toDefend) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);
	}
	hand = new Hand(*p.hand);

	ordersList = new OrdersList(*p.ordersList);	
}

//Assignment operators:
Player& Player::operator=(const Player& p) {
	cout << "Player with ID-:" << createdPlayers << " was created." << endl;
	name = p.name;
	playerID = p.playerID;
	ordersToIssueFlag = p.ordersToIssueFlag;
	for (Territory* p : p.territory) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);
	}
	for (auto p : p.toAttack) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);
	}
	for (auto p : p.toDefend) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);
	}
	hand = new Hand(*p.hand);

	ordersList = new OrdersList(*p.ordersList);

	return *this;
}

//Stream insertions:
istream& operator>>(istream& in, Player& p)
{
	in >> p.name;
	return in;
}

ostream& operator<< (ostream& out, const Player& p) {
	out << "Player Name: " << p.name << endl;
	out << "ID: " << p.playerID << endl;
	out << "Armies Amount: " << p.armiesAmount << endl;
	out << "Owned Territories: " << endl;
	for (int i = 0; i < p.territory.size(); ++i) {
		out << "<" << p.territory.at(i)->getTName() << ">";
	}
	out << endl;
	out << "Handed Cards: " <<endl;
	out << *(p.hand);
	out << endl;
	out << "Orders issued: " << endl;
	out << *(p.ordersList);
	return out;
}

//destructor
Player::~Player() {
	cout << "Player " << this->getName() << " will now be destroyed." << endl;
	if(ordersList != nullptr) {
		delete ordersList; 
	}
	if (hand != nullptr) {
		delete hand; 
	}
	//release memory
	territory.clear();
	
}

//Mutators:
void Player::setName(string s) {
	this->name = s;
}

void Player::setPlayerID(int playerID){
	this->playerID = playerID;
}

void Player::setArmiesAmount(int armies){
	this->armiesAmount = armies;
}
void Player::setTerritory(vector<Territory*> const& other) {
	territory = other;
}

void Player::setOrdersList(OrdersList* ordersList){
	this->ordersList = ordersList;
}

void Player::setConquered(bool result) {
	this->conquered = result;
}

void Player::setOrdersToIssueFlag(bool ordersLeftToIssue) {
	this->ordersToIssueFlag = ordersLeftToIssue;
}

//Acessors:
string Player::getName() {
	return this->name;
}

int Player::getPlayerID() {
	return playerID;
}

int Player::getArmiesAmount(void) {
	return armiesAmount;
}

vector<Territory*> Player::getTerritory() {
	return territory;
}

Hand* Player::getHand() {
	return hand;
}

bool Player::getOrdersToIssueFlag() {
	return ordersToIssueFlag;
}

//vector<Card*> Player::getCards(void) {
//	return cards;
//}

OrdersList* Player::getOrders(void) {
	return ordersList;
}

void Player::addTerritory(Territory* ter) {
	ter->setOwner(this);
	territory.push_back(ter);
}

//void Player::addCard(Card* card) {
//	hand->addCard(card);
//}

void Player::removeTerritory(Territory* toRemove) {
	territory.erase(std::remove(territory.begin(), territory.end(), toRemove), territory.end());
}

vector<Player*> Player::getCanNotAttack() {
	return cannotAttack;
}

bool Player::getConquered() {
	return conquered;
}

//Method:

void Player::printOrderList(void) {
	cout << "----------------------------------" << endl;
	cout << "The following commands are available: " << endl;
	cout << "DEPLOY: place some armies on one of the current player's territories." << endl;
	cout << "ADVANCE: move some armies from one of the current player's territories(source) to an adjacent territory." << endl;
	cout << "BOMB: destroy half of the armies located on an opponent's territory that is adjacent to one of the current player's territories." << endl;
	cout << "BLOCKADE: triple the number of armies on a target territory and make it a neutral territory." << endl;
	cout << "AIRLIFT: advance some armies from one of the current player's territories to any another territory." << endl;
	cout << "NEGOTIATE: prevent attacks between the current playerand another player until the end of the turn." << endl;
	cout << "----------------------------------" << endl;
}

void Player::discoverOrderType(string x, Order* issued) {
	string options[] = { "deploy", "advance", "bomb", "blockade", "airlift", "negotiate" };

	for (int i = 0; i < 6; i++)
	{
		if (options[i].compare(x) == 0) {
			issued->setOrderName(options[i]);
			return;
		}
	}

	issued->setOrderName("UNKOWN ORDER");
	return;
}

//Returns territories not owned by the player
vector<Territory*> Player::availableTerritoriesToAttack()
{
	//Returns enemy territories player has access to through adjacent territories
	vector<Territory*> attackList;
	for (auto t: territory) {
		for (auto d : t->getAdjTerritories()) {
			if (!(find(attackList.begin(), attackList.end(), d) != attackList.end())) {
				if (d->getOwner() != this) {
					attackList.push_back(d);
				}
			}
		}
	}
	
	return attackList;
}

//Returns territories owned by the player
vector<Territory*> Player::availableTerritoriesToDefend()
{
	vector<Territory*> defendList;
	for (auto t : territory) {
		defendList.push_back(t);
	}

	return defendList;
}


void Player::issueOrder()
{
	vector<Territory*> attackList = availableTerritoriesToAttack();
	vector<Territory*> defendList = availableTerritoriesToDefend();
	string orderAnswer;
	char orderAnswer2 = 'x';
	string territoryAnswer;
	bool repeatAttackOrDefendLoop = false;
	bool repeatMoveArmyUnitsAroundLoop = false;
	int armyAmountAnswer;
	int newArmyAmount;

	//while player still wants to add territories to attack or defend, stay in loop	
	while (orderAnswer2 != 'y' && orderAnswer2 != 'n')
	{
		cout << "Would you like to attack/defend territories? (y/n) \n";
		cin >> orderAnswer2;

		if (orderAnswer2 == 'y')
			repeatAttackOrDefendLoop = true;
		else if (orderAnswer2 == 'n')
			repeatAttackOrDefendLoop = false;
		else
			cout << "That is not a valid command. \n";
	}
	

	while(repeatAttackOrDefendLoop) {


		while (orderAnswer != "attack" && orderAnswer != "defend")
		{
			cout << "Would you like to defend or attack? \n";
			cin >> orderAnswer;

			if (orderAnswer != "attack" && orderAnswer != "defend")
				cout << "That is not a valid command. \n";
		}
		

		if (orderAnswer.compare("attack") == 0)
		{
			cout << "Here are the available territories to attack: \n";
			for (Territory* territory : attackList) {
				cout << territory->getTName() << endl;
			}
			cin >> territoryAnswer;

			if (makeSureTerritoryAnswerExists(attackList, territoryAnswer)) {
				//add territory to attackList
				for (Territory* territory : attackList)
				{
					if (territory->getTName().compare(territoryAnswer) == 0)
						toAttack.push_back(territory);
				}
			}
			else
				cout << territoryAnswer << " is not a valid territory. Please choose again. \n";

			
			
		}
		else if (orderAnswer.compare("defend") == 0)
		{
			cout << "Here are the available territories to defend: \n";
			for (Territory* territory : defendList) {
				cout << territory->getTName() << endl;
			}
			cin >> territoryAnswer;

			if (makeSureTerritoryAnswerExists(defendList, territoryAnswer)) {
				//add territory to defendList
				for (Territory* territory : defendList)
				{
					if (territory->getTName().compare(territoryAnswer) == 0)
						toDefend.push_back(territory);
				}
			}
			else
				cout << territoryAnswer << " is not a valid territory. Please choose again. \n";

		}
		else {
			cout << "You entered an invalid command \n";
		}

		//resetting answer
		orderAnswer = "";
		orderAnswer2 = 'x';
		while (orderAnswer2 != 'y' && orderAnswer2 != 'n') 
		{
			cout << "Would you like to attack/defend more territories? (y/n) \n";
			cin >> orderAnswer2;

			if (orderAnswer2 == 'y')
				repeatAttackOrDefendLoop = true;
			else if (orderAnswer2 == 'n')
				repeatAttackOrDefendLoop = false;
			else
				cout << "That is not a valid command. \n";
		}

	};

	//while player still has army units, order must deploy them
	while (getArmiesAmount() != 0) {
		cout << "You have armies left in your reinforcement pool, to which territory would you like to deploy them to? \n";
		cout << "Here are the territories you can deploy them to: \n";
		for (Territory* territory : toDefend)
		{
			cout << territory->getTName() <<endl;
		}
		cin >> territoryAnswer;

		//making sure territory entered is a territory that exists in the player's defend list
		if (makeSureTerritoryAnswerExists(toDefend, territoryAnswer)) {

			
			cout << "How many army units would you like to deploy to " << territoryAnswer << " ?\n";
			cout << "You have " << getArmiesAmount() << " army units left. \n";
			cin >> armyAmountAnswer; 
			while (armyAmountAnswer > getArmiesAmount())
			{
				cout << "Army amount entered is more than available army amount. Please enter amount again. \n";
				cin >> armyAmountAnswer;
			}
			
			newArmyAmount = getArmiesAmount() - armyAmountAnswer; 
			setArmiesAmount(newArmyAmount); //sets player's remaining army unit

			//getting territory original army size
			int territoryOriginalArmySize;
			for (Territory* territory : toDefend) {
				if (territory->getTName().compare(territoryAnswer) == 0)
					territoryOriginalArmySize = territory->getArmyAmount();
			}

			//storing the newly assigned army units in territory's army amount attribute
			for (Territory* territory : defendList)
			{
				if (territory->getTName().compare(territoryAnswer) == 0)
					territory->setArmyAmount(armyAmountAnswer + territoryOriginalArmySize);
			}

			cout << armyAmountAnswer << " units of army has been deployed to " << territoryAnswer << endl;

		}
		else
			cout << territoryAnswer << " is not a valid territory. Please choose again. \n";
	};

	//while player still wants to move army units around territories, stay in loop
	string territorySource, territoryDestination;
	int armyUnitsToBeMoved, originalArmyAmount, finalArmyAmount;

	//reset answer
	orderAnswer2 = 'x';
	while (orderAnswer2 != 'y' && orderAnswer2 != 'n') {
		cout << "Would you like to move army units around? (y/n) \n";
		cin >> orderAnswer2;
		if (orderAnswer2 == 'y')
			repeatMoveArmyUnitsAroundLoop = true;
		else if (orderAnswer2 == 'n')
			repeatMoveArmyUnitsAroundLoop = false;
		else
			cout << "That is not a valid command. \n";
	}
	
	int armyAmountOnTerritorySource;
	while (repeatMoveArmyUnitsAroundLoop) {
		cout << "Here are the territories you chose to defend and the number of army units on them: \n";
		for (Territory* territory : toDefend)
		{
			cout << territory->getTName() << " " << territory->getArmyAmount() << endl;
		}

		cout << "From which territory would you like to move army units from? \n";
		cin >> territorySource;

		if (makeSureTerritoryAnswerExists(toDefend, territorySource))
		{
			for (Territory* territory : toDefend)
			{
				if (territory->getTName() == territorySource)
					armyAmountOnTerritorySource = territory->getArmyAmount();
			}

			cout << "To which territory would you like to move army units to? \n";
			cout << "These are the territories available in your attack list: \n";
			for (Territory* territory : toAttack)
			{
				cout << territory->getTName() << endl;
			}
			cin >> territoryDestination;

			if (makeSureTerritoryAnswerExists(toAttack, territoryDestination))
			{
				cout << "Number of units to move? \n";
				cin >> armyUnitsToBeMoved; 

				while (armyUnitsToBeMoved > armyAmountOnTerritorySource)
				{
					cout << "Army amount entered is more than available army amount. Please enter again. \n";
					cin >> armyUnitsToBeMoved;
				}

				for (Territory* territory : toDefend)
				{
					if (territory->getTName().compare(territorySource) == 0)
					{
						originalArmyAmount = territory->getArmyAmount();
						finalArmyAmount = originalArmyAmount - armyUnitsToBeMoved;
						territory->setArmyAmount(finalArmyAmount);
					}

					if (territory->getTName().compare(territoryDestination) == 0)
					{
						originalArmyAmount = territory->getArmyAmount();
						finalArmyAmount = originalArmyAmount + armyUnitsToBeMoved;
						territory->setArmyAmount(finalArmyAmount);

					}
				}

				//reset answer
				orderAnswer2 = 'x';
				while (orderAnswer2 != 'y' && orderAnswer2 != 'n')
				{
					cout << "Would you like to move more army units around? (y/n) \n";
					cin >> orderAnswer2;
					if (orderAnswer2 == 'y')
						repeatMoveArmyUnitsAroundLoop = true;
					else if (orderAnswer2 == 'n')
						repeatMoveArmyUnitsAroundLoop = false;
					else
						cout << "Invalide command. Please input answer again. \n";

				}
				
			}

		}
		else
			cout << "Entered territory is not a valid territory.Choose again. \n";

	}

	//Look at cards available  in hand
	cout << "Here are your cards from which you can create orders from: \n";
	vector<Card*> cardsAvailable = hand->getCards();
	for (Card* card : cardsAvailable) {
		cout << card->getCardName(card->getCardType()) << endl;
	}

	string cardToUse;
	cout << "Which card would you like to use? \n";
	cin >> cardToUse;

	if (cardToUse.compare("bomb") == 0)
		Order* issued = new Order("bomb");
	else if (cardToUse.compare("blockade") == 0)
		Order* issued = new Order("blockade");
	else if (cardToUse.compare("airlift") == 0)
		Order* issued = new Order("airlift");
	else if (cardToUse.compare("diplomacy") == 0)
		Order* issued = new Order("negotiate");
	else if (cardToUse.compare("reinforcement"))
	{
		setArmiesAmount(getArmiesAmount() + 5);
	}
	 //take away the card that was used
	//add order to ordersList?

	/*-------------------OLD CODE--------------------*/
	//Order* issued = new Order();
	//string x;

	//printOrderList();
	//cout << "Please type out the order you would like to issue: \nAirlift \nBomb \nBlockade \nNegotiate" << endl;
	//cin >> x;
	////discoverOrderType(x, issued);
	//Order* issued = new Order(x);
	//ordersList->addOrder(issued);
	//cout << "Order was issued: " << issued->getOrderName() << endl;
	//cout << "Current Player orders: " << endl;
	//for (auto o : ordersList->getOrdersList()) {
	//	cout << *o;
	//}
}

//making sure territory enetered from command line is a proper territory
bool Player::makeSureTerritoryAnswerExists(vector<Territory*> territoryList, string territoryName) {
	for (Territory* t : territoryList) {
		if (t->getTName() == territoryName)
			return true;
	}
	return false;
}

