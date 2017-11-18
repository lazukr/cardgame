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
#define SEP_CHAR '='
#define SEP_COUNT 50

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
        
        int playerID = match->currentTurn;
        int enemyID = 1 - playerID;
        int selectedCards[2] = {-1, -1};
        struct Player *enemyPlayer = &match->players[enemyID];


        printCurrentTurn(match->players[playerID]);
        selectCards(enemyPlayer, selectedCards);
        
        // flips the cards
        flipFace(&enemyPlayer->fieldDeck, 1, selectedCards[0]);
        flipFace(&enemyPlayer->fieldDeck, 1, selectedCards[1]);
 
        // displays the cards
        printSeparator(SEP_CHAR, SEP_COUNT);
        printPlayerField(*enemyPlayer);
        printf("\n");

        if (checkSelection(enemyPlayer->fieldDeck, selectedCards)) {
            
            // cards matches

            printf("You have found a matching pair! \n");
            printf("+1 point for you! \n");
            updatePlayerDecks(enemyPlayer, selectedCards);
            int currentScore = ++match->players[playerID].score;
            printf("Your score is now %d!\n", currentScore);

        } else {

            // cards don't match

            printf("You did not find a match. \n");
            setDeckFace(&enemyPlayer->fieldDeck, 0);
        }
        
        // updates turn
        match->currentTurn = enemyID;
        
        printf("Press any button to continue.");
        getchar();
    }

    // declare winner
    int winner = 0;
    if (hasWon(match->players[1])) {
        winner = 1;
    }

    displayWinner(winner);

    printf("\n\n\n");
}

// function: updates players deck
// inputs:
//      struct Player *enemyPlayer:
//          the enemy player
//      int *selected:
//          reference to the indices selected by current turn player
//
// output:
//      void
//
// comments:
//      the function only uses the first two indices of selected
//      thus I didn't bother passing in a length parameter

void updatePlayerDecks(struct Player *enemyPlayer, int *selected) {

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

}

// function: grabs the selection that the user inputs
// input:
//      struct Player *enemyPlayer:
//          reference to the enemy player
//      int *curSelection:
//          the current selection
// output:
//      void
//
// comments:
//      again, this function assumes the current selection is not one
//      of the possible values. Each loop on the playmatch, we reset the 
//      current selection to {-1, -1}, thus I do not check on it

void selectCards(struct Player *enemyPlayer, int *curSelection) {

    int validIndices = enemyPlayer->fieldDeck.numOfCards - 1; // arrays start from 0 to n - 1

    printPlayerInfo(*enemyPlayer);

    while ( (curSelection[0] < 0 || curSelection[0] > validIndices) // first value is between 0 and valid index
            && (curSelection[1] < 0 || curSelection[1] > validIndices) // second value is between 0 and valid index
            && (curSelection[0] == curSelection[1])) { // the two values are not equal each other
        
        printf("Please select the indices of two cards to reveal. ");
        printf("It must be from 0 and %d, and they cannot be the same values.\n", validIndices);
        
        // grabs the inputs
        scanf("%d %d", &curSelection[0], &curSelection[1]);
        while (getchar() != '\n'); // remove remaining characters from buffer
        printf("\n");
    }
}

// function: checks if the selected cards match
// inputs:
//      struct Deck enemyDeck:
//          enemy deck
//      int *selected:
//          indices selected by player to check
// output:
//      int:
//          true if they are equal rank, else false
//
// comments:
//

int checkSelection(struct Deck enemyDeck, int *selected) {

    int foundPair = 0;

    if(enemyDeck.cards[selected[0]].rank == enemyDeck.cards[selected[1]].rank) {
        
        foundPair = 1;
    }

    return foundPair;
}


void printCurrentTurn(struct Player player) {
   
    printSeparator('#', 26); 
    printf("#%25c\n", '#');
    printf("# It's Player %d turn.%5c\n", player.id, '#');
    printf("# Score: %02d%15c\n", player.score, '#');
    printf("# Cards left in deck: %2d #\n", player.drawDeck.numOfCards);
    printf("#%25c\n", '#');
    printSeparator('#', 26);
    printf("\n\n");
}

void updateTurn(struct Match *match) {
    
    match->currentTurn = 1 - match->currentTurn;

}

void displayWinner(int winner) {

    printf("/###   /###   #   #  /###   ####   /###  ##### /###   /#   \n");
    printf("#   #  #   #  ##  #  #      #   #  #   #   #   #   #  ###  \n");
    printf("#      #   #  # # #  #      #   #  #   #   #    ##    ###  \n");
    printf("#      #   #  #  ##  #  ##  ####/  #####   #     ##    #/  \n");
    printf("#   #  #   #  #   #  #   #  #  #   #   #   #   #   #       \n");
    printf(" ###/   ###/  #   #   ###/  #   #  #   #   #    ###/   #   \n");

    printf("Player %d has won!\n", winner);
}

void freeMatch(struct Match *match) {
    
    freePlayer(&match->players[0]);
    freePlayer(&match->players[1]);

}

// end of file
// match.c
 
