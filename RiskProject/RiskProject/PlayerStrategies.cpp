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
void HumanPlayerStrategy::issueOrder(Player* player, string order) {
	//TODO: do we need to check the input?

	if (order == "deploy") {
		//
	}
	if (order == "advance") {
		//
	}
	else if (order == "blockade") {
		//
	}
	else if (order == "airlift") {
		//
	}
	else if (order == "negociate") {
		//
	}
	else if (order == "bomb") {
		//
	}
}

// Return the attack list of selected player
vector<Territory*> HumanPlayerStrategy::toAttack(Player* player) {
	return player->getAttackList();
}

// Return the defend list of selected player
vector<Territory*> HumanPlayerStrategy::toDefend(Player* player) {
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
void AggressivePlayerStrategy::issueOrder(Player* player, string order) {
	
	int orderNumber = 0;
	int territoryArmy = 0;
	string territoryToBeDeployedTo;

	string deployOrderName = "deploy";
	string advanceOrderName = "advance";
	string bombOrderName = "bomb";
	//TODO: INITIALIZATION PROBLEM AND HOW TO CHOOSE SUBSEQUENT TERRITORIES TO DEPLOY ARMIES TO
	//deploy all army to strongest territory
	//get territory w most army units on it 
	for (Territory* territory : toDefend(player))
	{
		if (territory->getArmyAmount() > territoryArmy) {
			territoryArmy = territory->getArmyAmount();
			territoryToBeDeployedTo = territory->getTName();
		}
	}
	//deploy all army to chosen territory
	deployOrderName = deployOrderName.append(to_string(orderNumber));
	for (Territory* territory : toDefend(player)) {
		if (territory->getTName().compare(territoryToBeDeployedTo) == 0) {
			orderNumber++;
			int playerArmyAmount = player->getArmiesAmount();
			int territoryArmyAmount = territory->getArmyAmount();
			int armyAmount = playerArmyAmount + territoryArmyAmount;

			Deploy* deployOrderName = new Deploy(armyAmount, territory, player);
			player->setArmiesAmount(0);
			player->tToDefend.push_back(territory);
			player->setOrdersList(deployOrderName);
		}
	}

	vector<Territory*> adjTerritoriesVector;
	//Move army units to adjacent enemy territory
	for (Territory* territory : toDefend(player)) {
		if (territory->getTName() == territoryToBeDeployedTo) {
			for (Territory* territoryAdj : territory->getAdjTerritories()) {
				
				if (territoryAdj->getOwner() != player)
				{
					orderNumber++;
					advanceOrderName = advanceOrderName.append(to_string(orderNumber)); //setting up the order obj name
					Advance* advanceOrderName = new Advance(player, territory, territoryAdj, territory->getArmyAmount());
					player->setOrdersList(advanceOrderName);
					break; //does this exit all of the loops? TO DEBUG
				}
			}
		}
	}

	bool usedCardFlag = false;

	//get cards- if its a bomb, then use it
	vector<Card*> cardsAvailable = player->getHand()->getCards();
	for (Card* card : cardsAvailable) {
		if (card->getCardName(card->getCardType()) == "bomb") 
		{
			//get random territory from territories that can be attacked
			vector<Territory*> territoriesToBeAttacked = toAttack(player);
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
vector<Territory*> AggressivePlayerStrategy::toAttack(Player* player) {
	return player->getAttackList();
}

// Return the defend list of selected player
vector<Territory*> AggressivePlayerStrategy::toDefend(Player* player) {
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
void BenevolentPlayerStrategy::issueOrder(Player* player, string order) {
	
}

// Return the attack list of selected player
vector<Territory*> BenevolentPlayerStrategy::toAttack(Player* player) {
	return player->getAttackList();
}

// Return the defend list of selected player
vector<Territory*> BenevolentPlayerStrategy::toDefend(Player* player) {
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
// Issue order
void NeutralPlayerStrategy::issueOrder(Player* player, string order) {
	//
}

// Return the attack list of selected player
vector<Territory*> NeutralPlayerStrategy::toAttack(Player* player) {
	return player->getAttackList();
}

// Return the defend list of selected player
vector<Territory*> NeutralPlayerStrategy::toDefend(Player* player) {
	return player->getDefendList();
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
void CheaterPlayerStrategy::issueOrder(Player* player, string order) {
	vector<Territory*> enemyTerritories = player->availableTerritoriesToAttack(); //gets adjacent territories to its own
	for (Territory* t : enemyTerritories)
	{
		t->setOwner(player); 
	}
}

// Return the attack list of selected player
vector<Territory*> CheaterPlayerStrategy::toAttack(Player* player) {
	return player->getAttackList();
}

// Return the defend list of selected player
vector<Territory*> CheaterPlayerStrategy::toDefend(Player* player) {
	return player->getDefendList();
}

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