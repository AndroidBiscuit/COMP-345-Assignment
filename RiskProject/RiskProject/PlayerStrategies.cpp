#include "PlayerStrategies.h"
#include <algorithm>
//_________________________________________________________________________________________________
// Human player strategy
//-------------------------------------------------------------------------------------------------
HumanPlayerStrategy::HumanPlayerStrategy() :PlayerStrategy()
{
}

HumanPlayerStrategy::HumanPlayerStrategy(Player* player) : PlayerStrategy(player)
{
}
// Issue order
void HumanPlayerStrategy::issueOrder() { //TODO:Need to pass neutral and players vector
	Player* neutralPlayer = player->neutral;
	//vector<Player*> playersAvailable = pAvailable;
	vector<Territory*> attackList = toAttack();
	vector<Territory*> defendList = toDefend();
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
	while (player->getArmiesAmount() != 0) {
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
		cout << "You have " << player->getArmiesAmount() << " army units left. \n";
		cin >> armyAmountAnswer;
		while (armyAmountAnswer > player->getArmiesAmount())
		{
			cout << "Army amount entered is more than available army amount. Please enter amount again. \n";
			cin >> armyAmountAnswer;
		}

		newArmyAmount = player->getArmiesAmount() - armyAmountAnswer;
		player->setArmiesAmount(newArmyAmount); //sets player's remaining army unit

		deployOrderName = deployOrderName.append(to_string(orderNumber));

		//create deploy order
		for (Territory* territory : defendList)
		{
			if (territory->getTName().compare(territoryAnswer) == 0)
			{
				Deploy* deployOrderName = new Deploy(armyAmountAnswer, territory, player); //make sure name fits
				player->ordersList->addOrder(deployOrderName);
				cout << "New deployment order added to " << player->getName() << "'s orderList \n";
				player->tToDefend.push_back(territory); //need to clear this somehow at the end of turn? or make sure that its army units arent empty
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
		for (Territory* territory : player->tToDefend)
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
				for (Territory* territoryAdj : territory->getAdjTerritories())
					cout << territoryAdj->getTName() << endl;
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
						Advance* advanceOrderName = new Advance(player, fromTerritory, toTerritory, armyAmountAnswer); //make sure name fits
						player->ordersList->addOrder(advanceOrderName);
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
	vector<Card*> cardsAvailable = player->hand->getCards();
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
				Bomb* bombOrderName = new Bomb(player, territory); //make sure name fits
				player->ordersList->addOrder(bombOrderName);

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
				Blockade* blockadeOrderName = new Blockade(territory, player, neutralPlayer);
				player->ordersList->addOrder(blockadeOrderName);
			}
		}
	}
	else if (cardToUse.compare("airlift") == 0)
	{
		orderNumber++;
		cout << "From which territory would you like to airlift army units from? \n";
		cout << "here are the territories where you have army units stationed at: \n";
		for (Territory* t : player->tToDefend) {
			cout << t->getTName() << endl;
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
						Airlift* airliftOrderName = new Airlift(player, fromTerritory, toTerritory, armyAmountAnswer); //make sure name fits
						player->ordersList->addOrder(airliftOrderName);

						//toDefend.push_back(territory); //need to clear this somehow at the end of turn? or make sure that its army units arent empty
					}
				}

			}
		}
	}

	else if (cardToUse.compare("diplomacy") == 0)
	{
		//string playerAnswer;
		//orderNumber++;
		//cout << "which player would you like to target? \n";
		//for (Player* p : playersAvailable)
		//{
		//	cout << p->getName() << endl;
		//}
		//cin >> playerAnswer;

		////create diplomacy order
		//negotiateOrderName = negotiateOrderName.append(to_string(orderNumber)); //setting up the order obj name
		//for (Player* targetplayer : playersAvailable)
		//{
		//	if (targetplayer->getName() == playerAnswer)
		//	{
		//		Negotiate* negotiateOrderName = new Negotiate(player, targetplayer);
		//		player->ordersList->addOrder(negotiateOrderName);
		//	}

		//}

	}
	else if (cardToUse.compare("reinforcement"))
	{
		player->setArmiesAmount(player->getArmiesAmount() + 5);
	}
	//take away the card that was used
}

// Return the attack list of selected player
vector<Territory*> HumanPlayerStrategy::toAttack() {
	return player->getAttackList();
}

// Return the defend list of selected player
vector<Territory*> HumanPlayerStrategy::toDefend() {
	return player->getDefendList();
}





//_________________________________________________________________________________________________
// Aggressive player strategy
//-------------------------------------------------------------------------------------------------
AggressivePlayerStrategy::AggressivePlayerStrategy() :PlayerStrategy()
{
}

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) : PlayerStrategy(player)
{
}
// Issue order
void AggressivePlayerStrategy::issueOrder() {
	
	int orderNumber = 0;
	int territoryArmy = 0;
	string territoryToBeDeployedTo;

	string deployOrderName = "deploy";
	string advanceOrderName = "advance";
	string bombOrderName = "bomb";
	//TODO: INITIALIZATION PROBLEM AND HOW TO CHOOSE SUBSEQUENT TERRITORIES TO DEPLOY ARMIES TO
	//5 army units and place them anywhere randomly on their territories
	vector<Territory*> territories = player->toDefend();

	for (int i = 0; i < 5; i++) {
		int random = rand() % territories.size();
		int orgnArmyAmount = territories[random]->getArmyAmount();
		territories[random]->setArmyAmount(orgnArmyAmount+1);
		int playerArmyAmount = player->getArmiesAmount();
		player->setArmiesAmount(playerArmyAmount - 1);
	}
	

	//deploy all army to strongest territory
	//get territory w most army units on it 
	for (Territory* territory : player->toDefend())
	{
		if (territory->getArmyAmount() > territoryArmy) {
			territoryArmy = territory->getArmyAmount();
			territoryToBeDeployedTo = territory->getTName(); //just choosing territory here
		}
	}
	//deploy all army to chosen territory
	deployOrderName = deployOrderName.append(to_string(orderNumber));
	for (Territory* territory : toDefend()) {
		if (territory->getTName().compare(territoryToBeDeployedTo) == 0) {
			orderNumber++;
			int playerArmyAmount = player->getArmiesAmount();
			int territoryArmyAmount = territory->getArmyAmount();
			int armyAmount = playerArmyAmount + territoryArmyAmount;

			Deploy* deployOrderName = new Deploy(armyAmount, territory, player);
			player->setArmiesAmount(0);
			player->tToDefend.push_back(territory); //tToDefend is a territory vector where army units are deployed to
			player->setOrdersList(deployOrderName);
		}
	}

	vector<Territory*> adjTerritoriesVector;
	//Move army units to adjacent enemy territory
	for (Territory* territory : toDefend()) {
		if (territory->getTName() == territoryToBeDeployedTo) {
			for (Territory* territoryAdj : territory->getAdjTerritories()) {
				
				if (territoryAdj->getOwner() != player) //making sure the adj territroy is an enemy's 
				{
					orderNumber++;
					advanceOrderName = advanceOrderName.append(to_string(orderNumber)); //setting up the order obj name
					Advance* advanceOrderName = new Advance(player, territory, territoryAdj, territory->getArmyAmount());
					player->setOrdersList(advanceOrderName);
					goto stop;
				}
			}
		}
	}
	stop:

	bool usedCardFlag = false;

	//get cards- if its a bomb, then use it
	vector<Card*> cardsAvailable = player->getHand()->getCards();
	for (Card* card : cardsAvailable) {
		if (card->getCardName(card->getCardType()) == "bomb") 
		{
			//get random territory from territories that can be attacked
			vector<Territory*> territoriesToBeAttacked = toAttack();
			int random = rand() % territoriesToBeAttacked.size();
			Territory* territory = territoriesToBeAttacked[random];
			orderNumber++;
			//create bomb order
			bombOrderName = bombOrderName.append(to_string(orderNumber)); //setting up the order obj name
			Bomb* bombOrdername = new Bomb(player, territory);
			//discard bomb card and grab a new card
			usedCardFlag = true;
			break;
		}
	}

	if (!usedCardFlag) {
		//discard a random card and pick up a new one

	}

	
	
}

// Return the attack list of selected player
vector<Territory*> AggressivePlayerStrategy::toAttack() {
	return player->getAttackList();
}

// Return the defend list of selected player
vector<Territory*> AggressivePlayerStrategy::toDefend() {
	return player->getDefendList();
}





//_________________________________________________________________________________________________
// Benevolent player strategy
//-------------------------------------------------------------------------------------------------
BenevolentPlayerStrategy::BenevolentPlayerStrategy() :PlayerStrategy()
{
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) : PlayerStrategy(player)
{
}
// Issue order
void BenevolentPlayerStrategy::issueOrder() {
	player->setOrdersToIssueFlag(false);
}

// Return the attack list of selected player
vector<Territory*> BenevolentPlayerStrategy::toAttack() {
	return player->getAttackList();
}

// Return the defend list of selected player
vector<Territory*> BenevolentPlayerStrategy::toDefend() {
	return player->getDefendList();
}





//_________________________________________________________________________________________________
// Neutral player strategy
//-------------------------------------------------------------------------------------------------
NeutralPlayerStrategy::NeutralPlayerStrategy() :PlayerStrategy()
{
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) : PlayerStrategy(player)
{
}
// Issue order: Neutral player: never issues any order.
void NeutralPlayerStrategy::issueOrder() {
	cout << "The Neutral Player cannot issue any orders." << endl;
	player->setOrdersToIssueFlag(false);
}

// Return the attack list of selected player
vector<Territory*> NeutralPlayerStrategy::toAttack() {
	vector<Territory*> ret;
	return ret;
}

// Return the defend list of selected player
vector<Territory*> NeutralPlayerStrategy::toDefend() {
	vector<Territory*> ret;
	return ret;
}




//_________________________________________________________________________________________________
// Cheater player strategy
//-------------------------------------------------------------------------------------------------
CheaterPlayerStrategy::CheaterPlayerStrategy() :PlayerStrategy()
{
}

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player) : PlayerStrategy(player)
{
}
// Issue order - automatically turns adjacent territory owners to cheater player's 
void CheaterPlayerStrategy::issueOrder() {
	Order* issued;
	Card* played;
	LogObserver* orderObserver = new LogObserver(player->getOrders());
	vector<Territory*> defend = this->toDefend();
	vector<Territory*> attack = this->toAttack();

	cout << "----------------------------------" << endl;
	cout << "Cheater will now advance on all adjacent enemy territories." << endl;

	for (Territory* t : attack) {
		//Remove territory from original owner:
		(t->getOwner())->removeTerritory(t);
		//Make territory transfer and move armies:
		t->setOwner(player);
		player->addTerritory(t);
	}

	cout << "Cheater player has conquered " << attack.size() << " territories." << endl;
	player->setConquered(true);
	//vector<Territory*> enemyTerritories = player->availableTerritoriesToAttack(); //gets adjacent territories to its own
	//for (Territory* t : enemyTerritories)
	//{
	//	t->setOwner(player); 
	//}
	player->setOrdersToIssueFlag(false);
}

vector<Territory*> CheaterPlayerStrategy::toAttack()
{
	//Returns enemy territories player has access to through adjacent territories. 
	vector<Territory*> attack;
	for (auto t : player->territory) {
		for (auto d : t->getAdjTerritories()) {
			if (!(find(attack.begin(), attack.end(), d) != attack.end())) {
				if (d->getOwner() != player) {
					attack.push_back(d);
				}

			}

		}
	}

	// Now the vector is sorted from best to worst target, uses the overloaded < operator from Map file
	sort(attack.begin(), attack.end());

	return attack;
}

vector<Territory*> CheaterPlayerStrategy::toDefend()
{
	//Returns territories owned by the player:
	vector<Territory*> defense;
	for (auto t : player->territory) {
		defense.push_back(t);
	}

	sort(defense.begin(), defense.end());

	return defense;
}

//// Return the attack list of selected player
//vector<Territory*> CheaterPlayerStrategy::toAttack() {
//	return player->getAttackList();
//}
//
//// Return the defend list of selected player
//vector<Territory*> CheaterPlayerStrategy::toDefend() {
//	return player->getDefendList();
//}

PlayerStrategy::PlayerStrategy()
{
	player = NULL;
}

PlayerStrategy::PlayerStrategy(Player* player)
{
	this->player = player;
}

PlayerStrategy::~PlayerStrategy()
{
	player = NULL;
}

void PlayerStrategy::setPlayer(Player* player)
{
	this->player = player;
}

Player* PlayerStrategy::getPlayer(void)
{
	return player;
}