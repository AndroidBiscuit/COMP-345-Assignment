#include "GameEngine.h"


void testGameStates() {
	int current = 0;
	int next = 0;
	GameEngine g;
	do {										/*game state transit to next*/
		system("CLS");
		next = g.gameStates(current);
		current = next;
	} while (current != -1);

}
