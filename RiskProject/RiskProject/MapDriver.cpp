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
    for (auto pair : mapLoader.myMap->continentIndexDictionary) {
        cout << pair.first->getCName() << ": " << pair.second << endl;
        /*for (string j : mapLoader.myMap->allTerritory[i]->adjacentTerritoryMembers) {
            cout << j << ", ";*/
        //}
        cout << endl;
    }
    /*cout << "-------------------------continent set-----------------------------" << endl;
    for (int i = 0; i < mapLoader.myMap->allContinent.size(); i++) {
        cout << mapLoader.myMap->allContinent[i]->getCName() << endl;
    }*/

    //cout << "-------------------------trying something here-----------------------------"  << endl;
    ////Creates graph from data
    //for (int i = 0; i < mapLoader.myMap->allTerritory.size(); i++)
    //{
    //    //for each territory

    //    for (int j = 0; j < mapLoader.myMap->allTerritory[i]->adjacentTerritoryMembers.size(); j++)
    //    { //cout << mapLoader.myMap->allTerritory[i]->adjacentTerritoryMembers[j] << endl;
    //        string adjTerritoryName = mapLoader.myMap->allTerritory[i]->adjacentTerritoryMembers[j];
    //        int destTerritoryID = mapLoader.myMap->getTerritoryIDFromTName(adjTerritoryName);
    //        mapLoader.myMap->addEdge(mapLoader.myMap->graph, i, destTerritoryID);
    //    }
    //}
    //mapLoader.myMap->addEdge()
    //cout << mapLoader.myMap->getTerritoryNameFromTerritoryID(0);
   /* cout << "-------------------------trying something here-----------------------------" << endl;
    for (int source = 0; source < mapLoader.myMap->allTerritory.size(); source++) 
    {
        for (int neighbour : mapLoader.myMap->graph)
            cout << "there is an edge between " << source << " and " << neighbour <<endl;

    }*/
    

}

//mapLoader contains all territories and continennts 