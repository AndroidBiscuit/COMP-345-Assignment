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
	if (input == "tournament") {
		theEffect = "Tournament mode is active.";
	}
	else if (input == "loadmap") {
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

	cout << "Destroying Command Processor." << endl;
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

	const string valid_commands[7] = {"tournament", "loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit" };

	bool isValid = false;

	vector<string> seperate_cmd = split(cmd->getCommand(), " ");
	vector<string> tournament_parameters;
	string input = seperate_cmd[0];
	string parameter = "";
	string playerStrategy = "";
	if (seperate_cmd.size() == 2) {
		parameter = seperate_cmd[1];
	}

	if (seperate_cmd.size() == 3) {
		parameter = seperate_cmd[1];
		playerStrategy = seperate_cmd[2];
	}

	if (seperate_cmd.size() > 3) {
		tournament_parameters = seperate_cmd;
	
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
		if (input == "tournament") {
			if (currentState == "start") {
				cmd->saveEffect(input);
				processTournamentCommand(tournament_parameters);
				bool isValid = validateTournamentParameters();
				if (!isValid) {
					cout << "The tournament parameters are not valid. Quit! " << endl;
					exit(0);
				}
				//Map files are loaded and validated as a result of executing a tournament command.
				for (int i = 0; i < listOfMapFiles.size(); i++) {

					//load maps 
					cout << "\n Loading Map " << i + 1 << endl;
					bool result = ge->loadMap(listOfMapFiles[i]);

					//if one of the map files cannot be loaded, print out the reason and exit game
					if (!result) {
						cout << listOfMapFiles[i] << " is an invalid file." << " Exit Game." << endl;
						exit(0);
					}
					else {
						ge->transition("maploaded");
						ge->getMap()->validate();
						if (!ge->getMap()->getValid()) {
							cout << listOfMapFiles[i] << " is an invalid map." << " Exit Game." << endl;
							exit(0);
						}
						ge->transition("mapvalidated");

						//play the game with the same setting for G(1-5) times
						for (int j = 0; j < numOfGames; j++) {

							//addplayers to GameEngines's data members players, players' name is the strategy they use
							for (int i = 0; i < listOfPlayerStrategies.size(); i++) {
								string name = listOfPlayerStrategies[i];
								if (name == "Neutral") {
									ge->addPlayer("Neutral2", name);
								}
								else {
									ge->addPlayer(name, name);
								}

							}
							//Game starts
							ge->gameStartSetting();
							ge->transition("assignreinforcement");
							ge->mainGameLoop(maxNumOfTurns);
							ge->clearPlayers();

							//if the tournament is not finished, go to mapvalidated, otherwise, exit program
							if (i == listOfMapFiles.size() - 1 && j == numOfGames - 1)
								ge->transition("exitprogram");
							else
								ge->transition("mapvalidated");
						}
					}

					//save the result of current map
					ge->winnersForTournament.push_back(ge->winnerForEachMap);

					//clear the data of winnerForEachMap to save next map's result
					ge->clearWinnerForEachMap();
				}
				//print the whole tournament result
				string outputRes = "";
				outputRes = "Tournament mode:\nM: ";
				for (string s : listOfMapFiles) {
					outputRes += s + "\t";
				}
				outputRes += "\nP: ";
				for (string s : listOfPlayerStrategies) {
					outputRes += s + "\t";
				}
				outputRes += "\nG: ";
				outputRes += to_string(numOfGames);
				outputRes += "\nD: ";
				outputRes += to_string(maxNumOfTurns);

				outputRes += "\nResults: \n";
				outputRes += "\t";
				for (int i = 0; i < numOfGames; i++) {
					outputRes += "Game " + to_string(i + 1) + "\t";
				}
				outputRes += "\n\n";
				for (int i = 0; i < ge->winnersForTournament.size(); i++) {
					outputRes += "Map " + to_string(i + 1) + "\t";
					for (int j = 0; j < ge->winnersForTournament[0].size(); j++) {
						outputRes += ge->winnersForTournament[i][j] + "\t";
					}
					outputRes += "\n\n";
				}
				cout << outputRes;
				ge->setOutputResults(outputRes);
				Notify(this);
				return true;
			}
				
		}

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
					if (playerStrategy == "Human") {
						ge->hasHumanPlayer = true;
					}
					ge->addPlayer(parameter, playerStrategy);
					cmd->saveEffect(input);
					ge->transition("playersadded");
				}
				//checks number of players, only 2-6 are allowed
				else if (ge->getPlayers().size() < 6) {
					if (playerStrategy == "Human") {
						ge->hasHumanPlayer = true;
					}
					ge->addPlayer(parameter, playerStrategy);
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

//process the tournament command and extract the parameters
void CommandProcessor::processTournamentCommand(vector<string> parameters) {
	int i = 1; // start from parameters after "tournament"
	while (i < parameters.size()) {
		if (parameters[i] == "M") {
			while (parameters[++i] != "P") {
				listOfMapFiles.push_back(parameters[i]);
			
			}
		}
		else if (parameters[i] == "P") {
			while (parameters[++i] != "G") {
				listOfPlayerStrategies.push_back(parameters[i]);
			}
		}
		else if (parameters[i] == "G") {
			i++;
			string temp;
			temp = parameters[i++];
			if (!isdigit(temp[0])) {
				cout << "The number of games should be an integer." << endl;
				exit(0);
			}
			numOfGames = stoi(temp);
		}
		else if (parameters[i] == "D") {
			i++;
			string temp;
			temp = parameters[i++];
			if (!isdigit(temp[0])) {
				cout << "The max number of turns should be an integer." << endl;
				exit(0);
			}
			maxNumOfTurns = stoi(temp);
		}
	}
    //print the results
	cout << "List of Map files:" << endl;
	for (string s : listOfMapFiles)
		cout << s << '\t';
	cout << endl;
	cout << "List of Player Strategies:" << endl;
	for (string s : listOfPlayerStrategies)
		cout << s << '\t';
	cout << endl;
	cout << "Number of Games: " << numOfGames << endl;
	cout << "Max number of Turns: " << maxNumOfTurns << endl;
}

//validates tournament parameters
bool CommandProcessor::validateTournamentParameters() {
	bool isValid = true;
	if (listOfMapFiles.size() < 1 || listOfMapFiles.size() > 5) {
		cout << "Please enter 1-5 map files" << endl;
		isValid = false;
	}
	if (listOfPlayerStrategies.size() < 2 || listOfPlayerStrategies.size() > 4) {
		cout << "Please enter 2-4 player strategies" << endl;
		isValid = false;
	}
	if (numOfGames < 1 || numOfGames > 5) {
		cout << "Please enter a number between 1 and 5 for number of games" << endl;
		isValid = false;
	}
	if (maxNumOfTurns < 10 || maxNumOfTurns > 50) {
		cout << "Please enter a number between 10 and 50 for max number of turns" << endl;
		isValid = false;
	}

	// validate strategy
	string strategy[4] = { "Aggressive" , "Benevolent" , "Neutral", "Cheater" };
	bool isStrategyValid = true;
	for (int i = 0; i < listOfPlayerStrategies.size(); i++) {
		if (listOfPlayerStrategies[i] != strategy[0] && listOfPlayerStrategies[i] != strategy[1] && listOfPlayerStrategies[i] != strategy[2] && listOfPlayerStrategies[i] != strategy[3])
			isStrategyValid = false;
	}



	if (!isStrategyValid) {
		cout << "At least one of the player Strategies entered is invalid!" << endl;
		isValid = false;
	}

	return isValid;

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
