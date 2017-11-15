// player.h
// comment: description of a player
// author: lazukr
//

#include "card.h"
#include "deck.h"

#ifndef _PLAYER
#define _PLAYER

struct Player {

    int turn;
    int score;
    struct Deck fieldDeck;
    struct Deck drawDeck;
    struct Deck graveDeck;
};

struct Player getPlayer(int turn, struct Deck *deck);
void drawToField(struct Player *player);
void fieldToGrave(struct Player *player);
void shufflePlayerDeck(struct Player *player);
void printPlayerInfo(struct Player player);
void printSeparator(char c, int numTimes);


#endif

// end of file
// player.h
