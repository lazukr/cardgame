// file: match.c
// description: implements a match
// author: lazukr
//

#include <stdlib.h>
#include <stdio.h>

#include "player.h"
#include "deck.h"
#include "card.h"
#include "match.h"

#define NUM_PLAYERS 2
#define NUM_SUITS 4
#define NUM_RANKS 13



struct Match newMatch() {

    struct Match thisMatch;
    thisMatch.currentTurn = rand() % 2;
    
    return thisMatch;
}



void startMatch(struct Match *match) {





}

// end of file
// match.c

