// file: deck.c
// comment: implementation of a deck
// author: lazukr
//


#include <stdlib.h>
#include <stdio.h>

#include "deck.h"

// function: initializes a deck
// inputs:
//      int maxNumOfCards, maximum number of cards in deck 
//      
// output:
//      struct Deck, structure containg details of a Deck
//
// comments:
//      
struct Deck getDeck(int maxNumOfCards) {
    
    struct Deck newDeck;
    newDeck.maxNumOfCards = maxNumOfCards;
    newDeck.numOfCards = 0;
    newDeck.cards = (struct Card *)malloc(sizeof(struct Card)*maxNumOfCards);
    return newDeck;
}

// function: inserts card into deck 
// inputs:
//      struct Deck *deck, reference of deck to insert card into
//      int suit, suit of the card we want to insert
//      int rank, rank of the card we want to insert
//
// output:
//      void
//
// comments:
//      this declares the card in the function and inserts it into the deck
//

void insertToDeck(struct Deck *deck, int suit, int rank) {
    
    if (deck->numOfCards == deck->maxNumOfCards) {
        printf("Deck is full.\n");
        return;
    }

    struct Card tempCard = getCard(suit, rank);
    deck->cards[deck->numOfCards] = tempCard;
    deck->numOfCards++;
}

// function: inserts card into deck
// inputs:
//      struct Deck *deck, reference of the deck to insert card into
//      struct Card card, card to insert into deck
//
// output:
//      void
//
// comments:
//      checks if deck is full, if full print an message about it
//      else insert element into deck

void insertToDeckByCard(struct Deck *deck, struct Card card) {
    
    if (deck->numOfCards == deck->maxNumOfCards) {
        printf("Deck is full.\n");
        return;
    }

    deck->cards[deck->numOfCards] = card;
    deck->numOfCards++;
}

// function: set all cards' face in deck to value of face
// inputs:
//      struct Deck *deck, reference of the deck
//      int face, value of face to set cards to
//
// output:
//      void
//
// comments:
//
void setDeckFace(struct Deck *deck, int face) {
    
    for (int i = 0; i < deck->numOfCards; i++) {
        
        deck->cards[i].face = face;
    }
}

// function: shuffles the deck
// inputs:
//      struct Deck *deck:
//          deck that we want to shuffle
//
// output:
//      void
//
// comments:
//      uses the Fisher-Yates shuffle
//

void shuffleDeck(struct Deck *deck) {

    for (int i = deck->numOfCards-1; i > 0; i--) {
        
        int randomIndex = rand() % (i + 1);
        swapCards(&deck->cards[i], &deck->cards[randomIndex]);
    }
}

void swapCards(struct Card *card1, struct Card *card2) {
    
    struct Card tempCard = *card1;
    *card1 = *card2;
    *card2 = tempCard;
}



void printDeck(struct Deck deck, int numPerRow) {
   
    if (deck.numOfCards == 0) {
        printf("Empty Deck.\n");
        return;
    }
    
    for (int i = 0; i < deck.numOfCards; i++) {
        
        printCard((deck.cards[i]));
        
        if ((numPerRow > 0) 
            && (i + 1 < deck.numOfCards)
            && ((i + 1) % numPerRow == 0)) {

            printf("\n");
        }

    }
    printf("\n");

}

// end of file
// deck.c
