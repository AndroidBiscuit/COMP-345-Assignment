#include <iostream>
#include "GameEngine.h"

using namespace std;


GameEngine::GameEngine()		
{
	state = "startState";									/*set first state as startState*/
}

GameEngine::GameEngine(const GameEngine& other)
{
	state = other.state;
}

void GameEngine::setState(string currentState)
{
	state = currentState;
}

string GameEngine::getState()
{
	return state;
}

GameEngine& GameEngine::operator =(const GameEngine& other) {
	state = other.state;
	return *this;
}

istream& operator>>(istream& in, GameEngine& ge)
{
	in >> ge.state;
	return in;
}

ostream& operator<<(ostream& out, const GameEngine& ge)
{
	out << ge.state << endl;
	return out;
}


int GameEngine::gameStates(int i)
{
	string input;
	switch (i) {
	case 0:
		cout << "Welcome to Warzone!" << endl;										/*start state*/
		cout << "This is " << getState() << " State." << endl << endl;
		system("pause");
		return ++i;

	case 1:																			/*loadmap state*/
		system("CLS");
		cout << "Input (loadmap) to load map(s)." << endl;
		cin >> input;
		if (input == "loadmap") {
			setState("load map");
			return ++i;
		}
		else {
			cout << "Invalid input, please input (loadmap)." << endl << endl;
			system("pause");
			return i;
		}
		break;

	case 2:																			/*validate map state*/
		cout << "Input (loadmap) to load map or input (validatemap) to validate map(s)." << endl;
		cout << "This is " << getState() << " State." << endl << endl;
		cin >> input;
		if (input == "loadmap") {
			setState("load map");
			cout << "Map Loaded" << endl;
			system("pause");
			return i;
		}
		else if (input == "validatemap") {
			setState("validate map");
			cout << "This is " << getState() << " State." << endl << endl;
			cout << "Map is valid" << endl;
			system("pause");
			return ++i;
		}
		else {
			cout << "Invalid input, please input (loadmap) or (validatemap)." << endl << endl;
			system("pause");
			return i;
		}
		break;

	case 3:																			/*add player state*/
		cout << "Input (addplayer) to add player(s)" << endl;
		cin >> input;
		if (input == "addplayer") {
			setState("add player");
			return ++i;
		}
		else {
			cout << "Invalid input, please input (addplayer)." << endl << endl;
			system("pause");
			return i;
		}
		break;

	case 4:																			/*add player state to add reinforcement state*/
		cout << "Input (addplayer) to add player(s) or (assigncountries) to add reinforcement" << endl;
		cout << "This is " << getState() << " State." << endl << endl;
		cin >> input;
		if (input == "addplayer") {
			setState("add player");
			cout << "Player added" << endl;
			system("pause");
			return i;
		}
		else if (input == "assigncountries") {
			setState("assign reinforcement");
			cout << "This is " << getState() << " State." << endl << endl;
			system("pause");
			return ++i;
		}
		else {
			cout << "Invalid input, please input (addplayer)." << endl << endl;
			system("pause");
			return i;
		}
		break;

	case 5:																		/*add reinforcement state*/
		cout << "Input (assigncountries) to add reinforcement" << endl;
		cout << "This is " << getState() << " State." << endl << endl;
		cin >> input;
		 if (input == "assigncountries") {
			setState("assign reinforcement");
			cout << "reinforcement added" << endl;
			system("pause");
			return ++i;
		}
		else {
			cout << "Invalid input, please input (addplayer)." << endl << endl;
			system("pause");
			return i;
		}
		break;

	case 6:																		/*issueorder state*/
		cout << "Input (issueorder) to issue order" << endl;
		cin >> input;
		if (input == "issueorder") {
			setState("Issue Orders");
			return ++i;
		}
		else {
			cout << "Invalid input, please input (issueorder)." << endl << endl;
			system("pause");
			return i;
		}
		break;

	case 7:																	/*issueorder state to execute order state*/
		cout << "Input (issueorder) to issue order or (endissueorders) to execute order" << endl;
		cout << "This is " << getState() << " State." << endl << endl;
		cin >> input;
		if (input == "issueorder") {
			cout << "order issued" << endl;
			system("pause");
			return i;
		}
		else if (input == "endissueorders") {
			setState("execute orders");
			return ++i;
		}
		else {
			cout << "Invalid input, please input (issueorder)." << endl << endl;
			system("pause");
			return i;
		}
		break;

	case 8:																								/*execute order state to add reinforcement state or win state*/
		cout << "Input (execorder) to execute order or (endexecorders) to assign reinforcement."<< endl;
		cout << "Or input (win)." << endl;
		cout << "This is " << getState() << " State." << endl << endl;
		cin >> input;
		if (input == "execorder") {
			cout << "order executed" << endl;
			system("pause");
			return i;
		}
		else if (input == "endexecorders") {
			setState("assign reinforcement");
			return 5;
		}
		else if (input == "win") {
			setState("Win");
			return ++i;
		}
		else {
			cout << "Invalid input, please input (execorder) or (endexecorders) or (win)." << endl << endl;
			system("pause");
			return i;
		}
		break;

	case 9:																				/*win state to end or player again*/
		cout << "Input (play) to start another game or (end) to exit." << endl;
		cin >> input;
		if (input == "play") {
			setState("Start");
			cout << "This is " << getState() << " State." << endl << endl;
			system("pause");
			return (i = 0);
		}
		else if (input == "end") {
			setState("End");
			cout << "This is " << getState() << " State. Thank you!" << endl << endl;
			system("pause");
			return -1;
		}
		else {
			cout << "Invalid input, please input (play) or (end)." << endl << endl;
			system("pause");
			return i;
		}
		break;
	}
}

