#pragma once
#include <string>
#include <iostream>
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include "CommandProcessing.h"

using namespace std;
class player;
class GameEngine {
private:
    string state;
	vector<Player*> players;
	Map* map;
	Deck* deck;

public:
	//Neutral Player:
	Player* neutral;

public:
	GameEngine(void);								/*Constructors*/
	GameEngine(const GameEngine& other);			/*Copy Constructors*/
													
	void setState(string newState);					/*Getter and setter*/
	string getState();
	Map* getMap();
	vector<Player*> getPlayers();

	GameEngine& operator =(const GameEngine& other);	/*assignment operator*/

	friend ostream& operator << (ostream& out, const GameEngine& g);		/*Stream Insertion*/
	~GameEngine();

	//Methods
	void startupPhase();
	void reinforcementPhase();
	void transition(string newState);
	bool loadMap(string fileName);
	void addPlayer();
	void addPlayer(string name);
	void removePlayer(Player* toRemove);
	bool gameStartSetting();
};