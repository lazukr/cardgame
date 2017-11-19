// file: deck.c
// comment: implementation of a deck
// author: lazukr
//


#include <stdlib.h>
#include <stdio.h>

#include "card.h"
#include "deck.h"

// function: initializes a deck
// inputs:
//      int maxNumOfCards:
//           maximum number of cards in deck 
//      
// output:
//      struct Deck:
//           structure containg details of a Deck
//
// comments:
//      
struct Deck getDeck(int maxNumOfCards) {
    
    struct Deck newDeck;
    newDeck.maxNumOfCards = maxNumOfCards;
    newDeck.numOfCards = 0;
    newDeck.cards = (struct Card *)malloc(sizeof(struct Card)*maxNumOfCards);
    //newDeck.cards;
    return newDeck;
}

// function: inserts card into deck 
// inputs:
//      struct Deck *deck:
//           reference of deck to insert card into
//      int suit:
//           suit of the card we want to insert
//      int rank:
//           rank of the card we want to insert
//
// output:
//      void
//
// comments:
//      this declares the card in the function and inserts it into the deck
//

void insertToDeck(struct Deck *deck, int suit, int rank) {
    
    if (isFull(*deck)) {
        printf("Deck is full.\n");
        return;
    }

    struct Card tempCard = getCard(suit, rank);
    deck->cards[deck->numOfCards] = tempCard;
    deck->numOfCards++;
}

// function: inserts card into deck
// inputs:
//      struct Deck *deck:
//           reference of the deck to insert card into
//      struct Card card:
//           card to insert into deck
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
//      struct Deck *deck:
//          reference of the deck
//      int face:
//           value of face to set cards to
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

// function: flips a card of the specified index in the deck to the
//           value of the face
//
// inputs:
//      struct Deck *deck:
//          reference to the deck
//      int face:
//          value of the face to set to
//      int index:
//          index of the card in deck
//
// output:
//      void
//
// comments:
//

void flipFace(struct Deck *deck, int face, int index) {
    
    if (index < deck->numOfCards) {
        deck->cards[index].face = face;
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

// function: swaps two cards
// inputs:
//      struct Card *card1:
//          reference to first card
//      struct Card *card2:
//          reference to second card
//
// output:
//      void
//
// comments:
//      for internal use
//

// function: removes card from deck by index
//  inputs:
//      struct Deck *deck:
//          reference to the deck
//      int index:
//          index for the card in deck that we want to remove
//      struct Card *card:
//          reference to a card struct that will take on the value of
//          the found card if it exists
//
// output:
//      int:
//          0 indicates no matches, 1 indicates a match was found and removed
//
// comments:
//      returns struct Card in case we need to do something with it
//

int removeFromDeckByIndex(struct Deck *deck, int index, struct Card *copyCard) {
    
    int success = 0;

    // makes sure index is within range
    // if not, we will return 0 for removal failure
    if (index >= 0 && index < deck->numOfCards) {
        
        *copyCard = deck->cards[index];
        deck->numOfCards--;
        
        // shift all cards down the array
        // this is inefficient O(n) time complexity each time
        // but we will use this for the time being
        for (int i = index; i < deck->numOfCards; i++) {
            deck->cards[i] = deck->cards[i+1];
        }

        success = 1;

    }
    
    return success;
}


void swapCards(struct Card *card1, struct Card *card2) {
    
    struct Card tempCard = *card1;
    *card1 = *card2;
    *card2 = tempCard;
}

int isFull(struct Deck deck) {
    int full = 0;
    
    if (deck.numOfCards == deck.maxNumOfCards) {
        full = 1;
    }
    return full;
}

int isEmpty(struct Deck deck) {
    
    int empty = 0;

    if (deck.numOfCards == 0) {
        empty = 1;
    }
    return empty;
}


// function: prints the whole deck
// inputs:
//      struct Deck deck:
//          deck that we want to print
//      int numPerRow:
//          number of cards to display per row
//
// output:
//      void
//
// comments:
//      

void printDeck(struct Deck deck, int numPerRow) {
   
    if (isEmpty(deck)) {
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

// function: free the deck's cards

void freeDeck(struct Deck *deck) {
    free(deck->cards);
}

// end of file
// deck.c
