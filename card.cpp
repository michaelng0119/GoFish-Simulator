//File Name: card.cpp
//
//Written by Owen Astrachan and Roger Priebe
// This class represents a playing card, i.e., "ace of spades"
// a Card is constructed from a rank (int in range 1..13)
// and a suit (Card::spades, Card::hearts, Card::diamonds,
// Card::clubs)
//
// Cards should be created by a Deck (see deck.h), a Deck returns
// good cards
// The function toString() converts a card to a string, e.g., to print
//
// Accessor functions include
//
// int GetRank()      -- returns 1, 2, ..., 13 for ace, two, ..., king
//
// bool SameSuitAs(c) -- returns true if same suit as Card c
//
// string suitString() -- returns "s", "h", "d" or "c"
//
// Note that the Ace is represented by 1 and the King by 13


#include <iostream>
#include <string>
#include <vector>
#include "card.h"
using namespace std;

    Card::Card()          // default, ace of spades
    {
        myRank = 1;
        mySuit = spades;
    }

    Card::Card(int rank, Suit s)
    {
        myRank = rank;
        mySuit = s;
    }

    string Card::toString()              const  // return string version e.g. Ac 4h Js
    {
        return(rankString(myRank) + suitString(mySuit));
    }

    bool Card::sameSuitAs(const Card& c) const  // true if suit same as c
    {
        return(mySuit == c.mySuit);
    }

    int  Card::getRank()                 const  // return rank, 1..13
    {
        return myRank;
    }

    string Card::suitString(Suit s)      const  // return "s", "h",...
    {
        switch(s){
            case spades: return("s");
            case hearts: return("h");
            case diamonds: return("d");
            case clubs: return("c");
        }
    }    

    string Card::rankString(int r)       const  // return "A", "2", ..."Q"  
    {
        string rank[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

        return rank[r-1];
    }


//I had difficulty getting to_string to compile so I elected to use a vector method instead
/*
        string rank;

        switch(r){
            case 1:  rank = "A";
                     break;
            case 11: rank = "J";
                     break;
            case 12: rank = "Q";
                     break;
            case 13: rank = "K";
                     break;
            default: rank = to_string(r);
                     break;
        }
        return rank;
*/        
    
    bool Card::operator == (const Card& rhs) const
    {
        return((myRank==rhs.myRank)&&(mySuit==rhs.mySuit));
    }

    bool Card::operator != (const Card& rhs) const
    {
        return !(*this == rhs);
    }

ostream& operator << (ostream& out, const Card& c)
    {
        out << c.toString();
        return out;
    }


