/*/*****************************************/
// COMP 345 - Part 4 - Cards deck / hand
// 
// Team DN07, Fall 2022
//
// Assignment 1: Faizan Ahmad 
// Due date: October 9th 2022
/*******************************************/

#include <iostream>
#include <random>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Cards.h"

using namespace std;

class Deck;




//-------------------------------------------------------------------------------------------------
// Card object
//-------------------------------------------------------------------------------------------------


// Constructor
Card::Card(CardType type) {
    this->cardType = type;
}

// Copy constructor
Card::Card(const Card& card) {
    this->cardType = card.cardType;
}

// Destructor
Card::~Card() {
    //delete this;
}

// Assignment operator
Card& Card::operator=(const Card& card) {
    this->cardType = card.cardType;
    return *this;
}

// Stream operator
ostream& operator << (ostream& out, const Card& card) {
    return out << "Card type: " << card.cardType;
}

// Getter for card type
Card::CardType Card::getCardType() {
    return this->cardType;
}

// Play method to use the card in hand and return it to the deck
void Card::play(vector<Order*>& orderList, Deck& deck) {

    // Temp
    Order* playOrder;

    if (this->cardType == CardType::BOMB) {
        //
    }
    if (this->cardType == CardType::REINFORCEMENT) {
        //
    }
    if (this->cardType == CardType::BLOCKADE) {
        //
    }
    if (this->cardType == CardType::AIRLIFT) {
        //
    }
    if (this->cardType == CardType::DIPLOMACY) {
        //
    }

    orderList.push_back(playOrder);

    // Show which card was used
    switch (this->getCardType()) {
    case 0:
        cout << "You used a BOMB card!" << endl;
        break;
    case 1:
        cout << "You used a REINFORCEMENT card!" << endl;
        break;
    case 2:
        cout << "You used a BLOCKADE card!" << endl;
        break;
    case 3:
        cout << "You used a AIRLIFT card!" << endl;
        break;
    case 4:
        cout << "You used a DIPLOMACY card!" << endl;
        break;
    }
}




//-------------------------------------------------------------------------------------------------
// Deck object
// Contains a finite collection of Warzone cards
//-------------------------------------------------------------------------------------------------


// Constructor
Deck::Deck() {
    for (int i = 0; i < 20; i++) {
        if (i % 5 == 0) {
            cards.push_back(new Card(Card::BOMB));
        }
        else if (i % 5 == 0) {
            cards.push_back(new Card(Card::REINFORCEMENT));
        }
        else if (i % 5 == 0) {
            cards.push_back(new Card(Card::BLOCKADE));
        }
        else if (i % 5 == 0) {
            cards.push_back(new Card(Card::AIRLIFT));
        }
        else {
            cards.push_back(new Card(Card::DIPLOMACY));
        }
    }
}

// Copy constructor
Deck::Deck(const Deck& deck) {
    // TODO
}

// Destructor
Deck::~Deck() {
    //delete this;
}

// Assignment operator
Deck& Deck::operator = (const Deck& deck) {
    this->cards = deck.cards;
    return *this;
}

// 
Deck::Deck(vector<Card*>& cards) {
    for (std::vector<Card*>::iterator it = cards.begin(); it != cards.end(); ++it) {
        cards.push_back(new Card(**it));
    }

    cout << this << endl;
}

// Stream operator
ostream& operator << (std::ostream& out, const Deck& deck) {
    return out << "Your deck has " << deck.cards.size() << " cards.";
}

// Draw a card at random from the cards remaining in the deck and place it in hand
Card Deck::draw() {
    Card* drawnCard = nullptr;

    // First check if the deck is empty
    if (!cards.empty()) {
        drawnCard = cards.back();
        cards.pop_back();
    }
    else {
        cout << "Error - Empty deck" << endl;
    }

    // Show drawn card
    cout << "Card type drawn: " << drawnCard->getCardType() << endl;

    return *drawnCard;
}

// Add card to deck
void Deck::addCard(Card& card) {
    this->cards.push_back(&card);
}

// Accessors
int Deck::getDeckSize() {
    return this->cards.size();
}




//-------------------------------------------------------------------------------------------------
// Hand object
//-------------------------------------------------------------------------------------------------


// Constructor
Hand::Hand() {
    // Randomized seed invocation
    srand(time(NULL));

    for (int i = 0; i < 5; i++) {

        // Generate random number
        int random = rand() % 5;

        // Compare random number output to card type
        if (random == 0) {
            this->cards.push_back(new Card(Card::BOMB));
        }
        else if (random == 1) {
            this->cards.push_back(new Card(Card::REINFORCEMENT));
        }
        else if (random == 2) {
            this->cards.push_back(new Card(Card::BLOCKADE));
        }
        else if (random == 3) {
            this->cards.push_back(new Card(Card::AIRLIFT));
        }
        else {
            this->cards.push_back(new Card(Card::DIPLOMACY));
        }
    }
}

// Copy constructor
Hand::Hand(const Hand& hand) {
    for (int i = 0; i < hand.cards.size(); i++) {
        this->cards.push_back(new Card(*hand.cards[i]));
    }

    cout << this << endl;
}

// Destructor
Hand::~Hand() {
    //delete this;
}

// Assignment operator
Hand& Hand::operator = (const Hand& hand) {
    this->cards = hand.cards;
    this->cardsInHard = hand.cardsInHard;

    return *this;
}

// Stream operator
ostream& operator<<(ostream& out, const Hand& hand) {
    out << "Your hand has " << hand.cards.size() << " cards.";
    for (auto x : hand.cards) {
        out << *x << endl;
    }
    return out;
}

// Add cards in hand
void Hand::addCard(Card& card) {
    this->cards.push_back(&card);
}

// Accessor: get cards from hand
vector<Card*> Hand::getCards() {
    return this->cards;
}

// Accessor: get number of cards in hand
int Hand::getNumberCards() {
    return this->cards.size();
}




// EOF
