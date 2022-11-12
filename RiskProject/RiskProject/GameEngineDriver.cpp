#include "GameEngine.h"
#include "GameEngineDriver.h"

void testStartupPhase() {

	cout << "Welcome to Warzone! " << endl;
	GameEngine* currentGame = new GameEngine();

	currentGame->startupPhase();

	delete currentGame;
	currentGame = nullptr;
	
	system("pause");

	cout << "Welcome to Warzone! " << endl;
	GameEngine* currentGame2 = new GameEngine();

	currentGame2->startupPhase();

	delete currentGame2;
	currentGame2 = nullptr;

}