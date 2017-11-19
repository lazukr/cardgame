// player.h
// comment: description of a player
// author: lazukr
//

#include "card.h"
#include "deck.h"

#ifndef _PLAYER
#define _PLAYER

struct Player {

    int id;
    int score;
    struct Deck fieldDeck;
    struct Deck drawDeck;
    struct Deck graveDeck;
};

struct Player getPlayer(int turn, struct Deck *deck);
void drawToField(struct Player *player);
void fieldToGrave(struct Player *player, int index);
void shufflePlayerDeck(struct Player *player);
int hasWon(struct Player player);
void printPlayerInfo(struct Player player);
void printPlayerID(struct Player player);
void printPlayerStats(struct Player player);
void printPlayerField(struct Player player);
void printPlayerGrave(struct Player player);
void freePlayer(struct Player *player);

#endif

// end of file
// player.h
