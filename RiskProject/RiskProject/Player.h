#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Map.h"
//#include "Cards.h"

using std::string;
using std::ostream;
using std::vector;
class Map;
class Territory;

class OrderT {
private:
	string orderName;


public:
	OrderT();
	OrderT(string);
	~OrderT();
	string getName();
	void setName(string);
	friend ostream& operator<<(ostream& out, const OrderT& p);

};

class OrdersListT {
public:
	vector<OrderT*> listOfOrders;
	int count;
	void addOrder(OrderT* other);
	friend ostream& operator << (ostream& out, const OrdersListT& p);
	OrdersListT();
	~OrdersListT();
};

class CardT {
private:
	string cardName;


public:
	CardT();
	CardT(string);
	~CardT();
	string getName();
	friend ostream& operator<<(ostream& out, const CardT& p);

};

class Player{
	static int createdPlayers;
private:
	int playerID;
	string name;
	vector<Territory*> territory;
	vector<CardT*> handCard;
	OrdersListT* ordersT;

	friend class Card;
	friend class GameEngine;
	friend class Map;

public:
	//stream Insertion
	friend ostream& operator<< (ostream& out, const Player& p);
	
	//Constructors
	Player();
	Player(const Player& p);

	//Destructors
	~Player();

	//Assignment Operators
	Player& operator = (const Player&);
	void setPlayerID(int playerID);
	void setName(string name);
	void setTerritory(vector<Territory*> const& other);
	void setCards(vector<CardT*>& cards);
	void setOrdersList(OrdersListT* orders);

	//Accessor methods
	string getName();
	int getPlayerID();
	vector<Territory*> getTerritory();
	vector<CardT*> getCards();
	OrdersListT* getOrders();

	//method
	void printOrderList(void);
	void discoverOrderType(string x, OrderT* issued);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack(vector<Territory*>);
	void issueOrder();
	void addTerritory(Territory*);
	void addCard(CardT*);

};

