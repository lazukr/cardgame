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
#include "utils.h"

#define NUM_PLAYERS 2
#define NUM_SUITS 4
#define NUM_RANKS 13
#define HALF_DECK 26
#define FIELD_SIZE 14

// function: creates a new match
// inputs:
//      none
//
// output:
//      struct Match:
//          a match structure that is basically a container for the whole game
//
// comments:
//      A lot of setup is done here. We first create the two decks (red and black).
//      Then create the players that take these decks. We also choose the current
//      turn randomly.
//

struct Match newMatch() {

    struct Match thisMatch;
    struct Deck redDeck;
    struct Deck blackDeck;

    redDeck = getDeck(HALF_DECK);
    blackDeck = getDeck(HALF_DECK);

    for (int i = 0; i < HALF_DECK; i++) {
        
        insertToDeck(&redDeck, i / NUM_RANKS, i % NUM_RANKS);
        insertToDeck(&blackDeck, i / NUM_RANKS + 2, i % NUM_RANKS);
    }

    thisMatch.currentTurn = rand() % NUM_PLAYERS;
    thisMatch.players[0] = getPlayer(0, &redDeck);
    thisMatch.players[1] = getPlayer(1, &blackDeck);
    
    return thisMatch;
}

// function: this is meant to start the match
// inputs:
//      struct Match *match:
//          reference to the match
//
// output:
//      void
//
// comments:
//      this is what shuffles the cards and draw
//      them to field deck to be played. This can
//      be done in the newMatch function, but we don't 
//      want a initialization of the match struct to
//      include parts of the actual gameplay

void startMatch(struct Match *match) {
    
    shufflePlayerDeck(&match->players[0]);
    shufflePlayerDeck(&match->players[1]);
    
    for (int i = 0; i < FIELD_SIZE; i++) {
        
        drawToField(&match->players[0]);
        drawToField(&match->players[1]);
    } 
    
    playMatch(match);

}

// function: this is where the main playing loop is 
// inputs:
//      struct Match *match:
//          reference to the match
//
// output:
//      void
//
// comments:
//      this is the main match loop that serves
//      as the game basically. It should not leave this loop
//      until someone has won the game.
//

void playMatch(struct Match *match) {

    while ( !hasWon(match->players[0])
            && !hasWon(match->players[1])) {
        
        printf("\n\n");
        
        printSeparator();
        printf("It's player %d turn.\n", match->currentTurn);
    
        int enemy = 1 - match->currentTurn;
        int selected[2] = {-1, -1};
        struct Player *enemyPlayer = &match->players[enemy];
        struct Deck *enemyField = &match->players[enemy].fieldDeck;
        int validIndices = enemyField->numOfCards - 1;

        printf("Please select two cards from your opponent's field. \n");
        printPlayerInfo(*enemyPlayer);
        
        while (selected[0] < 0 || selected[0] > validIndices) {            
            printf("Please select the first card. Between 0 and %d\n", validIndices);
            getInput(&selected[0]);
        }
        
        flipFace(enemyField, 1, selected[0]);
        printDeck(*enemyField, -1);

        while (selected[1] < 0 || selected[1] > validIndices || selected[0] == selected[1]) {
            
            if (selected[0] == selected[1]) {
                printf("You cannot select the same card twice.\n");
            }

            printf("Please select the index of the second card. Between 0 and %d, but not the same as your first selection, %d\n", validIndices, selected[0]);
            getInput(&selected[1]);
        }

        flipFace(enemyField, 1, selected[1]);
        printDeck(*enemyField, -1);        

        if (enemyField->cards[selected[0]].rank == enemyField->cards[selected[1]].rank) {
            
            printf("You have found a matching pair! \n");
            printf("+1 point for you! \n");
            

            // remove them with larger indices first
            // avoids removing the wrong item 
            if (selected[0] > selected[1]) {
                fieldToGrave(enemyPlayer, selected[0]);
                fieldToGrave(enemyPlayer, selected[1]);

            } else {
                fieldToGrave(enemyPlayer, selected[1]);
                fieldToGrave(enemyPlayer, selected[0]);

            }
            
            drawToField(enemyPlayer);
            drawToField(enemyPlayer);

            
            match->players[match->currentTurn].score++;

        }  else {
            printf("You did not find a match. \n");
            setDeckFace(enemyField, 0);
        }

        match->currentTurn = enemy;
        
        printf("Press any button to continue.");
        getchar();
    }

}



// function: prints all details of the match

void printMatch(struct Match match) {
    
    printPlayerInfo(match.players[0]);
    printPlayerInfo(match.players[1]); 

}


// end of file
// match.c

