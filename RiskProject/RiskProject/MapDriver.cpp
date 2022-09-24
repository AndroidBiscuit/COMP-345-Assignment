#include "MapDriver.h"
#include "MapLoader.h"
#include <iostream>
#include<string>
using std::cerr;
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;
#include <cstdlib> // for exit function



void testLoadMaps() {

    //Extracts data from .map 
	MapLoader mapLoader;
	mapLoader.setInputFileName("Canada1999.map");
	cout << mapLoader.getInputFileName() << endl;
	mapLoader.parseMapFile();

    //print adjacent relation line by line
    //each line represent each territory's adjacent relation with other t in map
    cout << "-------------------------Territory vector-----------------------------" << endl;
    cout << mapLoader.myMap->allTerritory.size() << endl;
    cout << mapLoader.myMap->allContinent.size() << endl;
    for (int i = 0; i < mapLoader.myMap->allTerritory.size(); i++) {
        cout << mapLoader.myMap->allTerritory[i]->getTName() << ": ";
        for (string j : mapLoader.myMap->allTerritory[i]->adjacentTerritoryMembers) {
            cout << j << ", ";
        }
        cout << endl;
    }
    cout << "-------------------------continent vector-----------------------------" << endl;
    for (int i = 0; i < mapLoader.myMap->allContinent.size(); i++) {
      cout << mapLoader.myMap->allContinent[i]->getCName() << endl;
    }

    //print adjacent relation line by line
  //each line represent each territory's adjacent relation with other t in map
    cout << "-------------------------Territory dictionary-----------------------------" << endl;
    cout << mapLoader.myMap->territoryIndexDictionary.size() << endl;
    cout << mapLoader.myMap->continentIndexDictionary.size() << endl;
    for (auto pair : mapLoader.myMap->territoryIndexDictionary) {
        cout << pair.first << ": " << pair.second << endl;
        cout << endl;
    }

    cout << "-------------------------Continent dictionary-----------------------------" << endl;
    for (auto pair : mapLoader.myMap->continentIndexDictionary) {
        cout << pair.first << ": " << pair.second << endl;
        cout << endl;
    }

    cout << "-------------------------setting up graph-----------------------------"  << endl;
    //Creates graph from data
    int nodesAmount = mapLoader.myMap->territoryIndexDictionary.size();
    
    for (int i = 0; i < mapLoader.myMap->allTerritory.size(); i++)
    {
        //for each territory

        for (int j = 1; j < mapLoader.myMap->allTerritory[i]->adjacentTerritoryMembers.size(); j++)
        { 
            string adjTerritoryName = mapLoader.myMap->allTerritory[i]->adjacentTerritoryMembers[j];
            int destTerritoryID = mapLoader.myMap->getTerritoryIDFromTName(adjTerritoryName);
           mapLoader.myMap->addEdge(mapLoader.myMap->graph, i, destTerritoryID);
        }
    }
     
    cout << "-------------------------------GRAPH REPRESENTATION-------------------------------" << endl;
    int numOfTerritories = mapLoader.myMap->allTerritory.size();
    mapLoader.myMap->printGraph(mapLoader.myMap->graph);

    cout << "-------------------------------trying things out-------------------------------" << endl;
    cout << "does edge between " << endl;
    bool a = mapLoader.myMap->edgeExistance(mapLoader.myMap->graph, 75, 25);
    bool b = mapLoader.myMap->edgeExistance(mapLoader.myMap->graph, 75, 70);
    bool c = mapLoader.myMap->edgeExistance(mapLoader.myMap->graph, 75, 13);

    cout << a << b << c;

}

//mapLoader contains all territories and continents 