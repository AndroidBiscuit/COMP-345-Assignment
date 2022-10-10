// MainDriver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MapDriver.h"
#include "PlayDriver.h"
#include "OrdersDriver.h"
#include "GameEngineDriver.h"
#include "CardsDriver.h"
#include <iostream>
using std::cout;
using namespace std;


int main()
{
    bool round = true;
    while (round) {
        system("CLS");
        cout << "\n-------------------Test Menu-----------------------------" << endl;
        cout << "1. Start to load the map.\n";
        cout << "2. Start to set the player.\n";
        cout << "3. Start to handle the orderslists.\n";
        cout << "4. Start to set the cards.\n";
        cout << "5. Start to test Game Engine.\n";
        cout << "\nPlease input your choice: ";
        int opt;
        cin >> opt;

        switch (opt) {
        case 1:
            testLoadMaps();
            continue;
        case 2:
            testPlayers();
            continue;
        case 3:
            testOrdersLists();
            system("pause");
            continue;
        case 4:
            testCards();
            continue;
        case 5:
            testGameStates();
            round = false;

        default:
            round = false;
        }
        
    }
    

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
