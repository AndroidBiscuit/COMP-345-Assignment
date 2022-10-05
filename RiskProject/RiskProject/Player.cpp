#include "Player.h"
#include <string>
using std::string;
using std::endl;
using std::cout;

class Order;
class Territroy;
int Player::createdPlayers = 0;

//constructors:
Player::Player() {
	createdPlayers++;
	name = "default";
	playerID = createdPlayers;
	orders = new OrdersList();
}

Player::Player(const Player& p) {
	createdPlayers++;
	this->name = p.name;
	this->playerID = p.playerID;
	for (auto p : p.territory) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);

	}
	for (auto p : p.handCard) {
		Card* temp = new Card(*p);
		addCard(temp);

	}
	orders = new OrdersList();
	for (auto p : p.orders->listOfOrders) {
		Order* temp = new Order();
		temp->getName() = p->getName();
		orders->addOrder(temp);
	}
}

Player& Player::operator=(const Player& p) {
	name = p.name;
	playerID = p.playerID;
	for (Territory* p : p.territory) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);
	}
	for (auto p : p.handCard) {
		Card* temp = new Card(*p);
		addCard(temp);

	}
	orders = new OrdersList();
	for (auto p : p.orders->listOfOrders) {
		Order* temp = new Order();
		temp->setName(p->getName());
		orders->addOrder(temp);
	}
	return *this;
}

ostream& operator<< (ostream& out, const Player& p) {
	out << "Player Name: " << p.name << endl;
	out << "ID: " << p.playerID << endl;
	out << "Owned Territories: " << endl;
	for (int i = 0; i < p.territory.size(); ++i) {
		out << "<" << p.territory.at(i)->getTName() << ">";
	}
	out << endl;
	out << "Handed Cards: " <<endl;
	for (Card* i : p.handCard) {
		out << *i;
	}
	out << endl;
	out << "Orders issued: " << endl;
	for (Order* i : p.orders->listOfOrders) {
		out << *i;
	}
	return out;
}

//destructor
Player::~Player() {
	cout << "Player " << this->getName() << " will now be destroyed." << endl;
	if(orders != NULL) {
		delete orders;
	}
	//release memory
	territory.clear();
	handCard.clear();
}

void Player::setName(string s) {
	this->name = s;
}

void Player::setPlayerID(int playerID){
	this->playerID = playerID;
}

void Player::setTerritory(vector<Territory*> const& other) {
	territory = other;
}

void Player::setCards(vector<Card*>& cards){
	this->handCard = cards;
}

void Player::setOrdersList(OrdersList* orders){
	this->orders = orders;
}

string Player::getName() {
	return this->name;
}

int Player::getPlayerID(void) {
	return playerID;
}

vector<Territory*> Player::getTerritory() {
	return territory;
}

vector<Card*> Player::getCards(void) {
	return handCard;
}

OrdersList* Player::getOrders(void) {
	return orders;
}

void Player::addTerritory(Territory* ter) {
	territory.push_back(ter);
}
void Player::addCard(Card* other) {
	handCard.push_back(other);
}

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
	string options[] = { "DEPLOY", "ADVANCE", "BOMB", "BLOCKADE", "AIRLIFT", "NEGOTIATE" };

	for (int i = 0; i < 6; i++)
	{
		if (options[i].compare(x) == 0) {
			issued->setName(options[i]);
			return;
		}
	}

	issued->setName("UNKOWN ORDER");
	return;
}

vector<Territory*> Player::toAttack(vector<Territory*> attackList)
{
	cout << "The list of territories that are be Attack" << endl;
	for (int i = 0; i < attackList.size(); i++)
	{
		cout << "Index " << i << " " << (*attackList[i]).getTName() << " " << (*attackList[i]).getCID() << endl;
	}
	return attackList;
}

vector<Territory*> Player::toDefend()
{
	vector<Territory*> defendList;
	Territory* temp = NULL;
	cout << "The list of territories that are be defended" << endl;
	for (int i = 0; i < territory.size(); i++)
	{
		cout << "Index " << i << " " << (*territory[i]).getTName() << " " << (*territory[i]).getCID() << endl;
		temp = territory[i];
		defendList.push_back(temp);
	}
	return defendList;
}

void Player::issueOrder()
{
	Order* issued = new Order();
	string x;

	printOrderList();
	cout << "Please type out the order you would like to issue: " << endl;
	cin >> x;
	discoverOrderType(x, issued);
	orders->addOrder(issued);
	cout << "Order was issued: " << issued->getName() << endl;
	cout << "Current Player orders: " << endl;
	for (auto o : orders->listOfOrders) {
		cout << *o;
	}
}

Order::Order() {
	string orderName;
}

Order::Order(string n) {
	this->orderName = n;
}

Order::~Order() {
	cout << "Order " << orderName << " will be deleted." << endl;
	orderName.clear();
}

string Order::getName() {
	return orderName;
}

void Order::setName(string name) {
	orderName = name;
}

ostream& operator<<(ostream& out, const Order& o) {
	out << o.orderName << endl;
	return out;
}

Card::Card() {
	string cardName;
}

Card::Card(string n) {
	this->cardName = n;
}

Card::~Card() {
	cout << "The Card " << cardName << " was deleted." << endl;
	cardName.clear();
}

string Card::getName() {
	return cardName;
}

ostream& operator<<(ostream& out, const Card& o) {
	out << o.cardName << endl;
	return out;
}

void OrdersList::addOrder(Order* other) {
	listOfOrders.push_back(other);
	count++;
}

OrdersList::OrdersList() {
	count = 0;
}
OrdersList::~OrdersList() {
	cout << "This list of orders will be deleted." << endl;
	for (auto o : listOfOrders) {
		delete o;
	}
}

ostream& operator<<(ostream& out, const OrdersList& p) {
	out << "The player has the following list of orders:" << endl;
	for (auto i : p.listOfOrders) {
		out << *i;
	}
	return out;

}