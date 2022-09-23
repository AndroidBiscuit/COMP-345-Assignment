#pragma once
#include "Map.h"

class MapLoader {
private :
	
	string inputFileName;               //input file path

public:
	Map* myMap;                         // a map object (pointer)
	friend ostream& operator<< (ostream& out, const MapLoader& m); // stream insertion operator

	MapLoader();                       //default constructor
	MapLoader(const MapLoader*);        //copy constructor
	MapLoader(Map*, string);            //two parameter constructor
	MapLoader& operator= (const MapLoader&);   //assigment operator
	~MapLoader();                          //destructor
	string getInputFileName();          //accessor
	void setInputFileName(const string&);            //mutator

	vector<string> tokenizeString(const string&, char); //tokenizes the line information from the text file by certain delimiter
	void toUpper(string& str); // captitalizes the first character of the name of Territories or continents
	void parseMapFile();               //reads the map file and stores the map as a Map object 

};


