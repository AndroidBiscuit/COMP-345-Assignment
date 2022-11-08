/*******************************************/
// COMP 345 - Part 4 - Cards deck / hand
// 
// Team DN07, Fall 2022
//
// Assignment 1: Faizan Ahmad 
// Due date: October 9th 2022
/*******************************************/

#include "Cards.h"
#include "CardsDriver.h"
#include <iostream>

using namespace std;




//-------------------------------------------------------------------------------------------------
// Part 4 driver
// contains a free function named testCards() that creates a deck of Warzone cards, then create 
// a hand object that is filled by drawing cards from the deck
//-------------------------------------------------------------------------------------------------


//void testCards() {
//
//    // Print title
//    cout << "********************************************" << "\n"
//        << "COMP 345 - Part 4 - Cards deck / hand driver" << endl << endl;
//
//    // Make new deck and hand
//    Deck* newDeck = new Deck();
//    Hand* newHand = new Hand();
//
//    // Print Deck and Hand
//    cout << *newDeck << endl;
//    cout << *newHand << endl;
//    cout << endl;
//
//    // Test draw method, first card
//    cout << "--------------------------------------------------" << endl;
//    cout << "Test draw method, first card: ";
//    Card firstCard = newDeck->draw();
//    newHand->addCard(firstCard);
//
//    // Test draw method, second card
//    cout << "--------------------------------------------------" << endl;
//    cout << "Test draw method, second card: ";
//    Card secondCard = newDeck->draw();
//    newHand->addCard(secondCard);
//
//    // Test draw method, third card
//    cout << "--------------------------------------------------" << endl;
//    cout << "Test draw method, third card: ";
//    Card thirdCard = newDeck->draw();
//    newHand->addCard(thirdCard);
//
//    cout << "--------------------------------------------------" << endl << endl;
//
//    // Re-print Deck and Hand
//    cout << "New: " << *newDeck << endl;
//    cout << "New: " << *newHand << endl;
//    cout << endl;
//
//    cout << "--------------------------------------------------" << endl << endl;
//
//    // Test play method
//    vector<Order*> orderList;
//
//    for (int i = 0; i < newHand->getCards().size(); i++) {
//        newHand->getCards()[i]->play(orderList, *newDeck);
//    }
//
//    cout << "--------------------------------------------------" << endl << endl;
//
//    cout << *newDeck << endl;
//    cout << *newHand << endl;
//
//    // Print program end
//    cout << "\n" << "End of driver class" << "\n" << "********************************************"
//        << endl << endl;
//
//    // Delete
//    system("pause");
//    cout << "----------------------------------------------" << endl;
//    cout << "Releasing the memory:" << endl;
//    delete newHand;
//    delete newDeck;
//    system("pause");
//    // Delete
//}

// EOF
