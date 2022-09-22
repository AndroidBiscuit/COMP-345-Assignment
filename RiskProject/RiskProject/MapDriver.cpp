#include "MapDriver.h"
#include "MapLoader.h"
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;
#include <cstdlib> // for exit function

void testLoadMaps() {
	MapLoader mapLoader;
	mapLoader.setInputFileName("C:/Users/janel/source/repos/COMP-345-Assignment/RiskProject/RiskProject/Canada1999.map");
	cout << mapLoader.getInputFileName() << endl;
	mapLoader.parseMapFile();

    //print adjacent relation line by line
    //each line represent each territory's adjacent relation with other t in map
    cout << mapLoader.myMap->allTerritory.size() << endl;
    cout << mapLoader.myMap->allContinent.size() << endl;
    for (int i = 0; i < mapLoader.myMap->allTerritory.size(); i++) {
        for (string j : mapLoader.myMap->allTerritory[i]->adjacentTerritoryMembers) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << "-------------------------continent set-----------------------------" << endl;
    for (int i = 0; i < mapLoader.myMap->allContinent.size(); i++) {
      cout << mapLoader.myMap->allContinent[i]->getCName() << endl;
    }

}