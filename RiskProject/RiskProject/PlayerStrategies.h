#pragma once
#include "GameEngine.h"
#include "Orders.h"
#include "Map.h"

class Player;

class PlayerStrategy {
public:
	Player* player;
	// Issue order
	virtual void issueOrder() = 0;

	// Return the attack list of selected player
	virtual vector<Territory*> toAttack() = 0;

	// Return the defend list of selected player
	virtual vector<Territory*> toDefend() = 0;

	PlayerStrategy();
	PlayerStrategy(Player* player);
	virtual ~PlayerStrategy();
	void setPlayer(Player* player);
	Player* getPlayer(void);

};

class HumanPlayerStrategy : public PlayerStrategy {
public: 
	HumanPlayerStrategy();
	HumanPlayerStrategy(Player* player);
	void issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
};

class AggressivePlayerStrategy : public PlayerStrategy {

public:
	AggressivePlayerStrategy();
	AggressivePlayerStrategy(Player* player);
	void issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	BenevolentPlayerStrategy();
	BenevolentPlayerStrategy(Player* player);
	void issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	NeutralPlayerStrategy();
	NeutralPlayerStrategy(Player* player);
	void issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
};

class CheaterPlayerStrategy : public PlayerStrategy {
public:
	CheaterPlayerStrategy();
	CheaterPlayerStrategy(Player* player);
	void issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
};

