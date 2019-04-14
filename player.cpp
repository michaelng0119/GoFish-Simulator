// FILE:  player.h
// written by Roger Priebe
// 1/22/08 (revised 9/2/08)
// This class represents a player in a card game that takes "tricks"
// The "Books" represent a container for holding tricks


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "player.h"
#include "card.h"
using namespace std;


    string Player::getName() const{
        return myName;
    }

    void Player::addCard(Card c)  //adds a card to the hand
    {
        myHand.push_back(c);
    }

    void Player::bookCards(Card c1, Card c2)
    {
        myHand.erase(find(myHand.begin(),myHand.end(),c1));
        myHand.erase(find(myHand.begin(),myHand.end(),c2));
        myBook.push_back(c1); myBook.push_back(c2);
    }   
         

    //OPTIONAL
    // comment out if you decide to not use it
    //this function will check a players hand for a pair. 
    //If a pair is found, it returns true and populates the two variables with the cards tha make the pair.
    bool Player::checkHandForBook(Card &c1, Card &c2)
    {
        for(int i = 0;i<myHand.size();i++){
            for(int j = i+1;j<myHand.size();j++){
                if(myHand[i].getRank() == myHand[j].getRank()){
                    c1 = myHand[i];
                    c2 = myHand[j];
                    return true;
                }
            }
        }
        return false;
    }


    //OPTIONAL
    // comment out if you decide to not use it    
    //Does the player have a card with the same rank as c in her hand?
    bool Player::rankInHand(Card c) const
    {
        for(int i = 0;i<myHand.size();i++){
            if(c.getRank() == myHand[i].getRank()) return true;
        }
        return false;
    } 
    

    //uses some strategy to choose one card from the player's
    //hand so they can say "Do you have a 4?"
    Card Player::chooseCardFromHand() const
    {
        return myHand[rand()%myHand.size()];
    } 
    

    //Does the player have the card c in her hand?
    bool Player::cardInHand(Card c) const
    {

        if(find(myHand.begin(),myHand.end(),c) == myHand.end()) return false;
        return true;
    }

    
    //Remove the card c from the hand and return it to the caller
    Card Player::removeCardFromHand(Card c) 
    {
        for(int i = 0; i < myHand.size();i++){
            if(c.getRank() == myHand[i].getRank()){
                vector<Card>::iterator card = find(myHand.begin(),myHand.end(),myHand[i]);
                Card temp = *card;
                myHand.erase(card);
                return temp;
            }
        }
    }

    string Player::showHand() const
    {
        string hand = "";

        for(int i = 0;i<myHand.size();i++){
            hand += myHand[i].toString();
            hand += " "; 
        }
        
        return hand;
    }

    string Player::showBooks() const 
    {
        string book = "";

        for(int i = 0;i<myBook.size();i = i + 2){
            book = book + myBook[i].toString() + "+" + myBook[i+1].toString();
            book += " "; 
        }
        
        return book;
    }

   

    int Player::getHandSize() const
    {
        return(myHand.size());
    }
 
    int Player::getBookSize() const
    {
        return(myBook.size()/2);
    } 
       
    //OPTIONAL
    // comment out if you decide to not use it
    //this function will check a players hand for a pair. 
    //If a pair is found, it returns true and populates the two variables with the cards tha make the pair.

    //bool checkHandForPair(Card &c1, Card &c2);

    //OPTIONAL
    // comment out if you decide to not use it    
    //Does the player have a card with the same rank as c in her hand?
    //e.g. will return true if the player has a 7d and the parameter is 7c
    
    //bool sameRankInHand(Card c) const; 
    
    
