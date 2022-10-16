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
	
	//constructors
	Order(); 
	Order(string orderName);
	Order(const Order& originalOrder); 
	
	//assignment operator
	Order& operator= (const Order& o); 

	//destructor
	~Order(); 
	
	//Assignment methods
	void setOrderName(string x);
	void setOrderEffect(string x);
	void setOrderExecutionFlag(bool flag);

	//Accessor methods
	string getOrderName();
	string getOrderEffect();
	bool getOrderExecutionFlag();

	//methods
	virtual bool validate(string order);
	virtual void execute();
	
	//stream insertion
	friend ostream& operator << (ostream& in, Order order);
};


class OrdersList
{
private:
	list<Order*> ordersList;
public:
	//list<Order*> ordersList;
	//constructors
	OrdersList(); 
	OrdersList(const OrdersList& originalOrdersList); 
	
	//assignment operator
	OrdersList& operator= (const OrdersList& ol); 

	//destructor
	~OrdersList();  

	//methods
	list<Order*> getOrdersList();
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
	Deploy(const Deploy& d); 
	Deploy& operator= (const Deploy& d);  
	~Deploy();  
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
	Advance(const Advance& a);
	Advance& operator= (const Advance& a);
	~Advance();
	bool validate(string order);
	void execute();

};

class Bomb : public Order
{
private:
public:
	Bomb();
	Bomb(string name);
	Bomb(const Bomb& b);
	Bomb& operator= (const Bomb& b);
	~Bomb();
	bool validate(string order);
	void execute();
};

class Blockade : public Order
{
private:
public:
	Blockade();
	Blockade(string name);
	Blockade(const Blockade& b);
	Blockade& operator= (const Blockade& b);
	~Blockade();
	bool validate(string order);
	void execute();

};

class Airlift : public Order
{
private:
public:
	Airlift();
	Airlift(string name);
	Airlift(const Airlift& a);
	Airlift& operator= (const Airlift& a);
	~Airlift();
	bool validate(string order);
	void execute();

};

class Negotiate : public Order
{
private:
public:
	Negotiate();
	Negotiate(string name);
	Negotiate(const Negotiate& a);
	Negotiate& operator= (const Negotiate& a);
	~Negotiate();
	bool validate(string order);
	void execute();

};