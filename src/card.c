// file: card.c
// description: implementation of a card
// author: lazukr

#include <stdlib.h>
#include <stdio.h>

#include "card.h"

// constants
static char SUITS[4][6] = {"\u2665", "\u2666", "\u2660", "\u2663"};
static char RANKS[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K'};
static char * FACE_DOWN_ASCII = "\u2588";

// function: initalizes a Card struct and returns it
// inputs:
//      int suit, the suit of the card
//      int rank, the rank of the card
// output:
//      struct Card, structure containing details of a card
// 
// comments:
//      SUIT GUIDE
//      HEARTS      - 0
//      SPADES      - 1
//      ClUBS       - 2
//      DIAMONDS    - 3
//
//      RANK GUIDE
//      ACE         - 1
//      NUMBERS     - 2 ~ 10
//      JACK        - 11
//      QUEEN       - 12
//      KING        - 13
struct Card getCard(int suit, int rank) {
    struct Card newCard;
    newCard.suit = suit;
    newCard.rank = rank;
    newCard.face = 0;
    return newCard;
}

void printCard(struct Card card) {
     if (card.face) {
        printf("%s%c ", SUITS[card.suit], RANKS[card.rank]);
     } else {
        printf("%s%s ", FACE_DOWN_ASCII, FACE_DOWN_ASCII);
     }
}

// end of file
// card.c
