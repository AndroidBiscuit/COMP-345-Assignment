#pragma once
#include <iostream>
#include <vector>
#include "Map.h"
//#include "Cards.h"
#include "OrdersCardsPlayerTest.h"
class Map;
class Territory;
class Player{
	static int createdPlayers;
private:
	int playerID;
	string name;
	vector<Territory*> territory;
	vector<Card*> handCard;
	OrdersList* orders;

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
	void setCards(vector<Card*>& cards);
	void setOrdersList(OrdersList* orders);

	//Accessor methods
	string getName();
	int getPlayerID();
	vector<Territory*> getTerritory();
	vector<Card*> getCards();
	OrdersList* getOrders();

	//method
	void printOrderList(void);
	void discoverOrderType(string x, Order* issued);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack(vector<Territory*>);
	void issueOrder();
	void addTerritory(Territory*);
	void addCard(Card*);

};