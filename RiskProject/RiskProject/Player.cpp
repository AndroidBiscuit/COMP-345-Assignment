#include "Player.h"
#include <string>
using std::string;
using std::endl;
using std::cout;
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
}

Player::Player(const Player& p) {
	cout << "Player with ID-:" << createdPlayers << " was created." << endl;
	createdPlayers++;
	this->name = p.name;
	this->armiesAmount = p.armiesAmount;
	this->playerID = p.playerID;
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
	createdPlayers--;
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
	//Order* issued = new Order();
	string x;

	printOrderList();
	cout << "Please type out the order you would like to issue: " << endl;
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