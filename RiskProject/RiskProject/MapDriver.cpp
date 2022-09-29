#include "MapDriver.h"
#include "MapLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <string.h>
using std::cerr;
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;
#include <cstdlib> // for exit function



// void testLoadMaps() {
Map* MapLoader::loadMap(string mapFilePath) {
    string line;
    string whatToDo = "default";
    int continentID = 1;
    Map* map;
    map = new Map();
    ifstream mapFile(mapFilePath);

    if(!mapFile.is_open()){
        cerr<<"file not found"<<endl;
        return nullptr;
    }

    try{
        while(getline(mapFile, line)){
            if(line == "" || line[0] == ';' ){ //insert semi colons to start of the first 3 lines to skip, or find a way to skip first 3 lines in txt fies
                continue;
            }else if(line.find("[Continents]")!= string::npos){
                whatToDo = "createContinents";
                continue;
            } else if(line.find("[Territories]") != string::npos){
                whatToDo = "createTerritories";
                continue;
            }


            if(whatToDo == "createContinents"){
                MapLoader::createContinent(&continentID, line, map);
            }else if(whatToDo == "createTerritories"){
                MapLoader::createTerritory(line,map);
            }
        }
        if(whatToDo == "default"){
            cout<<"The file was opened but not map was able to be created"<<endl;
            return nullptr;
        }

    }catch(exception e){
        e.what();
    }

    mapFile.close();
    cout<<"Completed Load Map"<<endl;
    return map;
}
// }
//     //Extracts data from .map 
// 	MapLoader mapLoader;
// 	mapLoader.setInputFileName("Canada1999.map");
// 	cout << mapLoader.getInputFileName() << endl;
// 	mapLoader.parseMapFile();

//     //print adjacent relation line by line
//     //each line represent each territory's adjacent relation with other t in map
//     cout << "-------------------------Territory vector-----------------------------" << endl;
//     cout << mapLoader.myMap->allTerritory.size() << endl;
//     cout << mapLoader.myMap->allContinent.size() << endl;
//     for (int i = 0; i < mapLoader.myMap->allTerritory.size(); i++) {
//         cout << mapLoader.myMap->allTerritory[i]->getTName() << ": ";
//         for (string j : mapLoader.myMap->allTerritory[i]->adjacentTerritoryMembers) {
//             cout << j << ", ";
//         }
//         cout << endl;
//     }
//     cout << "-------------------------continent vector-----------------------------" << endl;
//     for (int i = 0; i < mapLoader.myMap->allContinent.size(); i++) {
//       cout << mapLoader.myMap->allContinent[i]->getCName() << endl;
//     }

//     //print adjacent relation line by line
//   //each line represent each territory's adjacent relation with other t in map
//     cout << "-------------------------Territory dictionary-----------------------------" << endl;
//     cout << mapLoader.myMap->territoryIndexDictionary.size() << endl;
//     cout << mapLoader.myMap->continentIndexDictionary.size() << endl;
//     for (auto pair : mapLoader.myMap->territoryIndexDictionary) {
//         cout << pair.first << ": " << pair.second << endl;
//         cout << endl;
//     }

//     cout << "-------------------------Continent dictionary-----------------------------" << endl;
//     for (auto pair : mapLoader.myMap->continentIndexDictionary) {
//         cout << pair.first << ": " << pair.second << endl;
//         cout << endl;
//     }

//     cout << "-------------------------setting up graph-----------------------------"  << endl;
//     //Creates graph from data
//     int nodesAmount = mapLoader.myMap->territoryIndexDictionary.size();
    
//     for (int i = 0; i < mapLoader.myMap->allTerritory.size(); i++)
//     {
//         //for each territory

//         for (int j = 1; j < mapLoader.myMap->allTerritory[i]->adjacentTerritoryMembers.size(); j++)
//         { 
//             string adjTerritoryName = mapLoader.myMap->allTerritory[i]->adjacentTerritoryMembers[j];
//             int destTerritoryID = mapLoader.myMap->getTerritoryIDFromTName(adjTerritoryName);
//            mapLoader.myMap->addAdjacentTerritoryMembers(mapLoader.myMap->graph, i, destTerritoryID);
//         }
//     }
     
//     cout << "-------------------------------GRAPH REPRESENTATION-------------------------------" << endl;
//     int numOfTerritories = mapLoader.myMap->allTerritory.size();
//     mapLoader.myMap->printGraph(mapLoader.myMap->graph);

//     cout << "-------------------------------trying things out-------------------------------" << endl;
//     cout << "does edge between " << endl;
//     bool a = mapLoader.myMap->edgeExistance(mapLoader.myMap->graph, 75, 25);
//     bool b = mapLoader.myMap->edgeExistance(mapLoader.myMap->graph, 75, 70);
//     bool c = mapLoader.myMap->edgeExistance(mapLoader.myMap->graph, 75, 13);

//     cout << a << b << c;

// }

// //mapLoader contains all territories and continents 