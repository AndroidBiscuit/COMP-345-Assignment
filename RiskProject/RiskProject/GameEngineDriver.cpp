#include "GameEngine.h"


int main(void) {

	cout << "Welcome to Warzone! " << endl;
	GameEngine* currentGame = new GameEngine();

	currentGame->startupPhase();

	delete currentGame;
	currentGame = nullptr;
	return 0;
}
