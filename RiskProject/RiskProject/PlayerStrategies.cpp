// To Monica: we probably need to add the toAttack and toDefend methods to the player class


#include "PlayerStrategies.h"

//_________________________________________________________________________________________________
// Human player strategy
//-------------------------------------------------------------------------------------------------

// Issue order
void HumanPlayerStrategy::issueOrder(Player* player, string order) {
	//
}

// Return the attack list of selected player
vector<Territory*> HumanPlayerStrategy::toAttack(Player* player) {
	return *(player->);
}

// Return the defend list of selected player
vector<Territory*> HumanPlayerStrategy::toDefend(Player* player) {
	return *(player->);
}





//_________________________________________________________________________________________________
// Aggressive player strategy
//-------------------------------------------------------------------------------------------------

// Issue order
void HumanPlayerStrategy::issueOrder(Player* player, string order) {
	//
}

// Return the attack list of selected player
vector<Territory*> HumanPlayerStrategy::toAttack(Player* player) {
	return *(player->);
}

// Return the defend list of selected player
vector<Territory*> HumanPlayerStrategy::toDefend(Player* player) {
	return *(player->);
}





//_________________________________________________________________________________________________
// Benevolent player strategy
//-------------------------------------------------------------------------------------------------

// Issue order
void BenevolentPlayerStrategy::issueOrder(Player* player, string order) {
	//
}

// Return the attack list of selected player
vector<Territory*> BenevolentPlayerStrategy::toAttack(Player* player) {
	return *(player->);
}

// Return the defend list of selected player
vector<Territory*> BenevolentPlayerStrategy::toDefend(Player* player) {
	return *(player->);
}





//_________________________________________________________________________________________________
// Neutral player strategy
//-------------------------------------------------------------------------------------------------

// Issue order
void HumanPlayerStrategy::issueOrder(Player* player, string order) {
	//
}

// Return the attack list of selected player
vector<Territory*> NeutralPlayerStrategy::toAttack(Player* player) {
	return *(player->);
}

// Return the defend list of selected player
vector<Territory*> NeutralPlayerStrategy::toDefend(Player* player) {
	return *(player->);
}





//TODO cheater player?
