#include "OrdersCardsPlayerTest.h"
#include "Player.h"
#include "Map.h"


void testPlayers() {
	vector <Player*> players;
	int n = -1;
	bool round = true;
	string result;

	//creating necessary objects for demostration

	vector <Territory*> territories;
	

	Territory* t1 = new Territory(1, 1, "Vancouver Island");
	Territory* t2 = new Territory(2, 1, "Queen Charlotte Islands");
	Territory* t3 = new Territory(5, 2, "Iqualuit");
	Territory* t4 = new Territory(6, 2, "South Baffin Isle");
	Territory* t5 = new Territory(22, 3, "Fort Smith");
	Territory* t6 = new Territory(23, 3, "Yellowknife");


	territories.push_back(t3);
	territories.push_back(t4);
	

	Card* c1 = new Card("bomb");
	Card* c2 = new Card("airlift");
	


	cout << "Welcome to Warzone!" << endl;
	cout << "This is the Player creation menu." << endl;
	while (n < 1) {
		cout << "Please enter the number of desired players. " << endl;
		cout << "The number should be greater than or equal to one." << endl;
		cin >> n;
	}


	//Creating Player Objects:
	for (int i = 0; i < n; i++)
	{
		Player* temp = new Player();
		string name;
		cout << "Player " << (i + 1) << " - Enter Player's name: " << endl;
		cin >> name;
		(*temp).setName(name);
		cout << "Welcome to Warzone, " << name << "!" << endl;
		players.push_back(temp);
	}

	cout << "All players have been added! Here is who will be playing:" << endl;
	for (Player* p : players) {
		cout << "Player " << p->getPlayerID() << " - " << p->getName() << endl;
	}

	//Demonstrating copy constructor functionality:
	cout << "----------------------------------------------" << endl;
	cout << "Creating a Player using its copy constructor: " << endl;
	Player* copiedPlayer = new Player(*players[0]);
	copiedPlayer->setPlayerID(102);
	cout << "Player " << copiedPlayer->getPlayerID() << " - " << copiedPlayer->getName() << endl;
	players[0]->addTerritory(t1);
	players[0]->addTerritory(t2);
	players[0]->addCard(c1);
	players[0]->addCard(c2);
	cout << "----------------------------------------------" << endl;
	cout << "Issuing orders for Players:" << endl;
	//Issuing orders for example Player:
	for (auto p : players) {
		cout << "Player " << p->getPlayerID() << " - " << p->getName() << endl;
		round = true;
		while (round) {
			p->issueOrder();
			cout << "Would you like to issue more orders? Y/N" << endl;
			cin >> result;
			while (result != "N" && result != "n" && result != "y" && result != "Y") {
				cin >> result;
			}
			if (result == "N" || result == "n") {
				round = false;
			}
		}
		cout << *p << endl;
	}
	cout << "----------------------------------------------" << endl;
	//Demonstrating toAttack():
	cout << "Player " << players[0]->getPlayerID() << " - " << players[0]->getName() << endl;
	cout << "Territories to Attack:" << endl;
	players[0]->toAttack(territories);
	cout << endl;
	cout << "----------------------------------------------" << endl;
	//Demonstrating toDefend():
	cout << "Player " << players[0]->getPlayerID() << " - " << players[0]->getName() << endl;
	cout << "Territories to Defend:" << endl;
    players[0]->toDefend();
	cout << endl;
	cout << "----------------------------------------------" << endl;
	//Comparing the copied Players:
	cout << "Comparing the copied Players:" << endl;
	cout << *players[0] << endl;
	cout << *copiedPlayer << endl;
	cout << "----------------------------------------------" << endl;
	//Creating a copy using the assignment operator:
	if (players.size() > 1) {
		players[1]->addTerritory(t5);
		players[1]->addTerritory(t6);
		Player temp2;
		temp2 = *players[1];
		cout << "Creating a copy using the assignment operator:" << endl;
		cout << *players[1] << endl;
		cout << temp2 << endl;
	}
	cout << "----------------------------------------------" << endl;
	cout << "Releasing the memory:" << endl;
	if (copiedPlayer) {
		delete copiedPlayer;
		copiedPlayer = NULL;
	}
	for (Player* p : players) {
		if (p != nullptr) {
			delete p;
		}
	}
	for (Territory* p : territories) {
		if (p != nullptr) {
			delete p;
		}
	}

}