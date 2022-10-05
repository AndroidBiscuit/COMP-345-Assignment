#pragma once
#include <list>
#include <string>
using namespace std;

class Order
{
protected:
	string orderName;
	string orderEffect;
	bool orderExecutionFlag;

public:
	
	Order(); 
	Order(string orderName);
	
	virtual bool validate(string order);
	virtual void execute();

	string getOrderName();
	void setOrderName(string x);

	string getOrderEffect();
	void setOrderEffect(string x);

	bool getOrderExecutionFlag();
	void setOrderExecutionFlag(bool flag);
	
	//friend istream& operator >> (istream& in, Order order);
	friend ostream& operator << (ostream& in, Order order);
};


class OrdersList
{
private:

public:
	list<Order*> ordersList;	

	OrdersList(); //constructor
	//TO DO OrdersList(const OrdersList& originalOrdersList); //copy constructor
	//TO DO OrdersList& operator= (const OrdersList& ol); //assignment operator
	//~OrdersList(); //destructor


	void addOrder(Order* order);
	void move(int sourceIndex, int destinationIndex);
	void remove(int indexOfOrder); 
	void showOrdersList();
};





//children classes of Order - override validate() and execute()
class Deploy: public Order
{
private:
public:
	Deploy();
	Deploy(string name);
	bool validate(string order);
	void execute();

};

class Advance : public Order
{
private:
public:
	Advance();
	Advance(string name);
	bool validate(string order);
	void execute();

};

class Bomb : public Order
{
private:
public:
	Bomb();
	Bomb(string name);
	bool validate(string order);
	void execute();
};

class Blockade : public Order
{
private:
public:
	Blockade();
	Blockade(string name);
	bool validate(string order);
	void execute();

};

class Airlift : public Order
{
private:
public:
	Airlift();
	Airlift(string name);
	bool validate(string order);
	void execute();

};

class Negotiate : public Order
{
private:
public:
	Negotiate();
	Negotiate(string name);
	bool validate(string order);
	void execute();

};