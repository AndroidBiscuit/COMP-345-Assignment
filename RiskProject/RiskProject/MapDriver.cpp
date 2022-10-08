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


	//int numberOfMaps = -1;
	string fileName1 = "Japan.map";
	string fileName2 = "Canada.map";
	string fileName3 = "Invalid1.map";
	string fileName4 = "Invalid2.map";
    
	MapLoader* load = new MapLoader();


	try{
		
		load->loadMap(fileName1);
		load->loadMap(fileName2);
		load->loadMap(fileName3);
		
	}
	catch (const invalid_argument& e) {
		cout << "The map file provided was invalid. " << endl;
	}

	try{
		load->loadMap(fileName4);
	}
	catch (const invalid_argument& e) {
		cout << "The map file provided was invalid. " << endl;
	}


	system("pause");
	
	delete load;
	
	
	
}
