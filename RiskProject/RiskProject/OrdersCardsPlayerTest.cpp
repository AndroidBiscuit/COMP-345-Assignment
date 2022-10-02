#include "OrdersCardsPlayerTest.h"
#include <string>
using std::string;
using std::endl;
using std::cout;

Order::Order(){
	string orderName;
}

Order::Order(string n){
	this->orderName = n;
}

Order::~Order(){
	cout << "Order " << orderName << " will be deleted." << endl;
	orderName.clear();
}

string Order::getName(){
	return orderName;
}

void Order::setName(string name) {
	orderName = name;
}

ostream& operator<<(ostream& out, const Order& o){
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

ostream& operator<<(ostream& out, const OrdersList& p){
	out << "The player has the following list of orders:" << endl;
	for (auto i : p.listOfOrders) {
		out << *i;
	}
	return out;

}