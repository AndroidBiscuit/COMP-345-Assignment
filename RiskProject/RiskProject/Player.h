#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include "PlayerStrategies.h"

using std::string;
using std::ostream;
using std::vector;

class Map;
class Territory;
class Hand;
class Order;
class OrdersList;
class Deploy;
class Cards;
class PlayerStrategy;


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
	bool ordersToIssueFlag; 
	vector<int> friendlyPlayers; // Cannot attack these during the turn

	//From Cards
	Hand* hand;
	//From Orders
	OrdersList* ordersList;
	//From PlayerStrategies
	PlayerStrategy* playerStrategy;
	vector<Territory*> attackList;
	vector<Territory*> defendList;
	

public:
	vector<Territory*> tToAttack;
	vector<Territory*> tToDefend;
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
	void setOrdersToIssueFlag(bool ordersLeftToIssue);
	void setOrdersList(Order* order);


	//Accessor methods
	string getName();
	int getPlayerID();
	int getArmiesAmount();
	vector<Territory*> getTerritory();
	void removeTerritory(Territory* toRemove);
	Hand* getHand();
	OrdersList* getOrders(); 
	vector<Player*> getCanNotAttack();
	bool getConquered();
	bool getOrdersToIssueFlag();

	//method
	void printOrderList(void);
	void addFriendlyPlayer(int);
	void clearFriendlyPlayer();
	bool attackablePlayer(int);
	//int deployArmies();
	void discoverOrderType(string x, Order* issued);
	vector<Territory*> availableTerritoriesToDefend();
	vector<Territory*> availableTerritoriesToAttack();
	void issueOrder(Player* p, vector<Player*> playersVector); //here
	void addTerritory(Territory*);
	bool makeSureTerritoryAnswerExists(vector<Territory*>, string name);


	//Intelligent player
	bool intelligent;

	Player* neutral;
	Map* map;

	//Friend classes:
	friend class Card;
	friend class Hand;
	friend class OrdersList;
	friend class Deck;

	//Playter strategy
	PlayerStrategy* getStrategy();
	void setStrategy(PlayerStrategy* strategy);
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
	void issueOrder(string order);
	vector<Territory*> getAttackList();
	vector<Territory*> getDefendList();
	void setAttackList();
	void setDefendList();

	//define player strategy
	void definePlayerStrategy(string strategy);
	bool isNeutral;
};
