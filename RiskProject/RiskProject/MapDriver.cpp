#include "MapDriver.h"
#include "Map.h"
#include <iostream>
#include<string>
using std::cerr;
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;
#include <cstdlib> // for exit function



void testLoadMaps() {

	cout << "Welcome to Warzone!" << endl;
	cout << "This driver demonstrates the functionality of the Maps" << endl;


	int numberOfMaps = -1;
	string fileName = "Japan.map";
	MapLoader load;
	Map* created = nullptr;
	vector<Map*> mapsCreated;


	/*while (numberOfMaps < 1) {
		cout << "Please enter the number of Map files to be read. Number must be greater than zero." << endl;
		cin >> numberOfMaps;
	}
	for (int i = 0; i < numberOfMaps; i++) {
		cout << "Enter the name of the Map file you would like to read. Do not forget to add the extension." << endl;
		cin >> fileName;*/
		try {
			created = load.loadMap(fileName);
			mapsCreated.push_back(created);
			int sum = 0;
			for (Territory* p : created->getAllTerritory()) {
				sum++;
			}
			cout << "Territories placed: " << sum << endl;
		}
		catch (const invalid_argument& e) {
			cout << "The map file provided was invalid. " << endl;
		}
	/*}*/
	system("pause");
	/*for (auto p : mapsCreated) {
		delete(p);
	}*/
	
}
