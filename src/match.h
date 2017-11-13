// file: match.h
// description: defines a match, aka the 'engine' of the game
// author: lazukr
//

#include <stdlib.h>
#include <stdio.h>

#include "player.h"
#include "deck.h"
#include "card.h"

#ifndef _MATCH
#define _MATCH

#define NUM_PLAYERS 2
#define NUM_SUITS 4

struct Match {
    
    struct Deck masterDeck[NUM_SUITS];
    struct Player players[NUM_PLAYERS];
    int currentTurn;

};

struct Match newMatch();
void startMatch(struct Match *match);


#endif

// end of file
// match.h
