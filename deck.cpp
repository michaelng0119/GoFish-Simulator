// FILE: deck.cpp
// written by Owen Astrachan and Roger Priebe
// this class respresents a deck of cards
// When a Deck is constructed, it contains 52 cards
// in a "regular" order (aces, twos, threes, ... , kings)
//
// Shuffling a deck makes it consist of 52 cards in a random order
//
// dealCard() returns a card from the deck and decreases the
// number of cards in the deck (returned by size())
// The idea is that after shuffling, calling dealCard() 52 times
// returns each card in the deck after shuffling.
//
// Calling shuffle again replenishes the deck with 52 cards.

#include <ctime>
#include <cstdlib>
#include "card.h"
#include "deck.h"
    
    Deck::Deck()           // pristine, sorted deck
    {
       srand((unsigned)time(0));
       int i = 0;        
       myIndex = 0;

        for(int suit=0;suit<4;suit++){          //Two nested for loops, one for the suit
             for(int rank=1;rank<=13;rank++){   //one for the rank
                     myCards[i] = Card(rank, Card::Suit(suit));
                     i++;
             }
        }
    }

    void Deck::shuffle()   // shuffle the deck, all 52 cards present
    {
        myIndex = 0;    

        for (int i=0;i<208;i++){

            int ran1 = rand()%52; int ran2 = rand()%52;
            Card temp = myCards[ran1];
            myCards[ran1] = myCards[ran2];
            myCards[ran2] = temp;
        }
    }
            
    Card Deck::dealCard()   // get a card, after 52 are dealt, fail 
    {
        if(myIndex==52) return Card(1,Card::Suit(0));    //If all cards are dealt, deal ace of spades
        else{
            myIndex++;
            return(myCards[myIndex-1]);
        }
    }
//    int  size() const; // # cards left in the deck

    void Deck::showDeck()
    {
        for(int i = myIndex;i<SIZE;i++){
            cout << myCards[i];
        }
        cout << endl;
    }  
