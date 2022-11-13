/*******************************************/
// COMP 345 - Part 4 - Cards deck / hand
// 
// Team DN07, Fall 2022
//
// Assignment 1: Faizan Ahmad 
// Due date: October 9th 2022
/*******************************************/

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"
#include "Player.h"


using namespace std;

class Deck;
class Card;
class Hand;

// Use it as is for now. Intergation with other parts will be done in Assignment 2
class Order;
class Player;



//-------------------------------------------------------------------------------------------------
// Card object
//-------------------------------------------------------------------------------------------------

class Card {
public:
    // Each card has a type
    enum CardType {
        BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY
    };

    // Constructor
    Card(CardType type);
    

    // Copy constructor
    Card(const Card& card);

    // Deconstructor
    ~Card();

    // Assignment operator
    Card& operator = (const Card& card);

    // Stream operator
    friend ostream& operator << (std::ostream& out, const Card& card);

    // Getter for card type
    CardType getCardType();

    string getCardName(CardType card);

    // Play method to use the card in hand and return it to the deck
    void play(OrdersList* ordersList, Deck& deck);

private:
    CardType cardType;
};




//-------------------------------------------------------------------------------------------------
// Deck object
// Contains a finite collection of Warzone cards
//-------------------------------------------------------------------------------------------------

class Deck {
public:
    // Constructor
    Deck();

    // Copy constructor
    Deck(const Deck& deck);

    // Destructor
    ~Deck();

    // Assignment operator
    Deck& operator = (const Deck& deck);

    // 
    Deck(vector<Card*>& cards);

    // Stream operator
    friend ostream& operator << (std::ostream& out, const Deck& deck);

    // Draw a card at random from the remaining cards in the deck and place it in the hand
    Card draw();
    Card* draw(Player* p);

    // Add card to deck
    void addCard(Card& card);
    void addCard(Card* card);

    // Accessors
    int getDeckSize();
    vector<Card*> getCards();

private:
    vector<Card*> cards;
};




//-------------------------------------------------------------------------------------------------
// Hand object
//-------------------------------------------------------------------------------------------------

class Hand {
public:
    // Constructor
    Hand();

    // Copy constructor
    Hand(const Hand& hand);

    // Destructor
    ~Hand();

    // Assignment operator
    Hand& operator = (const Hand& hand);

    // Stream operator
    friend ostream& operator << (std::ostream& out, const Hand& hand);

    // Add cards in hand
    void addCard(Card& card);
    void addCard(Card* card);

    // Accessor: get cards from hand
    vector<Card*> getCards();

    // Accessor: get number of cards in hand
    int getNumberCards();

    //Accessor: get the pointer of deck
    Deck* getDeck();

    //Mutator : set the pointer of deck
    void setDeck(Deck* d);

private:
    vector<Card*> cards;
    int cardsInHard;
    Deck* deck;
};

#endif

// EOF