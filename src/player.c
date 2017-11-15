// file: player.c
// description: implements a player
// author: lazukr
//

#include <stdlib.h>
#include <stdio.h>

#include "player.h"
#include "card.h"
#include "deck.h"

// constants

#define FIELD_SIZE 14
#define HALF_DECK 26
#define SEPARATOR_COUNT 50
#define SEPARATOR_CHAR '='

// function: initalizes a player
// inputs:
//      int turn:
//          the turn that the player represents
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

struct Player getPlayer(int turn, struct Deck *deck) {

    struct Player newPlayer;
    newPlayer.turn = turn;
    newPlayer.score = 0;
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
//
// output:
//      void
//
// comments:
//

void FieldToGrave(struct Player *player) {
    
    if (isFull(player->graveDeck)) {
        //printf("Grave deck is full.\n");
        return;
    }


    struct Card copyCard;
    int indexOfLast = player->fieldDeck.numOfCards - 1;
    int fieldSuccess = removeFromDeckByIndex(&player->fieldDeck,
            indexOfLast, &copyCard);

    if (fieldSuccess) {
        insertToDeckByCard(&player->graveDeck, copyCard);
    }

}

void printPlayerInfo(struct Player player) {
    
    printSeparator(SEPARATOR_CHAR, SEPARATOR_COUNT);
    printf("Player: %-5d", player.turn);
    printf("Score: %d\n", player.score);
    printf("Cards left to draw: %d\n", player.drawDeck.numOfCards);
    printDeck(player.drawDeck, HALF_DECK/2);
    printSeparator(SEPARATOR_CHAR, SEPARATOR_COUNT);
    printf("Field:\n");
    printDeck(player.fieldDeck, FIELD_SIZE);
    printSeparator(SEPARATOR_CHAR, SEPARATOR_COUNT);
    printf("Grave:\n");
    printDeck(player.graveDeck, HALF_DECK/2);
    printSeparator(SEPARATOR_CHAR, SEPARATOR_COUNT); 

}

void printSeparator(char c, int numTimes) {
    
    for (int i = 0; i < numTimes; i++) {
        printf("%c", c);
    }
    printf("\n");
}


// end of file
// player.c
 
