#include "GameEngine.h"
#include "GameEngineDriver.h"

void testStartupPhase() {

	cout << "Welcome to Warzone! " << endl;
	GameEngine* currentGame = new GameEngine();

	currentGame->startupPhase();

	delete currentGame;
	currentGame = nullptr;

}