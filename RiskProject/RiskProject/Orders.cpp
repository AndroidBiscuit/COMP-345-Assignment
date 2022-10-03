#include "Orders.h"
#include <iostream>
#include<string>
#include <list>
#include <string>
using namespace std;


//-----------------------ORDERS FUNCTION IMPLEMENTATION----------------------//

Order::Order() {
	orderName = "";
}

Order::Order(string x) {
	orderName = x;
}

bool Order::validate(string order) {
	return false;
}

void Order::execute(Order order) {

}

string Order::getOrderName() { return orderName; }
void Order::setOrderName(string name)
{
	this->orderName = name;
}

string Order::getOrderEffect() { return orderEffect; }

void Order::setOrderEffect(string orderEffect)
{
	this->orderEffect = orderEffect;
}
/*
istream& operator >>(istream& input, Order order) {

}
*/
ostream& operator <<(ostream& input, Order order) {
	input << "Order is: " << order.getOrderName() << endl;
	input<<order.getOrderEffect() << endl;
	return input;

}


//-----------------------DEPLOY FUNCTION IMPLEMENTATION----------------------//

Deploy::Deploy() {}

Deploy::Deploy(string name) {
	orderName = name;
	orderEffect = "move a certain number of army units from the current player’s reinforcement pool to one of the current player’s territories.";
}

bool Deploy::validate(string order){
	//for now: if string matches with the name of order, then its validated
	string deploy = "deploy";
	if (deploy.compare(order) == 0)
		return true;

	return false;
}

void Deploy::execute(Order order) {
	if (validate(order.getOrderName()))
	{
		cout << this;
	}
	
}


//-----------------------ADVANCE FUNCTION IMPLEMENTATION----------------------//
Advance::Advance() {}

Advance::Advance(string name) {
	orderName = name;
}

bool Advance::validate(string order) {
	//for now: if string matches with the name of order, then its validated
	string deploy = "advance";
	if (deploy.compare(order) == 0)
		return true;

	return false;
}

void Advance::execute(Order order) {
	if (validate(order.getOrderName()))
	{
		cout << "Advance: move a certain number of army units from one territory (source territory) to another territory (target territory)" << endl;
	}

}

//-----------------------BOMB FUNCTION IMPLEMENTATION----------------------//

Bomb::Bomb() {}

Bomb::Bomb(string name) {
	orderName = name;
}

bool Bomb::validate(string order) {
	//for now: if string matches with the name of order, then its validated
	string deploy = "bomb";
	if (deploy.compare(order) == 0)
		return true;

	return false;
}

void Bomb::execute(Order order) {
	if (validate(order.getOrderName()))
	{
		cout << "Bomb: destroy half of the army units located on an opponent’s territory that is adjacent to one of the current player’s territories." << endl;
	}

}

//-----------------------BlOCKADE FUNCTION IMPLEMENTATION----------------------//

Blockade::Blockade() {}

Blockade::Blockade(string name) {
	orderName = name;
}

bool Blockade::validate(string order) {
	//for now: if string matches with the name of order, then its validated
	string deploy = "blockade";
	if (deploy.compare(order) == 0)
		return true;

	return false;
}

void Blockade::execute(Order order) {
	if (validate(order.getOrderName()))
	{
		cout << "Blockade: triple the number of army units on one of the current player’s territories and make it a neutral	territory" << endl;
	}

}

//-----------------------AIRLIFT FUNCTION IMPLEMENTATION----------------------//

Airlift::Airlift() {}

Airlift::Airlift(string name) {
	orderName = name;
}

bool Airlift::validate(string order) {
	//for now: if string matches with the name of order, then its validated
	string deploy = "airlift";
	if (deploy.compare(order) == 0)
		return true;

	return false;
}


void Airlift::execute(Order order) {
	if (validate(order.getOrderName()))
	{
		cout << "Airlift: advance a certain number of army units from one of the current player’s territories to any another yerritory" << endl;
	}

}

//-----------------------NEGOTIATE FUNCTION IMPLEMENTATION----------------------//

Negotiate::Negotiate() {}

Negotiate::Negotiate(string name) {
	orderName = name;
}

bool Negotiate::validate(string order) {
	//for now: if string matches with the name of order, then its validated
	string deploy = "negotiate";
	if (deploy.compare(order) == 0)
		return true;

	return false;
}

void Negotiate::execute(Order order) {
	if (validate(order.getOrderName()))
	{
		cout << "Negotiate: prevent attacks between the current player and the player targeted by the negotiate order until the end of the turn" << endl;
	}

}



//----------------------ORDERSLIST FUNCTION IMPLEMENTATION----------------------//

OrdersList::OrdersList() {

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