// file: player.c
// description: implements a player
// author: lazukr
//

#include <stdlib.h>
#include <stdio.h>

#include "player.h"
#include "card.h"
#include "deck.h"
#include "utils.h"
// constants

#define FIELD_SIZE 14
#define HALF_DECK 26
#define RANKS 13
#define SEP_CHAR '='
#define SEP_COUNT 50

// function: initalizes a player
// inputs:
//      int id:
//          the identity that the player represents
//          should be 0 or 1
//      
//      struct Deck:
//          deck that the player draws from
//
// output:
//      struct Player:  
//          structure containing details of a player
//
// comments:
//

struct Player getPlayer(int id, struct Deck *deck) {

    struct Player newPlayer;
    newPlayer.score = 0;
    newPlayer.id = id;
    newPlayer.drawDeck = *deck;
    newPlayer.fieldDeck = getDeck(FIELD_SIZE);
    newPlayer.graveDeck = getDeck(HALF_DECK);
    return newPlayer;
}

// function: puts a card from draw deck onto field deck
//
// inputs:
//      struct Player *player:
//          reference to a player
//
// output:
//      void
//
// comments:
//

void drawToField(struct Player *player) {

    if (isFull(player->fieldDeck)) {
        //printf("Field Deck is full. \n");
        return;
    }

    struct Card copyCard;
    int indexOfLast = player->drawDeck.numOfCards - 1;
    int drawSuccess = removeFromDeckByIndex(&player->drawDeck,
            indexOfLast, &copyCard);

    if (drawSuccess) {
        insertToDeckByCard(&player->fieldDeck, copyCard);
    }
}

// function: puts card from field deck onto grave deck
//
// inputs:
//      struct Player *player:
//          reference to a player
//      int index:
//          index of the card we are removing
//
// output:
//      void
//
// comments:
//

void fieldToGrave(struct Player *player, int index) {
    
    if (isFull(player->graveDeck)) {
        //printf("Grave deck is full.\n");
        return;
    }


    struct Card copyCard;
    int fieldSuccess = removeFromDeckByIndex(&player->fieldDeck,
            index, &copyCard);

    if (fieldSuccess) {
        insertToDeckByCard(&player->graveDeck, copyCard);
    }

}

// function: shuffles the draw deck of a player
//
// inputs:
//      struct Player *player:
//          reference to a player
//
// output:
//      void
//
// comments:
//

void shufflePlayerDeck(struct Player *player) {
    
    shuffleDeck(&player->drawDeck); 

}

int hasWon(struct Player player) {
    
    int hasWon = 0;
    
    // win condition is when you've cleared both
    // the enemy's field and draw deck
    // since it is half the standard 52 playing cards
    // there are 26 cards in their deck
    // and since cards are removed in pairs
    // 26 / 2 = 13
    if (player.score == HALF_DECK / 2) {
        hasWon = 1;
    } 
    return hasWon;
}

void printPlayerInfo(struct Player player) {

    printPlayerID(player);
    if (!isEmpty(player.graveDeck)) {
        printPlayerGrave(player);
    }

    printPlayerField(player);
    printf("\n");
}

void printPlayerID(struct Player player) {
    printf("Player %d's Stats\n", player.id);
    printSeparator(SEP_CHAR, SEP_COUNT);
}

void printPlayerStats(struct Player player) {
    
    printf("Score: %-3d", player.score);
    printf("Cards left to draw: %d\n", player.drawDeck.numOfCards);
}

void printPlayerGrave(struct Player player) {
    
    printf("Grave:\n");
    printDeck(player.graveDeck, HALF_DECK/2);
    printSeparator(SEP_CHAR, SEP_COUNT);
}

void printPlayerField(struct Player player) {
    printf("Field:\n");
    for (int i = 0; i < player.fieldDeck.numOfCards; i++) {
        printf("%02d ", i);
    }
    printf("\n");
    printDeck(player.fieldDeck, FIELD_SIZE);
    printSeparator(SEP_CHAR, SEP_COUNT);
}


// function: free player's decks
void freePlayer(struct Player *player) {
    
    freeDeck(&player->drawDeck);
    freeDeck(&player->fieldDeck);
    freeDeck(&player->graveDeck);
}

// end of file
// player.c

