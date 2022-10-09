#include <iostream>
#include "GameEngine.h"
#include "GameEngineDriver.h"
using namespace std;

/*initialize static pointers, scope the variable*/
State* State::loadmap = new MapState();
State* State::validatemap = new ValidteMapState();
State* State::start = new StartState();
State* State::addplayer = new AddPlayersState();
State* State::assigncountries = new AssignReinforcementState();
State* State::issueorder = new IssueOrdersState();
State* State::execorder = new ExecuteOrdersState();
State* State::endissueorders = new ExecuteOrdersState();
State* State::win = new WinState();
State* State::current = State::start;

void testGameStates() {
	while (true) {
		State::current->state();
		State::current->transition();
		State::current->command();
		system("CLS");
	}
}



