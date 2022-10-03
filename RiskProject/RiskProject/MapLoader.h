#pragma once
#include "Map.h"

class MapLoader {
private :
	string inputFileName;               
	Map loadedMap;

public:
	// stream insertion operator
	friend ostream& operator<< (ostream& out, const MapLoader& m); 

	//constuctors
	MapLoader();                       
	MapLoader(const MapLoader*);     

	friend class Map;

	//assigment operator
	MapLoader& operator= (const MapLoader&);  

	//destructor
	~MapLoader();         
	//accessor
	string getInputFileName();   
	//mutator
	void setInputFileName(const string&);        

	vector<string> tokenizeString(const string&, char); //tokenizes the line information from the text file by certain delimiter
	int getCID(Map*,string cName); //gets the continent ID by given continent name
	int getTID(Map*, string tName);//gets the territory ID by given territory name

	Map* getMap();
	Map* loadMap(string mapFile);

};




