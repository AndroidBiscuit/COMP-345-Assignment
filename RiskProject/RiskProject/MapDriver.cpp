#include "MapDriver.h"
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;
#include <cstdlib> // for exit function

void testLoadMaps() {

	//Extract data from .map file
	ifstream myFile;

	//if file couldn't be opened
	myFile.open("Canada1999");
	if (!myFile) {
		cerr << "Error: file could not be opened" << endl;
		exit(1);
	};

	if (myFile.is_open())
	{


	}

	myFile.close();
	
}