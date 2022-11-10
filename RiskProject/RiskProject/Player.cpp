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
vector<Territory*> Player::toAttack()
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
vector<Territory*> Player::toDefend()
{
	vector<Territory*> defendList;
	for (auto t : territory) {
		defendList.push_back(t);
	}

	return defendList;
}


void Player::issueOrder()
{
	vector<Territory*> attackList = toAttack();
	vector<Territory*> defendList = toDefend();
	string orderAnswer;
	string territoryAnswer;
	int armyAmountAnswer;
	int newArmyAmount;
	//while player still has army units, order must be deploying them
	while (getArmiesAmount() != 0) {
		cout << "You have armies left in your reinforcement pool, what would you like to do? (attack/defend)\n";
		cin >> orderAnswer;
		if (orderAnswer.compare("attack") == 0)
		{
			cout << "Here are the available territories to attack: \n";
			for (Territory* territory : attackList) {
				cout << territory->getTName() << endl;
			}
			cin >> territoryAnswer;
		}
		else if (orderAnswer.compare("defend") == 0)
		{
			cout << "Here are the available territories to defend: \n";
			for (Territory* territory : defendList) {
				cout << territory->getTName() << endl;
			}
			cin >> territoryAnswer;
		}
		else {
			cout << "You entered an invalid command \n";
		}

		cout << "How many army units would you like to deploy to " << territoryAnswer << " ?\n";
		cout << "You have " << getArmiesAmount() << " army units left. \n";
		cin >> armyAmountAnswer;
		newArmyAmount = getArmiesAmount() - armyAmountAnswer;
		setArmiesAmount(newArmyAmount);

		cout << armyAmountAnswer << " units of army has been deployed to " << territoryAnswer << endl;

	}




	/*-------------------OLD CODE--------------------*/
	//Order* issued = new Order();
	string x;

	printOrderList();
	cout << "Please type out the order you would like to issue: \nDeploy \nAdvance \nAirlift \nBomb \nBlockade \nNegotiate" << endl;
	cin >> x;
	//discoverOrderType(x, issued);
	Order* issued = new Order(x);
	ordersList->addOrder(issued);
	cout << "Order was issued: " << issued->getOrderName() << endl;
	cout << "Current Player orders: " << endl;
	for (auto o : ordersList->getOrdersList()) {
		cout << *o;
	}
}

