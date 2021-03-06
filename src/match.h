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
    
    struct Player players[NUM_PLAYERS];
    int currentTurn;

};

struct Match newMatch();
void startMatch(struct Match *match);
void playMatch(struct Match *match);

void updatePlayerDecks(struct Player *enemyPlayer, int *selected);
void selectCards(struct Player *enemyPlayer, int *selected);
int checkSelection(struct Deck enemyDeck, int *selected);

void printCurrentTurn(struct Player player);
void updateTurn(struct Match *match);
void displayWinner(int winner);
void freeMatch(struct Match *match);

#endif

// end of file
// match.h
