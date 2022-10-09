#include "GameEngine.h"

State::State() {}

State::~State() {}

void State::state() {}
void State::transition() {}
void State::command() {}
/*------------------------------------------------------------------StartState---------*/
StartState::StartState() {}

StartState::~StartState() {}
void StartState::state() {
	system("CLS");
	cout << "Welcome to Warzone Game!" << endl;
	cout << "This is Start State." << endl;
}
void StartState::transition() {
	current = loadmap;												/*current pointer to loadmap*/
}
void StartState::command() {
	cout << "Process to load map state..." << endl;
}

/*-------------------------------------------------------------MapState-----*/

MapState::MapState() {}

MapState::~MapState() {}

void MapState::state() {
	cout << "This is loadmap state" << endl;
	cout << "Please input (loadmap) to load  map or (validatemap) to validte map" << endl;
}

void MapState::transition() {
	string input;
	cin >> input;
	if (input == "loadmap") {
		cout << "map was loaded." << endl;
		current = loadmap;
	}
	else if (input == "validatemap") {
		current = validatemap;
	}
	else {
		cout << "Invalid command, please enter (loadmap) or (validatemap)." << endl;
	}
}

void MapState::command() {
	system("pause");
}

/*-------------------------------------------------------------------ValidteMapState----------*/
ValidteMapState::ValidteMapState() {}

ValidteMapState::~ValidteMapState() {}

void ValidteMapState::state() {
	cout << "This is validatemap state" << endl;

}
void ValidteMapState::transition() {
	cout << "Validated Map(s)." << endl;
	cout << "Input (addplayer) to state add player State" << endl;
	string input;
	cin >> input;

	if (input == "addplayer") {
		current = addplayer;
	}
	else {
		cout << "Invalid command, please input (addplayer)." << endl;
	}

}
void ValidteMapState::command() {
	system("pause");
}
/*------------------------------------------------------------AddPlayersState---------*/

AddPlayersState::AddPlayersState() {}

AddPlayersState::~AddPlayersState() {}
void AddPlayersState::state() {
	cout << "This is AddPlayers State" << endl;
	cout << "Please input (addplayer) to add player or (assigncountries) to assign reinforcement:" << endl;
}
void AddPlayersState::transition() {
	string input;
	cin >> input;
	if (input == "addplayer") {
		cout << "Player Added" << endl;
		current = addplayer;
	}
	else if (input == "assigncountries") {
		current = assigncountries;
	}

	else {
		cout << "Invalid command, please input (addplayer) or (assigncountries)." << endl;

	}
}
void AddPlayersState::command() {
	system("pause");
}

/*---------------------------------------------------------------------AssignReinforcementState-------*/
AssignReinforcementState::AssignReinforcementState() {}

AssignReinforcementState::~AssignReinforcementState() {}
void AssignReinforcementState::state() {
	cout << "This is AssignReinforcement State" << endl;
	cout << "Reinforcement assigned" << endl;
	cout << "Please input (issueorder) to assign reinforcement:" << endl;
}
void AssignReinforcementState::transition() {
	string input;
	cin >> input;
	if (input == "issueorder") {
		current = issueorder;
	}
	else {
		cout << "Invalid command, please input (issueorder) to issue order." << endl;
	}

}
void AssignReinforcementState::command() {
	system("pause");
}
/*-------------------------------------------------------------------------IssueOrdersState----------*/
IssueOrdersState::IssueOrdersState() {}

IssueOrdersState::~IssueOrdersState() {}
void IssueOrdersState::state() {
	cout << "This is Issue Orders State" << endl;
	cout << "Please input (issueorder) to issue order or (endissueorders) to end issue order:" << endl;
}
void IssueOrdersState::transition() {
	string input;
	cin >> input;
	if (input == "issueorder") {
		cout << "Order issued" << endl;
		current = issueorder;
	}
	else if (input == "endissueorders") {
		current = endissueorders;
	}
	else {
		cout << "invalid command, please input (issueorder) or (endissueorders)." << endl;
	}

}
void IssueOrdersState::command() {
	system("pause");
}

/*-------------------------------------------------------------------------------ExecuteOrdersState-------------*/

ExecuteOrdersState::ExecuteOrdersState() {}

ExecuteOrdersState::~ExecuteOrdersState() {}
void ExecuteOrdersState::state() {
	cout << "This is Execute Orders State" << endl;
	cout << "Please state (execorder) to execute order or (endexecorders) to end execute order:" << endl;
	cout << "If there's winner please enter (win)." << endl;
}
void ExecuteOrdersState::transition() {
	string input;
	cin >> input;
	if (input == "execorder") {
		cout << "Order Executed" << endl;
		current = execorder;
	}
	else if (input == "endexecorders") {
		current = assigncountries;
	}
	else if (input == "win") {
		current = win;
	}
	else {
		cout << "Invalid command, please input (execorder) or (endexecorders) or (win)." << endl;
	}

}
void ExecuteOrdersState::command() {
	system("pause");
}
/*--------------------------------------------------------------------WinState---*/
WinState::WinState() {}

WinState::~WinState() {}
void WinState::state() {
	cout << "This is Win State" << endl;
	cout << "Please input (end) to end game or (play) to start another game:" << endl;
}
void WinState::transition() {
	string input;
	cin >> input;
	if (input == "end") {
		cout << "Thnanks for playing, see you next time!" << endl;
		exit(0);
	}
	else if (input == "play") {
		current = start;
	}
	else {
		cout << "Invalid command, please input (end) or (play)." << endl;
	}

}
void WinState::command() {
	system("pause");
}
