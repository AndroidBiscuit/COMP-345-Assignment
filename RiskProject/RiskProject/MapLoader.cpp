#include <iostream>
#include <fstream>
#include <string>
#include<map>
#include <sstream>
#include "MapLoader.h"
#include "Map.h"

// //default constructor
// MapLoader::MapLoader() {
//     myMap = nullptr;
//     inputFileName = "none";
// }

// //copy constructor
// MapLoader::MapLoader(const MapLoader* ml) {
//     myMap = ml->myMap;
//     inputFileName = ml->inputFileName;
// }

// //two parameters constructor
// MapLoader::MapLoader(Map* myMap, string fileName) {
//     this->myMap = new Map();
//     this->inputFileName = fileName;
    
// }

// //assignment operator
// MapLoader& MapLoader::operator = (const MapLoader& ml) {
//     this->myMap = ml.myMap;
//     this->inputFileName = ml.inputFileName;
//     return *this;
// }

// //stream insertion operator
// ostream& operator<< (ostream& out, const MapLoader& m) {
//     out << m.myMap << m.inputFileName << endl;
//     return out;
// }

// //destructor
// MapLoader::~MapLoader() {
//     inputFileName.clear();
//     delete myMap;
//     myMap = NULL;
// }

// //accessor
// string MapLoader::getInputFileName() {
//     return inputFileName;
// }

// //mutator
// void MapLoader::setInputFileName(const string& s) {
//     inputFileName = s;
// }

// //splits the line information from the text file by certain delimiter
// vector<string> MapLoader::tokenizeString(const string& s, char delimiter) {
//     vector <string> tokens;                   // Vector of string to save tokens
//     stringstream text(s);                     // stringstream class check1
//     string token;                              
//     while (getline(text, token, delimiter))  // Tokenizing by delimiter like '=', ','
//     {
//         tokens.push_back(token);
//     }
//     return tokens;
// }

// // captitalizes the first character of the name of Territories or continents
// void MapLoader::toUpper(std::string& str) {
//     if (str.length() == 0) {
//         return;
//     }

//     str[0] = std::toupper(str[0]);
// }


// //reads the map file and stores the map as a Map object 
// void MapLoader::parseMapFile() {
//     bool mapFlag = false;
//     bool continentFlag = false;
//     bool territoryFlag = false;
//     int cID = -1;
//     int tID = -1;
//     string lineText;
//     // Read from the text file
//     ifstream MyReadFile(this->inputFileName);
//     // Use a while loop together with the getline() function to read the file line by line
//     while (getline(MyReadFile, lineText)) {
//         if (lineText == "[Map]") {
//             mapFlag = true;
//             continue;
//         }
//         if (mapFlag) {
//             this->myMap = new Map();
//             mapFlag = false;

//         }
//         if (lineText != "[Continents]" && !continentFlag && !territoryFlag) {
//             continue;
//         }
//         if (lineText == "[Continents]") {
//             continentFlag = true;
//             continue;
//         }
//         if (continentFlag) {
//             cID++;
//             vector<string> lineTokens;
//             lineTokens = tokenizeString(lineText, '=');
//             if (lineText.empty()) {
//                 continentFlag = false;
//                 territoryFlag = true;
//                 continue;
//             }

//             toUpper(lineTokens[0]);
//             Continent* temp = new Continent(lineTokens[0], cID);
//             myMap->allContinent.push_back(temp);
//             myMap->continentIndexDictionary.insert(pair<string, int>(lineTokens[0], cID));
//             /* cout << "Information" << line[0] << cID << endl;*/
//         }

//             if (lineText == "[Territories]") {
//                 territoryFlag = true;
//                 continue;
//             }

//             if (territoryFlag) {
//                 if (lineText.empty()) {
//                     continue;
//                 }
//                 else {
//                     tID++;
//                 }
//                 vector<string> lineTokens;
//                 lineTokens = tokenizeString(lineText, ',');
//                 for( string token : lineTokens){
//                     toUpper(token);
//                 }
//                 Territory* temp = new Territory(lineTokens[0], lineTokens[3], tID);
//                 myMap->allTerritory.push_back(temp);
//                 myMap->territoryIndexDictionary.insert(pair<string, int>(lineTokens[0], tID));
//                 for (int i = 3; i < lineTokens.size(); i++) {
//                     temp->adjacentTerritoryMembers.push_back(lineTokens[i]);
//                 }
       
//             }
//         }

//         // Close the file
//         MyReadFile.close();
//     }

vector<string> MapLoader::splitStringForMap(string stringToSplit) {
    const char* delimeter = ",";
    vector<string> wordsInString;
    char* token = strtok(const_cast<char*>(stringToSplit.c_str()), delimeter);

    while(token != nullptr){
        wordsInString.push_back(string(token));
        token = strtok(nullptr,delimeter);
    }

    delete[] token;
    return wordsInString;

}

void MapLoader::createTerritory(string territoryString, Map *map) {
    if(territoryString == "\r"){
        return;
    }
    //We create the territory from the string in the file by splittin git and then using the constructor
    vector<string> territoryToVector = splitStringForMap(territoryString);
    // INSERT MICHAEL NEW CODE 
    int TerritoryID = stoi(territoryToVector[0]);
    int xCoordinate = stoi(territoryToVector[1]);
    int yCoordinate = stoi(territoryToVector[2]);
    string territoryInContinent = territoryToVector[3];
    vector<int> adjacentTerritories;
    for ( int i = 4; i < territoryToVector.size(); i++){
        adjacentTerritories.push_back(stoi(territoryToVector[i]));
    }
    string territoryName = "Territory" + TerritoryID; 
    Territory* newTerritory = new Territory(TerritoryID, xCoordinate, yCoordinate, territoryInContinent, adjacentTerritories);
    Territory* t;
    t = new Territory(stoi(territoryToVector[0]), stoi(territoryToVector[1]), stoi(territoryToVector[2]),territoryToVector[3], stoi(territoryToVector[4]));
    map->addTerritory(t);
    //then add the territory to continent
    Continent* c = map->getCID(t->getContinentID());
    c->addTerritory(t);

}

void MapLoader::createContinent(int *continentID, string continentString, Map *map) {
    if(continentString == "\r"){
        return;
    }
    //Create the continent and add it to the map
    vector<string> continentToVector = splitStringForMap(continentString);
    string name = continentToVector[0];
    vector<string> continentParams;
    string word= "";
    for (auto x : name){
        if(x == '='){
            continentParams.push_back(word);
            word = "";
        }
        else {
            word+= x;
        }    
    }
    continentParams.push_back(word);
    Continent* c;
    c = new Continent(*continentID, continentParams[0], stoi(continentParams[1]));
    map->addContinent(c);
    *continentID = *continentID + 1;
}

// void MapLoader::createAdjacentTerritoryMembers(string adjacentTerritoryMembers, Map *map) {
//     if(adjacentTerritoryMembers == "\r"){
//         return;
//     }
//     //First we split the string into the individual components, then get all the territories within
//     // the map, so we are able can add their adjacent territories

//     vector<string> adjacentTerritoriesToVector = splitStringForMap(adjacentTerritoryMembers);
//     vector<Territory*> mapTerritories = map->getAllTerritory();

//     //now we take the current territory and add each adjacent territory

//     Territory* territoryInMap = map->getTerritoryID(stoi(adjacentTerritoriesToVector[0]));
//     int adjacentTerritoryId;
//     for(int i = 1; i< adjacentTerritoriesToVector.size(); i++){
//         adjacentTerritoryId = stoi(adjacentTerritoriesToVector[i]);
//         territoryInMap->addAdjacentTerritoryMembers(map->getTerritoryID(adjacentTerritoryId));
//     }


//}