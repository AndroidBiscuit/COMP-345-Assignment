#pragma once
#include <string>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "CommandProcessing.h"
#include "LoggingObserver.h"

using namespace std;
class Deck;
class GameEngine : public Subject {
private:
    string state;
	vector<Player*> players;
	Map* map;
	Deck* deck;

	bool orderIssueRecursion;
	bool executeOrderRecursion;
	bool deployOrdersFlag;

	string outputResults;

public:
	bool hasHumanPlayer = false;
	//Neutral Player:
	Player* neutral;
	vector<string> winnerForEachMap;
	vector<vector<string>> winnersForTournament;

public:
	GameEngine(void);								/*Constructors*/
	GameEngine(const GameEngine& other);			/*Copy Constructors*/
													
	void setState(string newState);					/*Getter and setter*/
	string getState();
	Map* getMap();
	vector<Player*> getPlayers();
	void clearPlayers();
	void clearWinnerForEachMap();
	void setOutputResults(string outputResults);

	GameEngine& operator =(const GameEngine& other);	/*assignment operator*/

	friend ostream& operator << (ostream& out, const GameEngine& g);		/*Stream Insertion*/
	~GameEngine();

	//Methods
	virtual string stringToLog(void);
	void startupPhase();
	void transition(string newState);
	bool loadMap(string fileName);
	void addPlayer();
	void addPlayer(string name);
	void addPlayer(string name, string strategy);
	void removePlayer(Player* toRemove);
	bool gameStartSetting();
	void mainGameLoop(int);

	void reinforcementPhase();
	void issueOrderPhase();
	void executeOrderPhase();
	int playerOwnsEntireContinent(Player* p, int x);
	bool playerOwnsAllContinents();
};