#include <iostream>
#include <fstream>

#include <cstdlib>
#include <vector>
#include "card.h"
#include "deck.h"
#include "player.h"

using namespace std;

//Draws numCards from the deck and places into the player's hand
void dealHand(Deck &d, Player &p, int numCards, int &deckCards);

//Asking sequence, will return the card asked for
Card playerAsk(Player p, ofstream& outfile);

//Response sequence. Will check to see if matching rank is inside hand
//If matching rank found, the card will be erased and the other player will book
//the rank.
//If matching rank not found, asking player will draw a card and the turn will increment
void playerResponse(ofstream& outfile, Deck &d, Player &pRespond, Player &pAsk, Card c, int &turn, int &deckCards);

int main()
{

    ofstream outfile ("gofish_results.txt");              //outfile is the name of function used to write to gofish_results.txt

    Deck d;
    d.shuffle();
    int deckCards = 52;

    Player p1("Roger");
    Player p2("Jonathon");

    dealHand(d,p1,7,deckCards);
    dealHand(d,p2,7,deckCards);
    int turn = 0;

    Card book1;
    Card book2;

                                                          //Initial check for books in dealt hands
    if(p1.checkHandForBook(book1,book2)){
        while(p1.checkHandForBook(book1,book2)){
            p1.bookCards(book1,book2);
        }
        outfile << p1.getName() << " starts with books - " << p1.showBooks() << endl;
    }
    if(p2.checkHandForBook(book1,book2)){
        while(p2.checkHandForBook(book1,book2)){
            p2.bookCards(book1,book2);
        }
        outfile << p2.getName() << " starts with books - " << p2.showBooks() << endl;
    }

    outfile << p1.getName() << " starts with " << p1.showHand() << endl;
    outfile << p2.getName() << " starts with " << p2.showHand() << endl;



                                                           //Main loop for the game
                                                           //Break conditions : either player's book size is majority
                                                           //or the number of cards in the deck is 0
                                                           //Player's turn is determined by int term that alternates 0 and 1
    while(p1.getBookSize()<27 && p2.getBookSize()<27 && deckCards!=0){
        outfile << endl;

        if(turn == 0){
        Card c = playerAsk(p1,outfile);
        playerResponse(outfile,d,p2,p1,c,turn,deckCards);

        }
        else{
        Card c = playerAsk(p2,outfile);
        playerResponse(outfile,d,p1,p2,c,turn,deckCards);
        }
    }

        outfile << endl;


                                                            //Print statements for win condition
    if (p1.getBookSize()==27)
        outfile << p1.getName() << " wins with a book size of " << p1.getBookSize() << endl;
    else if (p2.getBookSize()==27)
        outfile << p2.getName() << " wins with a book size of " << p2.getBookSize() << endl;
    else if (deckCards == 0){
        if (p1.getBookSize() > p2.getBookSize())
            outfile << "Deck is empty" << endl <<p1.getName() << " wins with a book size of " << p1.getBookSize() << endl;
        else
            outfile << "Deck is empty" << endl <<p2.getName() << " wins with a book size of " << p2.getBookSize() << endl;
    }   

    outfile << endl << p1.getName() << "'s ending hand is " << p1.showHand() << endl;
    outfile << p1.getName() << "'s ending books were " << p1.showBooks() << endl << endl;

    outfile << p2.getName() << "'s ending hand is " << p2.showHand() << endl;
    outfile << p2.getName() << "'s ending books were " << p2.showBooks() << endl << endl;

    outfile.close();
}

//Draws numCards from the deck and places into the player's hand
void dealHand(Deck &d, Player &p, int numCards, int &deckCards)
{
    for(int i = 0; i < numCards; i++){
        p.addCard(d.dealCard());
        deckCards--;
    }
}

//Asking sequence, will return the card asked for
Card playerAsk(Player p, ofstream& outfile)
{
    Card temp = p.chooseCardFromHand();                // Random card is chosen from hand and asked for

    outfile << p.getName() <<  " asks - Do you have a " << temp.rankString(temp.getRank()) << "?" << endl;
    return temp;
} 

//Response sequence. Will check to see if matching rank is inside hand
//If matching rank found, the card will be erased and the other player will book
//the rank.
//If matching rank not found, asking player will draw a card and the turn will increment
void playerResponse(ofstream& outfile, Deck &d, Player &pRespond, Player &pAsk, Card c, int &turn, int &deckCards)
{
    outfile << pRespond.getName() << " says - ";
    
    if(pRespond.rankInHand(c)){
        outfile << "Yeah, I have a " << c.rankString(c.getRank()) << endl;

        pAsk.addCard(pRespond.removeCardFromHand(c));  //Corresponding ranked card will be transferred into asking player
        Card c1; Card c2;
        pAsk.checkHandForBook(c1,c2);                  //asking player will then check for a book and book them.
        pAsk.bookCards(c1,c2);
        outfile << pAsk.getName() << " books the " << c.rankString(c.getRank()) << endl;  
    }    
                
    else{
        outfile << "Go Fish" << endl;

        Card draw = d.dealCard();                      //Player will draw a card and turn will increment
        pAsk.addCard(draw);
        outfile << pAsk.getName() << " draws " << draw << endl;
        turn = (turn+1)%2;
        deckCards--;
    }   
}
