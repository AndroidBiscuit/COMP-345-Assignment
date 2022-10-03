// MainDriver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MapDriver.h"
#include "PlayDriver.h"
#include <iostream>
using std::cerr;
using std::cout;
using namespace std; 
using std::endl;
using std::ifstream;
#include <cstdlib> // for exit function
#include <fstream> // reading a text file
#include <string>
#include <sstream>


int main()
{
    //std::cout << "Start to load the map.\n";

    //testLoadMaps();

   std::cout << "Start to set the player.\n";

    testPlayers();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
