#include "GameEngine.h"
#include "GameEngineDriver.h"

void testStartupPhase() {

	cout << "Welcome to Warzone! " << endl;
	GameEngine* currentGame = new GameEngine();

	currentGame->startupPhase();

	delete currentGame;
	currentGame = nullptr;

}

void testMainGameLoop() {

	cout << "Welcome to Warzone game loop! " << endl;
	GameEngine* currentGame = new GameEngine();
	/*Player* p1 = new Player();
	Player* p2 = new Player();

	Map* map = new Map();

	currentGame->addPlayer();*/

	currentGame->startupPhase();

	delete currentGame;
	currentGame = nullptr;
	
}