#pragma once
#include <string>
#include <iostream>
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"

using namespace std;

class GameEngine {
private:
    string state;
	vector<Player*> players;


public:
	GameEngine(void);								/*Constructors*/
	GameEngine(const GameEngine& other);			/*Copy Constructors*/
													
	void setState(string newState);					/*Getter and setter*/
	string getState();

	GameEngine& operator =(const GameEngine& other);	/*assignment operator*/

	friend ostream& operator << (ostream& out, const GameEngine& g);		/*Stream Insertion*/
	friend istream& operator >> (istream& in, GameEngine& g);
	~GameEngine();

	int gameStates(int i);								/*main game loop*/
};