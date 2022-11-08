#include "CommandProcessing.h"

using std::cout;
using std::endl;
using std::cin;


//Command class
// Constructors
Command::Command(void) {
	command = "Default";
	effect = "Default";
}

Command::Command(string input) : command(input) {
}

Command::Command(const Command& other) {
	command = other.command;
	effect = other.effect;
}

// Destructor
Command::~Command(void) {
	cout << "Destroying a command object." << endl;
}

//Getter and Setter
string Command::getCommand(void) {
	return command;
}

string Command::getEffect(void) {
	return effect;
}

//Assignment operator
Command& Command::operator =(const Command& other) {
	command = other.command;
	effect = other.effect;
	return *this;
}

//Stream insertion
ostream& operator << (ostream& out, const Command& cmd) {
	out << "The command is " << cmd.command << " and the effect is " << cmd.effect << endl;
	return out;
}

//saves the effect of the command as a string
void Command::saveEffect(string input) {

	string theEffect;
	if (input == "loadmap") {
		theEffect = "Map has been successfully loaded.";
	}
	else if (input == "validatemap") {
		theEffect = "Map has been validated.";
	}
	else if (input == "addplayer") {
		theEffect = "The player has been added.";
	}
	else if (input == "gamestart") {
		theEffect = "Reinforcement has been assigned.";
	}
	else if (input == "replay") {
		theEffect = "The last game settings has been erased. Ready to take new settings.";
	}
	else if (input == "quit") {
		theEffect = "Program exits";
	}

	this->effect = theEffect;
}

//CommandProcessor class
//Constructor
CommandProcessor::CommandProcessor() {
	commands = vector<Command*>();
}

CommandProcessor::CommandProcessor(const CommandProcessor& other) {
	for (auto p : other.commands) {
		Command* temp = new Command(*p);
		commands.push_back(temp);
	}
}

//Destructor
CommandProcessor::~CommandProcessor(void) {

	cout << "Destroying CommandProcessor." << endl;
	for (auto p : commands) {
		delete p;
	}
	commands.clear();

}

//Accessor
vector<Command*>CommandProcessor::getCommands() {
	return commands;
};

//Assignment operator
CommandProcessor& CommandProcessor::operator =(const CommandProcessor& other) {
	for (auto p : other.commands) {
		Command* temp = new Command(*p);
		commands.push_back(temp);
	}
	return *this;
}

//Stream insertion
ostream& operator << (ostream& out, const CommandProcessor& cp) {
	for (Command* cmd : cp.commands) {
		out << "Command is " << cmd->getCommand() << endl;
		out << "Effect is " << cmd->getEffect() << endl;
	}
	return out;
}

//reads a string from the console
string CommandProcessor::readCommand(void) {
	string input;
	// get the whole line from user's input
	getline(cin, input);
	return input;
}

//saves the command in the list of commands
Command* CommandProcessor::saveCommand(string command) {
	Command* temp = new Command(command);
	commands.push_back(temp);
	return temp;
}

//reads and saves a command by the GameEngine
Command* CommandProcessor::processCommand()
{
	string input = readCommand();
	Command* temp = saveCommand(input);
	return temp;
}

//validates a given command in the current game engine
bool CommandProcessor::validate(string input, string currentState) {

	const string valid_commands[6] = { "loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit" };

	bool isValid = false;

	for (string cmd : valid_commands) {
		if (input == cmd)
			isValid = true;
	}

	if (!isValid) {
		cout << "This command is not valid in Warzone!" << endl;
		return false;
	}
	else {
		if (input == "loadmap") {
			if (currentState == "start" || currentState == "maploaded") {
				return true;
			}
		}
		else if (input == "validatemap") {
			if (currentState == "maploaded") {
				return true;
			}
		}
		else if (input == "addplayer") {
			if (currentState == "mapvalidated" || currentState == "playersadded") {
				return true;
			}
		}
		else if (input == "gamestart") {
			if (currentState == "playersadded") {
				return true;
			}
		}
		else if (input == "replay") {
			if (currentState == "win") {
				return true;
			}
		}
		else if (input == "quit") {
			if (currentState == "win") {
				return true;
			}
		}
	}

	cout << "It is a game command, but not valid in the current state" << endl;
	return false;
}
