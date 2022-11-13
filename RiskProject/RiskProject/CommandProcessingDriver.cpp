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

	system("pause");
	GameEngine* currentGame2 = new GameEngine();
	CommandProcessor* processor2 = new CommandProcessor();
	cout << "Read commands from file, please input <filename>." << endl;
	string fileName;
	cin >> fileName;
	// copy the source file so that we can delete the top line after reading it
	ifstream inFile(fileName);
	ofstream outFile("copy.txt");
	outFile << inFile.rdbuf();
	inFile.close();
	outFile.close();
	FileLineReader* fprocessor = new FileLineReader("copy.txt"); // adaptee
	FileCommandProcessorAdapter* adapter = new FileCommandProcessorAdapter(fprocessor);// adapter (inherited from target)

	while (currentGame2->getState() != "assignreinforcement") {
		currentState = currentGame2->getState();
		cout << *currentGame2 << endl;
		Command* cmd = adapter->processCommand();
		isValid = processor->validate(cmd, currentGame2);

		if (!isValid) {
			cmd->saveEffect("error");
			break;
		}
	
	}
	
	system("pause");

	delete processor2;
	processor2 = nullptr;
	delete currentGame2;
	currentGame2 = nullptr;
	delete adapter;
	adapter = nullptr;
}