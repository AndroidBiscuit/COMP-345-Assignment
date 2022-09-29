#include "Map.h"
#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>
#include <stack>
#include<algorithm>
#include<vector>
#include <typeinfo>


//TERRITORY CLASS
Territory::Territory()
{
    tName = "";
    TID = 0;
    continentID = 0;
    playerID = 0;
    armyAmount = 0;
    xCoord = 0;
    yCoord = 0;

}
Territory::Territory(int TID, int xCoord, int yCoord, string tName, int continentID)
{
    this->tName = tName;
    this->TID = TID;
    this->xCoord = xCoord;
    this->yCoord = yCoord;
    this->continentID = continentID;
    this->playerID = 0;
    this->armyAmount = 0;

}
//ostream& operator<< (ostream& out, const Territory& t) {}

//copy constructor
Territory::Territory(Territory* t) {
    tName = t->getTName();
    TID = t->getTID();
    xCoord = t->getXCoord();
    yCoord = t->getYCoord();
    continentID = t->getContinentID();
    playerID = t->getPlayerID();
    armyAmount = t->getArmyAmount();
}
//assignment operator
Territory& Territory::operator=(Territory* t)
{
    this->tName = t->getTName();
    this->TID = t->getTID();
    this->xCoord = t->getXCoord();
    this->yCoord = t->getYCoord();
    this->continentID = t->getContinentID();
    this->playerID = t->getPlayerID();
    this->armyAmount = t->getArmyAmount();
    return *this;
}

// Territory::~Territory() {}
const string Territory::getTName() const { 
    return tName; 
}
const int Territory::getTID() const { 
    return TID; 
}
const int Territory::getContinentID() const { 
    return continentID; 
    }
const int Territory::getPlayerID() const {
     return playerID; 
     }
const int Territory::getXCoord() const{
    return xCoord;
}
const int Territory::getYCoord() const{
    return yCoord;
}

int Territory::getArmyAmount() { return armyAmount; }

void Territory::setTName(string tName)
{
    tName = tName;
}
void Territory::setTID(int tID)
{
    tID = tID;
}
const vector<Territory*> Territory::getAdjacentTerritoryMembers() const {
     return adjacentTerritoryMembers;
    }
string Territory::toString() {
    string territory;
    territory.append("Territory Name: "+ tName + ", ");
    territory.append("Territory ID: "+to_string(TID) + ", ");
    territory.append("Territory Continent ID: "+to_string(continentID));
    territory.append("Territory X Coordinate: "+ to_string(xCoord) + ", ");
    territory.append("Territory Y Coordinate: "+ to_string(yCoord));
    return territory;
}

void Territory::adjacentTerritoryMembersToString() {
    cout<<"Territory: " + to_string(TID) + "'s adjacentTerritories:"<<endl;
    for(auto& territory:adjacentTerritoryMembers){
        cout<<to_string(territory->TID)+ ", ";
    }
    cout<<endl;
}
//CONTINENT CLASS
Continent::Continent()
{
    cName = "";
    continentID = 0;
    numberOfTerritories = 0;
}
Continent::Continent(int continentID, string cName, int numberOfTerritories)
{
    this->cName = cName;
    this->continentID = continentID;
    this-> numberOfTerritories = numberOfTerritories;
}

//Copy Constructor 
Continent::Continent(Continent *c){
    continentID = c->getContinentID();
    cName = c->getCName();
    numberOfTerritories = c->getNumberOfTerritories();

}

Continent& Continent::operator=(Continent* c){
    this->continentID = c->getContinentID();
    this->cName = c->getCName(); 
    this -> numberOfTerritories = c-> getNumberOfTerritories();
}

const string Continent::getCName() const{ 
    return cName; 
    }
const int Continent::getContinentID() const{ 
    return continentID; 
    }
const int Continent:: getNumberOfTerritories() const{
    return numberOfTerritories; 
}

string Continent::toString() {
    string continent;
    continent.append("Continent Name: "+ cName + ", ");
    continent.append("Continent ID: " + to_string(continentID) + ", ");
    continent.append("Number of Territories: "+ to_string(numberOfTerritories));
    return continent;
}

Map::Map()
{
    allTerritory = vector<Territory*>() ;
    allContinent = vector<Continent*>() ;

}

Map::Map(Map* map){
    allTerritory = vector<Territory*>() ;
    allContinent = vector<Continent*>() ;
    for(auto &t: map ->allTerritory){
        allTerritory.push_back(new Territory(t));
    }
    for(auto &c: map ->allContinent){
        allContinent.push_back(new Continent(c));
    }

    addAdjacentTerritoryMembers(map->allTerritory);
}

Map& Map::operator =(Map* map){
    allTerritory = vector<Territory*>() ;
    allContinent = vector<Continent*>() ;
    for(auto &t: map ->allTerritory){
        allTerritory.push_back(new Territory(t));
    }
    for(auto &c: map ->allContinent){
        allContinent.push_back(new Continent(c));
    }

    addAdjacentTerritoryMembers(map->allTerritory);
}

void Map::addAdjacentTerritoryMembers(vector<Territory*> addTerritories){
    Territory* AddTerritories;
    for(int i = 0; allTerritory.size(); i++ ){
        for(int j = 0; j < addTerritories[i]->getAdjacentTerritoryMembers().size(); j++){
            AddTerritories = addTerritories[i]->getAdjacentTerritoryMembers()[j];
            allTerritory[i]->addAdjacentTerritoryMembers(AddTerritories);
        }
    }

}

void Map::addTerritory(Territory* t) {
    allTerritory.push_back(t);
}

void Map::addContinent(Continent* c) {
    allContinent.push_back(c);
}

vector<Territory*> Map::getAllTerritory() { 
    return allTerritory; 
}
vector<Continent*> Map::getAllContinent() { 
    return allContinent; 
}
void Map::setMapName(string mName)
{
    mName = mName;
}




// Map::Map(string mName)
// {
//     this->mName = mName;

// }

// string Map::getMName() { 
//     return mName; 
//     }
// string Map::getTerritoryNameFromTerritoryID(int tID)
// {
//     string tName = allTerritory[tID]->getTName(); 
//     return tName;
// };

// int Map::getTerritoryIDFromTName(string tName)
// {
//     std::map<string, int>::iterator it;
//     it = territoryIndexDictionary.find(tName);

//     return territoryIndexDictionary.find(tName)->second;
   
// }


// void Map::addEdge(vector<int> graph[], int source, int destination)
// {
//     graph[source].push_back(destination);
//     //Uncomment to check if edge has been added
//     /*string sourceTerritory = getTerritoryNameFromTerritoryID(source);
//     string destinationTerritory = getTerritoryNameFromTerritoryID(destination);
//     cout << "edge from " << sourceTerritory << " to " <<destinationTerritory << " has been added!" <<endl;
//     */
// }

// bool Map::edgeExistance(vector<int>graph[], int src, int destination) //Terrirtoy 1 points to adjacent territory 
// {
//     for (int i = 0; i < allTerritory.size(); i++)
//     {
//         for (auto x : graph[i])
//         {
//             if (src == i && destination == x)
//                 return true;
//         }
        
//     }
//     return false;
// }

bool Map::validate() {
    bool territoryGraph = true;
    bool continentSubGraph = true;
    bool territoryToOneContinent = true;
    //First Check if the territories are a connected graph
    vector<bool> visitedTerritories(allTerritory.size() + 1);
    vector<int> visitedContinent(allContinent.size() + 1);
    int countTerritories = 0;
    int countContinents = 0;

    dfsForTerritories(1,allTerritory[0],visitedTerritories);
    for (int i = 0; i < visitedTerritories.size(); ++i) {
        if (visitedTerritories[i])
            countTerritories++;
    }
    if(countTerritories != visitedTerritories.size() -1){
        cout<<"territories are not a graph"<<endl;
        return false;
    }else{
        cout<<"territories are graph"<<endl;
    }
    //set visited countries back to default
    visitedTerritories = vector<bool>(allTerritory.size() + 1);


    //Secondly Check territory subgraph
    for(int i = 0; i < allContinent.size(); i++){
        cout<<"checking territory subgraph"<<endl;
        countContinents = 0;

        for(int j = 0; j < allTerritory.size(); j++){
            if(allTerritory[j]->getContinentID() == allContinent[i]->getContinentID())
                countContinents++;
        }

        for(int j = 0; j< allTerritory.size(); j++){

            visitedTerritories = vector<bool>(allTerritory.size() + 1);
            visitedContinent[allContinent[i]->getContinentID()] = 0;

//If this does not work, set up a continent ID in the territory class ******* or look into comparing strings (string 1 = string 2)

            if(allTerritory[j]->getContinentID() == allContinent[i]->getContinentID()){
                dfsForContinentSubGraph(allTerritory[j]->getTID(), allContinent[i]->getContinentID(), allTerritory[j],visitedTerritories, visitedContinent);
                if(countContinents != visitedContinent[allContinent[i]->getContinentID()]){
                    continentSubGraph = false;
                    break;
                }

            }
        }

        if(continentSubGraph){
            cout<<"continent is valid subgraph"<<endl;
        }else{
            cerr<<"continent isn't valid subgraph"<<endl;
        }
    }


    //finally check all territories belong to one continent
    territoryToOneContinent = eachTerritoryToContinent();
    if(territoryToOneContinent == true){
        cout<<"all territories are to one continent"<<endl;
    }else{
        cerr<<"error not all territories are to one continent"<<endl;
    }


    if (territoryToOneContinent == true && territoryGraph == true && continentSubGraph == true){
        cout<<"Map is validated"<<endl;
        return true;
    }else{
        return false;
    }

}
bool Map::eachTerritoryToContinent() {
    vector<bool> count(allTerritory.size() + 1);
    for(int i = 1; i < count.size() + 1; i++){
        count[i] = false;
    }

    for(int i = 0; i < allTerritory.size(); i++){
        if(!count[allTerritory[i]->getTID()]){
            count[allTerritory[i]->getTID()] = true;

        }else {
            return false;
        }
    }
    return true;
}
void Map::dfsForTerritories(int id, Territory* t, vector<bool>& visitedTerritories){
    visitedTerritories[id] = true;
    int AdjacentTerritoryID;

    for(int i = 0; i < t->getAdjacentTerritoryMembers().size(); i++){
        AdjacentTerritoryID = t->getAdjacentTerritoryMembers()[i]->getTID();

        if(visitedTerritories[AdjacentTerritoryID] == false){
            dfsForTerritories(AdjacentTerritoryID,t->getAdjacentTerritoryMembers()[i] , visitedTerritories);
        }
    }
}

void Map::dfsForContinentSubGraph(int territoryID, int continentID, Territory *territory, vector<bool> &visitedTerritories,
                             vector<int> &subGraphCounter) {
    visitedTerritories[territoryID] = true;
    subGraphCounter[continentID]++;
    int AdjacentTerritoryID;
    int AdjacentContinentID;

    for(int i = 0; i < territory->getAdjacentTerritoryMembers().size(); i++){
        AdjacentTerritoryID = territory->getAdjacentTerritoryMembers()[i]->getTID();
        AdjacentContinentID = territory->getAdjacentTerritoryMembers()[i]->getContinentID();

        if(visitedTerritories[AdjacentTerritoryID] == false && continentID == AdjacentContinentID){
            dfsForContinentSubGraph(AdjacentTerritoryID, continentID, territory->getAdjacentTerritoryMembers()[i], visitedTerritories, subGraphCounter);
        }
    }

}

void Map::printGraph(vector<int> graph[])
{
    string territoryName;
    for (int v = 0; v < allTerritory.size(); ++v) {
        territoryName = getTerritoryNameFromTerritoryID(v);
        cout << "\n Adjacency list of territory " << territoryName <<endl;
        cout << "\n " <<v;
        for (auto x : graph[v])
            cout << "-> " << x;
        printf("\n");
    }
}