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
	string currentState;
	bool isValid{};

	CommandProcessor* processor = new CommandProcessor();
	
	while (state != "exitprogram") {
		currentState = this->getState();
		cout << *this << endl;
		
		cout << "Enter your command: " << endl;
		Command* cmd = processor->processCommand();

		isValid = processor->validate(cmd, this);

		if (!isValid) {
			cmd->saveEffect("error");
			continue;
		}
		if (currentState == "assignreinforcement") {
			/*playPhase();*/
			cout << "switch the game to the play phase" << endl;
		}
	
	}
	delete processor;
	processor = nullptr;
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