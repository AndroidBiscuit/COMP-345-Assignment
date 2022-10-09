#pragma once
#include <string>
#include <iostream>

using namespace std;

class GameEngine {
	string state;

public:
	GameEngine(void);								/*Constructors*/
	GameEngine(const GameEngine& other);			/*Copy Constructors*/
													
	void setState(string newState);					/*Getter and setter*/
	string getState();

	GameEngine& operator =(const GameEngine& other);	/*assignment operator*/

	friend ostream& operator << (ostream& out, const GameEngine& g);		/*Stream Insertion*/
	friend istream& operator >> (istream& in, GameEngine& g);

	int gameStates(int i);								/*main game loop*/
};