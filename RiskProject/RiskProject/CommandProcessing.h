#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using std::string;
using std::ostream;
using std::vector;

class Command{

	string command;
	string effect;

public:
	//Constructor
	Command();
	Command(string command);
	Command(const Command& other);

	//Destructor
	~Command();

	//Accessor and mutator
	string getCommand();
	string getEffect();

	//Assignment operator
	Command& operator = (const Command& other);

	//Stream insertion
	friend ostream& operator << (ostream& out, const Command& c);

	//Method
	void saveEffect(string input);

};

class CommandProcessor {
private:
	vector<Command*> commands;

protected:
	//Method
	string readCommand();
	Command* saveCommand(string command);

public:
	//Constructor
	CommandProcessor();
	CommandProcessor(const CommandProcessor& other);

	//Destructor
	~CommandProcessor();

	//Accessor
	vector<Command*> getCommands();

	//Assignment operator
	CommandProcessor& operator =(const CommandProcessor& other);

	//Stream insertion
	friend ostream& operator << (ostream& out, const CommandProcessor& cp);

	//Method
	Command* processCommand();
	bool validate(string input, string currentState);


};