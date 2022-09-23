#include <iostream>
#include <fstream>
#include <string>
#include<map>
#include <sstream>
#include "MapLoader.h"
#include "Map.h"

//default constructor
MapLoader::MapLoader() {
    myMap = nullptr;
    inputFileName = "none";
}

//copy constructor
MapLoader::MapLoader(const MapLoader* ml) {
    myMap = ml->myMap;
    inputFileName = ml->inputFileName;
}

//two parameters constructor
MapLoader::MapLoader(Map* myMap, string fileName) {
    this->myMap = new Map();
    this->inputFileName = fileName;
    
}

//assignment operator
MapLoader& MapLoader::operator = (const MapLoader& ml) {
    this->myMap = ml.myMap;
    this->inputFileName = ml.inputFileName;
    return *this;
}

//stream insertion operator
ostream& operator<< (ostream& out, const MapLoader& m) {
    out << m.myMap << m.inputFileName << endl;
    return out;
}

//destructor
MapLoader::~MapLoader() {
    inputFileName.clear();
    delete myMap;
    myMap = NULL;
}

//accessor
string MapLoader::getInputFileName() {
    return inputFileName;
}

//mutator
void MapLoader::setInputFileName(const string& s) {
    inputFileName = s;
}

//splits the line information from the text file by certain delimiter
vector<string> MapLoader::tokenizeString(const string& s, char delimiter) {
    vector <string> tokens;                   // Vector of string to save tokens
    stringstream text(s);                     // stringstream class check1
    string token;                              
    while (getline(text, token, delimiter))  // Tokenizing by delimiter like '=', ','
    {
        tokens.push_back(token);
    }
    return tokens;
}

// captitalizes the first character of the name of Territories or continents
void MapLoader::toUpper(std::string& str) {
    if (str.length() == 0) {
        return;
    }

    str[0] = std::toupper(str[0]);
}


//reads the map file and stores the map as a Map object 
void MapLoader::parseMapFile() {
    bool mapFlag = false;
    bool continentFlag = false;
    bool territoryFlag = false;
    int cID = 0;
    int tID = 0;
    string lineText;
    // Read from the text file
    ifstream MyReadFile(this->inputFileName);
    // Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, lineText)) {
        if (lineText == "[Map]") {
            mapFlag = true;
            continue;
        }
        if (mapFlag) {
            this->myMap = new Map();
            mapFlag = false;

        }
        if (lineText != "[Continents]" && !continentFlag && !territoryFlag) {
            continue;
        }
        if (lineText == "[Continents]") {
            continentFlag = true;
            continue;
        }
        if (continentFlag) {
            cID++;
            vector<string> lineTokens;
            lineTokens = tokenizeString(lineText, '=');
            if (lineText.empty()) {
                continentFlag = false;
                territoryFlag = true;
                continue;
            }

            toUpper(lineTokens[0]);
            myMap->allContinent.push_back(new Continent(lineTokens[0],cID));
            myMap->continentIndexDictionary.insert(pair<Continent*, int>(new Continent(lineTokens[0], cID), cID));
            /* cout << "Information" << line[0] << cID << endl;*/
        }

            if (lineText == "[Territories]") {
                territoryFlag = true;
                continue;
            }

            if (territoryFlag) {
                if (lineText.empty()) {
                    continue;
                }
                else {
                    tID++;
                }
                vector<string> lineTokens;
                lineTokens = tokenizeString(lineText, ',');
                for( string token : lineTokens){
                    toUpper(token);
                }
                Territory* temp = new Territory(lineTokens[0], lineTokens[3], tID);
                myMap->allTerritory.push_back(temp);
                myMap->territoryIndexDictionary.insert(pair<Territory*, int>(temp, cID));
                for (int i = 3; i < lineTokens.size(); i++) {
                    temp->adjacentTerritoryMembers.push_back(lineTokens[i]);
                }
       
            }
        }

        // Close the file
        MyReadFile.close();
    }
