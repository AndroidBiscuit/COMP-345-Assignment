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
	else {
		theEffect = input;
	}

	this->effect = theEffect;
	Notify(this);
}

// redefine the virtual method inherited from Subject class
string Command::stringToLog() {
	return "Current effect: " + effect;
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
	Notify(this);// When a command is read, it is written in the log file. When a command is executed, its effect is written in the log file.
	return temp;
}

//reads and saves a command by the GameEngine
Command* CommandProcessor::processCommand()
{
	string input = readCommand();
	Command* temp = saveCommand(input);
	return temp;
}

// This free function split a string to several components according to the delimiter
//source: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
vector<string> split(string s, string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}
//validates a given command in the current game engine
bool CommandProcessor::validate(Command* cmd, GameEngine* ge) {

	string currentState = ge->getState();

	const string valid_commands[6] = { "loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit" };

	bool isValid = false;

	vector<string> seperate_cmd = split(cmd->getCommand(), " ");
	string input = seperate_cmd[0];
	string parameter = "";
	if (seperate_cmd.size() == 2) {
		parameter = seperate_cmd[1];
	}

	for (string cmd : valid_commands) {
		if (input == cmd)
			isValid = true;
	}

	if (!isValid) {
		cout << "This command is not valid in Warzone!" << endl;
		return false;
	}
	else {
		//Start state: the loadmap command results in sucessfully loading a readable map, trasitioning to the maploaded state
		if (input == "loadmap") {
			if (currentState == "start" || currentState == "maploaded") {
				bool rest = ge->loadMap(parameter);
				if (rest) {
					cmd->saveEffect(input);
					ge->transition("maploaded");
				}
				else { cmd->saveEffect("loadmap error"); }
				return true;
			}
		}
		//Maploaded state: the validatemap command is used to validate the map. 
        //If successful, the game transitions to the mapValidated state
		else if (input == "validatemap") {
			if (currentState == "maploaded") {
				ge->getMap()->validate();
				if (ge->getMap()->getValid()) {
					cmd->saveEffect(input);
					ge->transition("mapvalidated");
				}
				else {
					cmd->saveEffect("validatemap error");
					ge->transition("start");
				}
					
				return true;
			}
		}
		//MapValidated state: the addplayer command is used to create players and insert them in the game (2-6 players). 
		else if (input == "addplayer") {
			if (currentState == "mapvalidated" || currentState == "playersadded") {
				if (ge->getPlayers().size() == 0) {
					ge->addPlayer(parameter);
					cmd->saveEffect(input);
					ge->transition("playersadded");
				}
				//checks number of players, only 2-6 are allowed
				else if (ge->getPlayers().size() < 6) {
					ge->addPlayer(parameter);
					cmd->saveEffect(input);
				}

				else {
					cout << "Players has been added. Please enter \"gamestart\"" << endl;
				}
				return true;
			}
		}

		else if (input == "gamestart") {
			if (currentState == "playersadded") {
				if (ge->getPlayers().size() > 1) {
					//fulfills the game start settings
					ge->gameStartSetting();
					cmd->saveEffect(input);
					ge->transition("assignreinforcement");
				}
				else {
					cmd->saveEffect("There are not enough players in the game to start yet.");
					cout << "There are not enough players in the game to start yet." << endl;
				}
				return true;
			}
		}
		else if (input == "replay") {
			if (currentState == "win") {
				ge->getPlayers().clear();
				delete ge->getMap();
				cmd->saveEffect(input);
				ge->transition("start");
				return true;
			}
		}
		else if (input == "quit") {
			if (currentState == "win") {
				cmd->saveEffect(input);
				ge->transition("exitprogram");
				return true;
			}
		}
	}

	cmd->saveEffect("It is a game command, but not valid in the current state");
	cout << "It is a game command, but not valid in the current state" << endl;

	return false;
}

// redefine the virtual method inherited from Subject class
string CommandProcessor::stringToLog() {
	return "Input command: " + commands.back()->getCommand();
}

// FileLineReader class
//Constructor
FileLineReader::FileLineReader() {
	fileName = "Default";
}

FileLineReader::FileLineReader(string fileName) {
	this->fileName = fileName;
}

FileLineReader::FileLineReader(const FileLineReader& other) {
	fileName = other.fileName;
}

//Destructor
FileLineReader::~FileLineReader(void) {
	cout << "Destroying FileLineReader." << endl;
}

//Assignment operator
FileLineReader& FileLineReader::operator =(const FileLineReader& other) {
	fileName = other.fileName;
	return *this;
}

//Stream insertion
ostream& operator << (ostream& out, const FileLineReader& f) {
	out << f.fileName << endl;
	return out;
}

// This method reads a file line by line
string FileLineReader::readLineFromFile(void) {

	ifstream input{};
	input.open(fileName);

	// check if the file is empty
	if (input.peek() == std::ifstream::traits_type::eof()) {
		cout << "The command file is empty!" << endl;
		exit(0);
	}
	string current;

	// get the first line of the file
	getline(input, current);
	input.close();

	// remove the first line from the file
	int count = 0;
	string line;
	ifstream inFile(fileName);
	ofstream outFile("removedfirstline.txt");
	while (getline(inFile, line)) {
		count++;
		if (count != 1) {
			outFile << line << "\n";
		}
	}
	inFile.close();
	outFile.close();

	// delete the original file
	remove("copy.txt");
	// change the file name of removeline.txt to copy.txt
	rename("removedfirstline.txt", "copy.txt");

	return(current);
}

// FileCommandProcessorAdapter class 

// Constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter() {
	fprocessor = new FileLineReader();
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* processor) {
	fprocessor = processor;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other) : CommandProcessor(other) {
	this->fprocessor = new FileLineReader(*other.fprocessor);
}

//Destructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
	cout << "Destroying FileCommandProcessorAdapter." << endl;
	delete fprocessor;
	fprocessor = nullptr;
}

//Assignment operator
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator =(const FileCommandProcessorAdapter& other) {
	CommandProcessor::operator = (other);
	this->fprocessor = new FileLineReader(*other.fprocessor);
	return *this;
}

//Stream insertion:
ostream& operator << (ostream& out, const FileCommandProcessorAdapter& fp) {
	out << fp.fprocessor << endl;
	return out;
}

// this class is inherited from CommandProcessor, so it can overwrite the processCommand() and change the input source from console to file
Command* FileCommandProcessorAdapter::processCommand() {
	// use adaptee object to read commands from a file
	string input = fprocessor->readLineFromFile();
	Command* temp = CommandProcessor::saveCommand(input);
	return temp;
}
