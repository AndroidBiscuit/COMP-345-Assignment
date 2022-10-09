#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class State {
public:
	State();

	State(const State& other);								/*Copy Constructor*/

	State& operator =(const State& other);					/*assignment operator*/

	friend ostream& operator << (ostream& out, const State& g);			/*Stream Insertion*/
	
	virtual ~State();

	virtual void state();									/*polymorphism state machine*/
	virtual void transition();
	virtual void command();
	static State* current;									/*current state pointer*/
	static State* loadmap, * validatemap, *start, *addplayer, *assigncountries, *issueorder, *endissueorders,
		*execorder, *win;									/*states*/
};
/*inheritance from state*/
class MapState : public State {								/*load map state*/
public:
	MapState();
	virtual ~MapState();
	void state();
	void transition();
	void command();
};

class ValidteMapState : public State {						/*validate map state*/
public:
	ValidteMapState();
	virtual ~ValidteMapState();
	void state();
	void transition();
	void command();
};

class StartState : public State {							/*Start State*/
public:
	StartState();
	virtual ~StartState();
	void state();
	void transition();
	void command();
};

class AddPlayersState : public State {						/*Add Players State*/
public:
	AddPlayersState();
	virtual ~AddPlayersState();
	void state();
	void transition();
	void command();
};

class AssignReinforcementState : public State {				/*AssignReinforcement State*/
public:
	AssignReinforcementState();
	virtual ~AssignReinforcementState();
	void state();
	void transition();
	void command();
};

class IssueOrdersState : public State {						/*Issue Order State*/
public:
	IssueOrdersState();
	virtual ~IssueOrdersState();
	void state();
	void transition();
	void command();
};

class ExecuteOrdersState : public State {					/*Execute Order State*/
public:
	ExecuteOrdersState();
	virtual ~ExecuteOrdersState();
	void state();
	void transition();
	void command();
};

class WinState : public State {								/*Win State*/
public:
	WinState();
	virtual ~WinState();
	void state();
	void transition();
	void command();
};

