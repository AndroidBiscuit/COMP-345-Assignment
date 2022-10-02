#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::string;
using std::ostream;
using std::vector;

class Order {
private:
	string orderName;


public:
	Order();
	Order(string);
	~Order();
	string getName();
	void setName(string);
	friend ostream& operator<<(ostream& out, const Order& p);

};

class OrdersList {
public:
	vector<Order*> listOfOrders;
	int count;
	void addOrder(Order* other);
	friend ostream& operator << (ostream& out, const OrdersList& p);
	OrdersList();
	~OrdersList();
};

class Card {
private:
	string cardName;


public:
	Card();
	Card(string);
	~Card();
	string getName();
	friend ostream& operator<<(ostream& out, const Card& p);

};