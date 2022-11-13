#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "GameEngine.h"
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include "LoggingObserver.h"

using std::string;
using std::ostream;
using std::vector;

class GameEngine;

class Command : public Subject{

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

	//Method
	virtual string stringToLog();

};

class CommandProcessor : public Subject {
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
	bool validate(Command* cmd, GameEngine* ge);
	virtual string stringToLog();

};

class FileLineReader {
	string fileName;

public:
	//constructor
	FileLineReader();
	FileLineReader(string fileName);
	FileLineReader(const FileLineReader& other);

	//Destructor
	~FileLineReader();

	//Assignment operator
	FileLineReader& operator =(const FileLineReader& other);

	//Stream insertion
	friend ostream& operator << (ostream& out, const FileLineReader& f);

	//Method
	virtual string readLineFromFile(void);

};

// The target is CommandProcessor which reads commands from the console
// The adaptee is FileCommandProcessor that reads commands from a file
// FileCommandProcessorAdapter is the adapter
class FileCommandProcessorAdapter : public CommandProcessor {

	// addptee class object
	FileLineReader* fprocessor;

public:
	//Constructor
	FileCommandProcessorAdapter();
	FileCommandProcessorAdapter(FileLineReader* processor);
	FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other);

	//Destructor
	~FileCommandProcessorAdapter();

	Command* processCommand(void);

	//Assignment operator
	FileCommandProcessorAdapter& operator =(const FileCommandProcessorAdapter& other);

	//Stream insertion:
	friend ostream& operator << (ostream& out, const FileCommandProcessorAdapter& fp);
};
