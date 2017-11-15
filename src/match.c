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
#define HALF_DECK 26


struct Match newMatch() {

    struct Match thisMatch;
    struct Deck redDeck;
    struct Deck blackDeck;

    redDeck = getDeck(HALF_DECK);
    blackDeck = getDeck(HALF_DECK);

    for (int i = 0; i < NUM_SUITS*NUM_RANKS/2; i++) {
        
        insertToDeck(&redDeck, i / NUM_RANKS, i % NUM_RANKS);
        insertToDeck(&blackDeck, i / NUM_RANKS + 2, i % NUM_RANKS);
    }

    thisMatch.currentTurn = rand() % NUM_PLAYERS;
    thisMatch.players[0] = getPlayer(0, &redDeck);
    thisMatch.players[1] = getPlayer(1, &blackDeck);
    
    return thisMatch;
}



void startMatch(struct Match *match) {
    
    shufflePlayerDeck(&match->players[0]);
    shufflePlayerDeck(&match->players[1]);

}

void printMatch(struct Match match) {
    
    printPlayerInfo(match.players[0]);
    printPlayerInfo(match.players[1]); 

}


// end of file
// match.c

