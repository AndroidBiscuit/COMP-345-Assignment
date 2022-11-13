#include "LoggingObserverDriver.h"
#include "LoggingObserver.h"
#include "GameEngine.h"
#include <iostream>
#include <fstream>
#include <string>
using std::ofstream;
using std::endl;
using std::cout;
using std::invalid_argument;

void testLoggingObserver() {
	ofstream log;
	log.open("gamelog.txt");

	if (log) {
		//emptying file here
		cout << "Emptying gamelog.txt for this game..." << endl;
		cout << endl;
		log.open("gamelog.txt", std::ofstream::out | std::ofstream::trunc);
		log.close();
	}
	else {
		cout << "ERROR - File could not be opened!" << endl;
		throw invalid_argument("ERROR - File could not be opened!");
	}

	cout << "Welcome to Warzone! " << endl;
	GameEngine* currentGame = new GameEngine();
	LogObserver* obs = new LogObserver(currentGame);

	currentGame->startupPhase();

	delete obs;
	obs = nullptr;
	delete currentGame;
	currentGame = nullptr;

}