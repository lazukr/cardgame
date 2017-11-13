// file: card.h
// description: description of a card
// author: lazukr

#ifndef _CARD
#define _CARD

struct Card {
    
    int suit;
    int rank;
    int face;
};

struct Card getCard(int suit, int rank);
void printCard(struct Card card);

#endif

// end of file
// card.h
