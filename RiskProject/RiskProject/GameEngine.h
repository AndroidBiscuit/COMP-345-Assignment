#pragma once
#include <string>
#include <iostream>
using namespace std;

class GameEngine {
private:
	string state;

public:
	GameEngine();
	GameEngine(const GameEngine*);				//copy constructor

	GameEngine& operator =(const GameEngine&);	//assign operator

	void setState(string s) {					//getter and setter
		state = s;
	}
	string getState() {
		return state;
	}

	friend ostream& operator << (ostream& out, const GameEngine& ge);	//stream insertion operator
	friend istream& operator >> (istream& in, GameEngine& ge);

	int testGameStates(int opt);				//testGameStates function
};


