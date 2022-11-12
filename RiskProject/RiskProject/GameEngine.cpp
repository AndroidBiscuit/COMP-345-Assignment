#include <iostream>
#include <algorithm>
#include <random>
#include "GameEngine.h"

using std::default_random_engine;


//Constructor
GameEngine::GameEngine(){
	state = "start";									/*set first state as start*/
}

GameEngine::GameEngine(const GameEngine& other){
	state = other.state;
}

//mutator and accessor
void GameEngine::setState(string currentState){
	state = currentState;
}

string GameEngine::getState(){
	return state;
}

Map* GameEngine::getMap() {
	return map;
};

vector<Player*> GameEngine::getPlayers() {
	return players;
};

//Assignment operator
GameEngine& GameEngine::operator =(const GameEngine& other){
	state = other.state;
	return *this;
}

// Stream insertion
ostream& operator<<(ostream& out, const GameEngine& ge)
{
	out << "The current state is : " << ge.state << endl;
	return out;
}

//Destructor
GameEngine::~GameEngine() {
	cout << "Destorying GameEngine!" << endl;
	if (neutral != NULL) {
		delete neutral;
		neutral = NULL;
	}

	if (map != NULL) {
		delete map;
		map = NULL;
	}

	if (deck != NULL) {
		delete deck;
		deck = NULL;
	}

	for (auto p : players) {
		delete p;
	}
}


// sets GameEngine object's state
void GameEngine::transition(string newState) {
	this->setState(newState);
	cout << "You are transited to state: " << this->getState() << endl;
}


//implements a command-based user interaction mechanism to start the game.
void GameEngine::startupPhase() {
	string source;
	string currentState;
	bool isValid{};

	Command* cmd{};
	CommandProcessor* cprocessor{};
	FileLineReader* fprocessor{};
	FileCommandProcessorAdapter* adapter{};

	do {
	    //Upon starting the application, a command line option is set to either read commands from the console
		cout << "Please enter -console or -file <filename> to choose the input source." << endl;
		cin >> source;
	
		//Commands can be read from the console
		if (source == "console") {
			cprocessor = new CommandProcessor();
		}
		
		else if(source == "file") {
			string fileName;
			cin >> fileName;
			// copy the source file so that we can delete the top line after reading it
			ifstream inFile(fileName);
			ofstream outFile("copy.txt");
			outFile << inFile.rdbuf();
			inFile.close();
			outFile.close();
			fprocessor = new FileLineReader("copy.txt"); // adaptee
			adapter = new FileCommandProcessorAdapter(fprocessor);// adapter (inherited from target)
		
		}
	} while (source != "console" && source != "file");

	// remove the "enter" from the cin buffer
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	
	while (state != "exitprogram") {
		currentState = this->getState();
		cout << *this << endl;
		
		if (currentState == "assignreinforcement") {
			cout << "switch the game to the play phase" << endl;
			/*playPhase();*/
			break;
		}

		if (source == "console") {
			cout << "Enter your command: " << endl;
			cmd = cprocessor->processCommand();
			isValid = cprocessor->validate(cmd, this);

			if (!isValid) {
				cmd->saveEffect("error");
				continue;
			}
		}
		else if (source == "file") {
			cmd = adapter->processCommand();
			isValid = cprocessor->validate(cmd, this);

			if (!isValid) {
				cmd->saveEffect("error");
				break;
			}
		}
	
	}

	if (source == "console") {
		delete cprocessor;
		cprocessor = nullptr;
	}
	else if (source == "file") {
		delete adapter;
		adapter = nullptr;
	}
}

void GameEngine::reinforcementPhase() {
	for (Player* p : players) {
		int originalArmies = p->getArmiesAmount();
		int numOfTerritoriesOwned = (p->getTerritory()).size(); 
		int numOfReinforcementArmyUnits = floor(numOfTerritoriesOwned / 3);

		//if player owns entire continent- they receive the bonus army reinforcement
		//check for player owning all the territories of an entire continent
		for (auto c : map->getAllContinent()) {
			int playerOwnedTCounter = 0;
			int territoryCounter = 0;

			for (auto t : c->getSubGraph()) {
				territoryCounter++;
				if (t->getOwner()->getPlayerID() == p->getPlayerID()) {
					playerOwnedTCounter++;
				}
			}
			//if fullfill the requirments, give the bonus of the armyValue of the continent
			if (territoryCounter == playerOwnedTCounter) {
				cout << "Player " << p->getName() << " owns the entire of " << c->name << "and gains a " << c->armyValue << " bonus!" << endl;
				numOfReinforcementArmyUnits += c->armyValue;
			}
		}
		//Default minimum to 3
		if (numOfReinforcementArmyUnits < 3) {
			numOfReinforcementArmyUnits = 3;
		}

		p->setArmiesAmount(numOfReinforcementArmyUnits + originalArmies);
		cout << "Player " << p->getPlayerID() << " - " << p->getName() << " has received " << numOfReinforcementArmyUnits << " armies." << endl;
		cout << "Current army count is: " << p->getArmiesAmount() << endl;

	}
}

//takes a map's file name to create a Map object 
bool GameEngine::loadMap(string fileName) {
	int numberOfMaps = -1;
	MapLoader load;
	Map* created = nullptr;
	vector<Map*> mapsCreated;

	try {
		created = load.loadMap(fileName);
		mapsCreated.push_back(created);
		int sum = 0;
		for (Territory* p : created->getAllTerritory()) {
			sum++;
		}
		cout << "Territories placed: " << sum << endl;
		map = created;
		return true;
	}
	catch (const invalid_argument& e) {
		cout << "The map file provided was invalid. " << endl;
		return false;
	}
}

//removes a player from the game
void GameEngine::removePlayer(Player* toRemove) {
	players.erase(remove(players.begin(), players.end(), toRemove), players.end());
	delete toRemove;
}

//takes player's name as the parameter to create a player object 
void GameEngine::addPlayer(string name) {

	//Creating Player Objects:
	Player* temp = new Player();
	temp->setName(name);
	cout << "Welcome to Warzone, " << name << "!" << endl;
	players.push_back(temp);
}

//asks player's name from the console to create a player object 
void GameEngine::addPlayer(void) {
	int n = 0;
	cout << "Player Creation Menu." << endl;
	while (n < 2 || n > 6) {
		cout << "Please enter the number of players. " << endl;
		cout << "The number should be between 2 and 6." << endl;
		cin >> n;
	}

	//Creating Player Objects:
	for (int i = 0; i < n; i++)
	{
		Player* temp = new Player();
		string name;
		cout << "Player " << (i + 1) << " - Enter Player's name: " << endl;
		cin >> name;
		(*temp).setName(name);
		cout << "Welcome to Warzone, " << name << "!" << endl;
		players.push_back(temp);
	}

	cout << "All players have been added! Here is who will be playing:" << endl;
	for (Player* p : players) {
		cout << "Player " << (*p).getPlayerID() << " - " << (*p).getName() << endl;
	}
}

//sets up the neccesary settings for the game to start
bool GameEngine::gameStartSetting() {
	//shuffle the territories vector before assigning territories
	auto rng = default_random_engine{};
	string result;
	bool isIntelligent = false;
	vector<Territory*> copyTerritories = map->getAllTerritory();
	std::shuffle(std::begin(copyTerritories), std::end(copyTerritories), rng);

	//Determine whether user input will be used:
	cout << "Would you like to use console input to play the game? Y/N" << endl;
	cin >> result;
	while (result != "N" && result != "n" && result != "y" && result != "Y") {
		cin >> result;
	}
	if (result == "Y" || result == "y") {
		isIntelligent = true;
	}

	//Create neutral player:
	neutral = new Player();
	neutral->setName("Neutral");
	//Print out players:
	cout << "All players have been added! Here is who will be playing:" << endl;
	for (Player* p : players) {
		cout << "Player " << p->getPlayerID() << " - " << p->getName() << endl;
		if (isIntelligent) { //Sets intelligence modifier for all players (demo purposes):
			p->intelligent = true;
		}
		//Associate the neutral player with all players:
		p->neutral = neutral;
		//Associate Map with players:
		p->map = map;
	}

	// Fairly distributing the territories among all players
	int playerCount = players.size();
	int count = 0;
	int index = 0;
	for (auto t : copyTerritories) {
		index = count % playerCount;
		t->setOwner(players[index]);
		players[index]->addTerritory(t);
		cout << "Territory " << t->getTName() << " is now owned by " << t->getOwner()->getName() << endl;
		count++;
	}

	//Randomly determine the order of play of the players in the game
	std::shuffle(std::begin(players), std::end(players), rng);
	//Create Deck object:
	deck = new Deck();

	//Add initial army value and draw cards:
	for (auto p : players) {
		p->getHand()->setDeck(deck);
		//Give 50 initial armies to each player
		p->setArmiesAmount(50);

		//Each player draws 2 cards each from the deck
		deck->draw(p);
		deck->draw(p);
	
		cout << "\nPlayer " << p->getName() + " has received the following cards: " << endl;
		for (auto c : p->getHand()->getCards()) {
			cout << *c << endl;
		}
	}

	//Enter play phase.
	return true;



}