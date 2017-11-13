// file: deck.h
// comment: description of a deck
// author: lazukr
//

#include <stdlib.h>
#include <stdio.h>

#include "card.h"

#ifndef _DECK
#define _DECK

struct Deck {

    int maxNumOfCards;
    int numOfCards;
    struct Card * cards;

};

struct Deck getDeck(int maxNumOfCards);
void printDeck(struct Deck deck, int numPerRow);
void insertToDeck(struct Deck *deck, int suit, int rank);
void insertToDeckByCard(struct Deck *deck, struct Card card);
void setDeckFace(struct Deck *deck, int face);
void shuffleDeck(struct Deck *deck);
struct Card removeFromDeckByIndex(struct Deck *deck, int index);
void swapCards(struct Card *card1, struct Card *card2);


#endif

// end of file
// deck.h

