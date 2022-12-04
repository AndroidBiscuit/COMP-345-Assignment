#include "PlayerStrategiesDriver.h"
#include <iostream>
#include "GameEngine.h"
#include "Map.h"
#include "Player.h"
using namespace std;

void testPlayerStrategies() {

    GameEngine* newGame = new GameEngine();

    string fileName = "Japan.map";

    newGame->loadMap(fileName);

    if (newGame->getMap()->getValid()) {
        newGame->addPlayer("Human", "Human");
        newGame->addPlayer("Neutral", "Neutral");
        newGame->addPlayer("Cheater", "Cheater");
        newGame->addPlayer("Aggressive", "Aggressive");
        newGame->addPlayer("Benevolent", "Benevolent");

        newGame->gameStartSetting();

        newGame->mainGameLoop(10000);

    }

    system("pause");
}