#pragma once
#include <list>
#include <string>
#include"Map.h"
#include"Player.h"
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

	//stream insertion
	friend ostream& operator << (ostream& in, OrdersList ordersList);
};


//children classes of Order - override validate() and execute()
class Deploy: public Order
{
private:
	int armyUnits;
	Territory* territory;
	Player* player;
public:
	Deploy();
	Deploy(const Deploy& d); 
	Deploy& operator= (const Deploy& d);  
	~Deploy();  
	Deploy(string name);
	Deploy(int armyUnits, Territory* t, Player* p);
	bool validate(Territory* t, Player* p);
	void execute();

};

class Advance : public Order
{
private:
	int armyUnits;
	Territory* srcTerritory;
	Territory* dstnTerritory;
	Player* player;
public:
	Advance();
	Advance(string name);
	Advance(const Advance& a);
	Advance(Player* p, Territory* a, Territory* b, int armyUnits);
	Advance& operator= (const Advance& a);
	~Advance();
	bool validate(Player* p, Territory* a, Territory* b, int x);
	void execute();

};

class Bomb : public Order
{
private:
	Player* player;
	Territory* territory;
public:
	Bomb();
	Bomb(string name);
	Bomb(const Bomb& b);
	Bomb(Player* p, Territory* t);
	Bomb& operator= (const Bomb& b);
	~Bomb();
	bool validate(Player *p, Territory* t);
	void execute();
};

class Blockade : public Order
{
private:
	Player* player;
	Player* neutralPlayer;
	Territory* territory;
public:
	Blockade();
	Blockade(string name);
	Blockade(const Blockade& b);
	Blockade(Territory* territory, Player* player, Player* np);
	Blockade& operator= (const Blockade& b);
	~Blockade();
	bool validate(Territory* territory, Player* player);
	void execute();

};

class Airlift : public Order
{
private:
	int armyUnits;
	Territory* srcTerritory;
	Territory* dstnTerritory;
	Player* player;
public:
	Airlift();
	Airlift(string name);
	Airlift(const Airlift& a);
	Airlift(Player* p, Territory* a, Territory* b, int armyUnits);
	Airlift& operator= (const Airlift& a);
	~Airlift();
	bool validate(Player* p, Territory* src, Territory* dstn, int armyNum);
	void execute();

};

class Negotiate : public Order
{
private:
	Player* enemyPlayer;
	Player* player;
public:
	Negotiate();
	Negotiate(string name);
	Negotiate(const Negotiate& a);
	Negotiate(Player* p1, Player* p2);
	Negotiate& operator= (const Negotiate& a);
	~Negotiate();
	bool validate(Player* p1, Player* p2);
	void execute();

};
