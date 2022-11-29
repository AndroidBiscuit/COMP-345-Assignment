#include "Player.h"
#include <string>
using std::string;
using std::endl;
using std::cout;
using std::cin;
using std::remove;


class Cards;
class Order;
class OrderList;
class Territroy;

//Static variable initialer:
int Player::createdPlayers = 0;

//constructors:
Player::Player() {
	cout << "Player with ID-" << createdPlayers << " was created." << endl;
	createdPlayers++;
	name = "default";
	armiesAmount = 0;
	playerID = createdPlayers;
	ordersList = new OrdersList();
	hand = new Hand();
	intelligent = false;
	ordersToIssueFlag = true;
}

Player::Player(const Player& p) {
	cout << "Player with ID-:" << createdPlayers << " was created." << endl;
	createdPlayers++;
	this->name = p.name;
	this->armiesAmount = p.armiesAmount;
	this->playerID = p.playerID;
	this->ordersToIssueFlag = p.ordersToIssueFlag;
	for (auto p : p.territory) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);

	}
	for (auto p : p.tToAttack) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);
	}
	for (auto p : p.tToDefend) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);
	}
	hand = new Hand(*p.hand);

	ordersList = new OrdersList(*p.ordersList);	
}

//Assignment operators:
Player& Player::operator=(const Player& p) {
	cout << "Player with ID-:" << createdPlayers << " was created." << endl;
	name = p.name;
	playerID = p.playerID;
	ordersToIssueFlag = p.ordersToIssueFlag;
	for (Territory* p : p.territory) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);
	}
	for (auto p : p.tToAttack) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);
	}
	for (auto p : p.tToDefend) {
		Territory* temp = new Territory(*p);
		addTerritory(temp);
	}
	hand = new Hand(*p.hand);

	ordersList = new OrdersList(*p.ordersList);

	return *this;
}

//Stream insertions:
istream& operator>>(istream& in, Player& p)
{
	in >> p.name;
	return in;
}

ostream& operator<< (ostream& out, const Player& p) {
	out << "Player Name: " << p.name << endl;
	out << "ID: " << p.playerID << endl;
	out << "Armies Amount: " << p.armiesAmount << endl;
	out << "Owned Territories: " << endl;
	for (int i = 0; i < p.territory.size(); ++i) {
		out << "<" << p.territory.at(i)->getTName() << ">";
	}
	out << endl;
	out << "Handed Cards: " <<endl;
	out << *(p.hand);
	out << endl;
	out << "Orders issued: " << endl;
	out << *(p.ordersList);
	return out;
}

//destructor
Player::~Player() {
	cout << "Player " << this->getName() << " will now be destroyed." << endl;
	if(ordersList != nullptr) {
		delete ordersList; 
	}
	if (hand != nullptr) {
		delete hand; 
	}
	//release memory
	territory.clear();
	createdPlayers--;
}

//Mutators:
void Player::setName(string s) {
	this->name = s;
}

void Player::setPlayerID(int playerID){
	this->playerID = playerID;
}

void Player::setArmiesAmount(int armies){
	this->armiesAmount = armies;
}
void Player::setTerritory(vector<Territory*> const& other) {
	territory = other;
}

void Player::setOrdersList(OrdersList* ordersList){
	this->ordersList = ordersList;
}

void Player::setConquered(bool result) {
	this->conquered = result;
}

void Player::setOrdersToIssueFlag(bool ordersLeftToIssue) {
	this->ordersToIssueFlag = ordersLeftToIssue;
}

//Acessors:
string Player::getName() {
	return this->name;
}

int Player::getPlayerID() {
	return playerID;
}

int Player::getArmiesAmount(void) {
	return armiesAmount;
}

vector<Territory*> Player::getTerritory() {
	return territory;
}

Hand* Player::getHand() {
	return hand;
}

bool Player::getOrdersToIssueFlag() {
	return ordersToIssueFlag;
}

//vector<Card*> Player::getCards(void) {
//	return cards;
//}

OrdersList* Player::getOrders(void) {
	return ordersList;
}

void Player::addTerritory(Territory* ter) {
	ter->setOwner(this);
	territory.push_back(ter);
}

//void Player::addCard(Card* card) {
//	hand->addCard(card);
//}

void Player::removeTerritory(Territory* toRemove) {
	territory.erase(std::remove(territory.begin(), territory.end(), toRemove), territory.end());
}

vector<Player*> Player::getCanNotAttack() {
	return cannotAttack;
}

bool Player::getConquered() {
	return conquered;
}

//Method:

void Player::printOrderList(void) {
	cout << "----------------------------------" << endl;
	cout << "The following commands are available: " << endl;
	cout << "DEPLOY: place some armies on one of the current player's territories." << endl;
	cout << "ADVANCE: move some armies from one of the current player's territories(source) to an adjacent territory." << endl;
	cout << "BOMB: destroy half of the armies located on an opponent's territory that is adjacent to one of the current player's territories." << endl;
	cout << "BLOCKADE: triple the number of armies on a target territory and make it a neutral territory." << endl;
	cout << "AIRLIFT: advance some armies from one of the current player's territories to any another territory." << endl;
	cout << "NEGOTIATE: prevent attacks between the current playerand another player until the end of the turn." << endl;
	cout << "----------------------------------" << endl;
}

void Player::addFriendlyPlayer(int dstnPlayerID) {
	friendlyPlayers.push_back(dstnPlayerID);
}

void Player::clearFriendlyPlayer() {
	friendlyPlayers.clear();
}

bool Player::attackablePlayer(int dstnPlayerID) {
	for (int i = 0; i < friendlyPlayers.size(); i++) {
		if (friendlyPlayers[i] == dstnPlayerID) {
			return false;
		}
	}

	return true;
}

void Player::discoverOrderType(string x, Order* issued) {
	string options[] = { "deploy", "advance", "bomb", "blockade", "airlift", "negotiate" };

	for (int i = 0; i < 6; i++)
	{
		if (options[i].compare(x) == 0) {
			issued->setOrderName(options[i]);
			return;
		}
	}

	issued->setOrderName("UNKOWN ORDER");
	return;
}

//Returns territories not owned by the player
vector<Territory*> Player::availableTerritoriesToAttack()
{
	//Returns enemy territories player has access to through adjacent territories
	vector<Territory*> attackList;
	for (auto t: territory) {
		for (auto d : t->getAdjTerritories()) {
			if (!(find(attackList.begin(), attackList.end(), d) != attackList.end())) {
				if (d->getOwner() != this) {
					attackList.push_back(d);
				}
			}
		}
	}
	
	return attackList;
}

//Returns territories owned by the player
vector<Territory*> Player::availableTerritoriesToDefend()
{
	vector<Territory*> defendList;
	for (auto t : territory) {
		defendList.push_back(t);
	}

	return defendList;
}


void Player::issueOrder(Player* np, vector<Player*> pAvailable)
{
	Player* neutralPlayer = np;
	vector<Player*> playersAvailable = pAvailable;
	vector<Territory*> attackList = availableTerritoriesToAttack();
	vector<Territory*> defendList = availableTerritoriesToDefend();
	char orderAnswer2 = 'x';
	string orderAnswer;
	string territoryAnswer;
	string territorySource;
	string territoryDestination;
	bool repeatAttackOrDefendLoop = false;
	bool repeatMoveArmyUnitsAroundLoop = false;

	int armyUnitsToBeMoved, originalArmyAmount, finalArmyAmount, armyAmountAnswer, newArmyAmount;

	static int orderNumber = 0;
	string deployOrderName = "deploy";
	string advanceOrderName = "advance";
	string bombOrderName = "bomb";
	string blockadeOrderName = "blockade";
	string airliftOrderName = "airlift";
	string negotiateOrderName = "negotiate";

	//while player still has army units, order must be "deploy"
	while (getArmiesAmount() != 0) {
		orderNumber++;
		cout << "You have armies left in your reinforcement pool, to which territory would you like to deploy them to? \n";
		cout << "Here are the territories you can deploy them to: \n";
		for (Territory* territory : defendList)
		{
			cout << territory->getTName() << endl;
		}
		cin >> territoryAnswer;

		//making sure territory entered is a territory that exists in the player's defend list
		//if (makeSureTerritoryAnswerExists(toDefend, territoryAnswer)) { //perform this validation in orders?


			cout << "How many army units would you like to deploy to " << territoryAnswer << " ?\n";
			cout << "You have " << getArmiesAmount() << " army units left. \n";
			cin >> armyAmountAnswer;
			while (armyAmountAnswer > getArmiesAmount())
			{
				cout << "Army amount entered is more than available army amount. Please enter amount again. \n";
				cin >> armyAmountAnswer;
			}

			newArmyAmount = getArmiesAmount() - armyAmountAnswer;
			setArmiesAmount(newArmyAmount); //sets player's remaining army unit

			deployOrderName = deployOrderName.append(to_string(orderNumber));

			//create deploy order
			for (Territory* territory : defendList)
			{
				if (territory->getTName().compare(territoryAnswer) == 0)
				{
					Deploy* deployOrderName = new Deploy(armyAmountAnswer, territory, this); //make sure name fits
					ordersList->addOrder(deployOrderName);
					cout << "New deployment order added to " << this->getName() << "'s orderList \n";
					tToDefend.push_back(territory); //need to clear this somehow at the end of turn? or make sure that its army units arent empty
				}
			}
			
	};

	while (orderAnswer2 != 'y' && orderAnswer2 != 'n')
	{
		cout << "Would you like to move army units around on the map? \n";
		cin >> orderAnswer2;

		if (orderAnswer2 == 'y')
			repeatAttackOrDefendLoop = true;
		else if (orderAnswer2 == 'n')
			repeatAttackOrDefendLoop = false;
		else
			cout << "That is not a valid command. \n";
	}

	//while player still wants to move army units around the map, stay in loop
	while (repeatAttackOrDefendLoop) {
		orderNumber++;

		cout << "Here are where your army units are stationed at: \n";
		for (Territory* territory : tToDefend)
		{
			cout << territory->getTName() << " with " << territory->getArmyAmount() << endl;
		}
		
		cout << "From where would you like to move your army units? \n";
		cin >> territorySource;

		cout << "To where would you like to move your army units? \n";
		cout << "Here are the available territories adjacent to your chosen territory: \n";
		for (Territory* territory : defendList)
		{
			if (territory->getTName() == territorySource) {
				for(Territory* territoryAdj : territory->getAdjTerritories())
					cout<<territoryAdj->getTName() <<endl;
			}
		}
		cin >> territoryDestination;

		cout << "How many army units would you like to deploy to this destination territory? \n";
		cin >> armyAmountAnswer; //might need to do some checking here

		
		//create advance order
		advanceOrderName = advanceOrderName.append(to_string(orderNumber)); //setting up the order obj name
		
		for (Territory* fromTerritory : defendList)
		{
			if (fromTerritory->getTName().compare(territorySource) == 0)
			{
				for (Territory* toTerritory : fromTerritory->getAdjTerritories())
				{
					if (toTerritory->getTName().compare(territoryDestination) == 0)
					{
						Advance* advanceOrderName = new Advance(this, fromTerritory, toTerritory, armyAmountAnswer); //make sure name fits
						ordersList->addOrder(advanceOrderName);
					}
				}
				
			}
		}

		//resetting answer
		orderAnswer = "";
		orderAnswer2 = 'x';
		while (orderAnswer2 != 'y' && orderAnswer2 != 'n')
		{
			cout << "Would you like to move more army units around? (y/n) \n";
			cin >> orderAnswer2;

			if (orderAnswer2 == 'y')
				repeatAttackOrDefendLoop = true;
			else if (orderAnswer2 == 'n')
				repeatAttackOrDefendLoop = false;
			else
				cout << "That is not a valid command. \n";
		}

	};






	//Look at cards available  in hand and allow user to input answer
	cout << "Here are your cards from which you can create orders from: \n";
	vector<Card*> cardsAvailable = hand->getCards();
	for (Card* card : cardsAvailable) {
		cout << card->getCardName(card->getCardType()) << endl;
	}

	string cardToUse;
	bool cardValid = false;
	cout << "Which card would you like to use? \n";
	cin >> cardToUse;
	//while(!cardValid)
	//{
	//	cout << "Which card would you like to use? \n";
	//	cin >> cardToUse;

	//	//check to make sure the card exists in player's hand
	//	for (Card* card : cardsAvailable)
	//	{
	//		if (card->getCardName(card->getCardType()) == cardToUse)
	//			cardValid = true;

	//	}
	//	if (!cardValid)
	//		cout << "Invalid card, choose again. \n";
	//}
	//

	if (cardToUse.compare("bomb") == 0)
	{
		orderNumber++;
		cout << "To which enemy territory would you like to throw a bomb onto? \n";
		cout << "These are the enemy territories available to throw it on: \n";
		for (Territory* enemyTerritory : attackList)
		{
			cout << enemyTerritory->getTName() << endl;
		}
		cin >> territoryAnswer;

		//create bomb order
		bombOrderName = bombOrderName.append(to_string(orderNumber)); //setting up the order obj name
		for (Territory* territory : attackList)
		{
			if (territory->getTName().compare(territoryAnswer) == 0)
			{
				Bomb* bombOrderName = new Bomb(this, territory); //make sure name fits
				ordersList->addOrder(bombOrderName);				
				
			}
		}
	}
	else if (cardToUse.compare("blockade") == 0)
	{
		orderNumber++;
		cout << "To which territory would you like to use blockade on? \n";
		cout << "Here are the available territories you can use it on: \n";
		for (Territory* territory : defendList)
		{
			cout << territory->getTName() << endl;
		}
		cin >> territoryAnswer;

		//create blockade order
		blockadeOrderName = blockadeOrderName.append(to_string(orderNumber)); //setting up the order obj name

		for (Territory* territory : defendList)
		{
			if (territory->getTName() == territoryAnswer)
			{
				Blockade* blockadeOrderName = new Blockade(territory, this, neutralPlayer);
				ordersList->addOrder(blockadeOrderName);
			}
		}
	}
	else if (cardToUse.compare("airlift") == 0)
	{
		orderNumber++;
		cout << "From which territory would you like to airlift army units from? \n";
		cout << "here are the territories where you have army units stationed at: \n";
		for (Territory* t : tToDefend) {
			cout << t->getTName() <<endl;
		}
		cin >> territorySource;

		cout << "To where would you like to airlift army units to? \n";
		cin >> territoryDestination;

		cout << "How many army units would you like to move? \n";
		cin >> armyAmountAnswer;

		//create airlift order
		airliftOrderName = airliftOrderName.append(to_string(orderNumber)); //setting up the order obj name
		for (Territory* fromTerritory : defendList)
		{
			if (fromTerritory->getTName().compare(territorySource) == 0)
			{
				for (Territory* toTerritory : defendList)
				{
					if (toTerritory->getTName().compare(territoryDestination) == 0)
					{
						Airlift* airliftOrderName = new Airlift(this, fromTerritory, toTerritory, armyAmountAnswer); //make sure name fits
						ordersList->addOrder(airliftOrderName);
						
							//toDefend.push_back(territory); //need to clear this somehow at the end of turn? or make sure that its army units arent empty
					}
				}

			}
		}
	}
		
	else if (cardToUse.compare("diplomacy") == 0)
	{
		string playerAnswer;
		orderNumber++;
		cout << "which player would you like to target? \n";
		for (Player* p : playersAvailable)
		{
			cout << p->getName() << endl;
		}
		cin >> playerAnswer;

		//create diplomacy order
		negotiateOrderName = negotiateOrderName.append(to_string(orderNumber)); //setting up the order obj name
		for (Player* targetplayer : playersAvailable)
		{
			if (targetplayer->getName() == playerAnswer)
			{
				Negotiate* negotiateOrderName = new Negotiate(this, targetplayer);
				ordersList->addOrder(negotiateOrderName);
			}
				
		}
		
	}
	else if (cardToUse.compare("reinforcement"))
	{
		setArmiesAmount(getArmiesAmount() + 5);
	}
	 //take away the card that was used

}

//making sure territory enetered from command line is a proper territory
bool Player::makeSureTerritoryAnswerExists(vector<Territory*> territoryList, string territoryName) {
	for (Territory* t : territoryList) {
		if (t->getTName() == territoryName)
			return true;
	}
	return false;
}

PlayerStrategy *Player::getStrategy() {
	return playerStrategy;
}

void Player::setStrategy(PlayerStrategy* strategy) {
	playerStrategy = strategy;
}

vector<Territory*> Player::toAttack() {
	return playerStrategy->toAttack(this);
}

vector<Territory*> Player::toDefend() {
	return playerStrategy->toDefend(this);
}

void Player::issueOrder(string order) {
	playerStrategy->issueOrder(this, order);
}

vector<Territory*> Player::getAttackList() {
	return attackList;
}

vector<Territory*> Player::getDefendList() {
	return defendList;
}

void Player::setAttackList() {
	this->attackList = this->availableTerritoriesToAttack();
}

void Player::setDefendList() {
	this->defendList = this->availableTerritoriesToDefend();
}

void Player::setOrdersList(Order* order) {
	ordersList->addOrder(order);
}