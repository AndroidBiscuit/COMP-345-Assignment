#include "CommandProcessing.h"
#include "GameEngine.h"
using std::cout;
using std::endl;

void testCommandProcessor() {
	bool isValid{};
	GameEngine* currentGame = new GameEngine();
	CommandProcessor* processor = new CommandProcessor();
	string currentState = currentGame->getState();
	cout << *currentGame << endl;
	bool round = true;
	string result;
	
	while(round) {
		cout << "Enter your command: " << endl;
		Command* cmd1 = processor->processCommand();
		isValid = processor->validate(cmd1, currentGame);
		cout << "Would you like to use continue test the command? Y/N" << endl;
		cin >> result;
		while (result != "N" && result != "n" && result != "Y" && result != "y") {
			cin >> result;
		}
		if (result == "N" || result == "n") {
			round = false;
			
		}
		
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	

	for (auto p : processor->getCommands())
		cout << "Processor includes: " << *p << endl;

	delete processor;
	processor = nullptr;
	delete currentGame;
	currentGame = nullptr;
}