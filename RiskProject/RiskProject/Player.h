#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

using std::string;
using std::ostream;
using std::vector;

class Map;
class Territory;
class Hand;
class Order;
class OrdersList;
class Deploy;


class Player{

private:
	//Data members:
	int playerID;
	int armiesAmount;
	string name;
	vector<Territory*> territory;
	vector<Player*> cannotAttack; // records the players that can't be attacked as using with the negotiate
	static int createdPlayers;
	bool conquered;

	//From Cards
	Hand* hand;
	//From Orders
	OrdersList* ordersList;
	

public:
	//stream Insertion
	friend ostream& operator<< (ostream& out, const Player& p);
	friend istream& operator >> (istream& in, Player& p);
	
	//Constructors
	Player();
	Player(const Player& p);

	//Destructors
	~Player();

	//Assignment Operators
	Player& operator = (const Player&);

	//Mutators:
	void setPlayerID(int playerID);
	void setArmiesAmount(int armies);
	void setName(string name);
	void setTerritory(vector<Territory*> const& other);
	void setOrdersList(OrdersList* orders); 
	void setConquered(bool result);


	//Accessor methods
	string getName();
	int getPlayerID();
	int getArmiesAmount();
	vector<Territory*> getTerritory();
	void removeTerritory(Territory* toRemove);
	Hand* getHand();
	vector<Card*> getCards();
	OrdersList* getOrders(); 
	vector<Player*> getCanNotAttack();
	bool getConquered();

	//method
	void printOrderList(void);
	int deployArmies();
	Order* discoverOrderType(string x);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void determineTarget(int state, Order* order);
	void determineSource(int state, Order* order);
	void issueOrder(); //here
	void addTerritory(Territory*);

	//From Cards
    void addCard(Card* card);
	void addOrder(Order* order);
	Hand* getHand();

	//Intelligent player
	bool intelligent;

	Player* neutral;
	Map* map;

	//Friend classes:
	friend class Card;
	friend class Hand;
	friend class OrdersList;
	friend class Deck;

};

