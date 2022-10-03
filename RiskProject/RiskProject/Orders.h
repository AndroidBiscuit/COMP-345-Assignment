#pragma once
#include <list>
#include <string>
using namespace std;

class Order
{
private:
	string orderName;

public:
	
	Order(); 
	Order(string orderName);
	
	//virtual void validate(Order order);
	//virtual void execute(Order order);

	string getOrderName();
	//friend istream& operator >> (istream& in, Order order);
	//friend ostream& operator << (ostream& in, Order order);
};


class OrdersList
{
private:

public:
	list<Order*> ordersList;
	list<int> alist;
	list<Order> list2;
	

	OrdersList(); //constructor
	//TO DO OrdersList(const OrdersList& originalOrdersList); //copy constructor
	//TO DO OrdersList& operator= (const OrdersList& ol); //assignment operator
	//~OrdersList(); //destructor


	void addOrder(Order* order);
	void addOrder(int a);
	void move(int sourceIndex, int destinationIndex);
	void remove(int indexOfOrder); 
	void showOrdersList();
};



/*

//children classes of Order - override validate() and execute()
class Deploy: public Order
{
private:
public:
	Deploy();
	bool validate(string order);
	void execute(Order order);

};

class Advance : public Order
{
private:
public:
	void validate(Order order);
	void execute(Order order);

};

class Bomb : public Order
{
private:
public:
	void validate(Order order);
	void execute(Order order);
};

class Block : public Order
{
private:
public:
	void validate(Order order);
	void execute(Order order);

};

class Airlift : public Order
{
private:
public:
	void validate(Order order);
	void execute(Order order);

};

class Negotiate : public Order
{
private:
public:
	void validate(Order order);
	void execute(Order order);

};
*/