// file: game.c
// description: main file for the game
// author: lazukr
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h> // for randomizing things
#include <ctype.h> // checking types 

#include "./src/card.h"
#include "./src/deck.h"
#include "./src/player.h"
#include "./src/match.h"
#include "./src/utils.h"

#define NUM_SUITS 4 
#define NUM_RANKS 13

void printMenu();
void printInvalidInput();
void printStartGame();

int main() {

    srand(time(NULL));
    int run = 1;
    int current;

    printf("Welcome to Cardgame!\n\n");

    while (run) {
        printMenu();
        getInput(&current);
        switch (current) {
            case 1:
                printStartGame();
                break;
            
            case 2:
                exit(1);
                break;

            default:
                printInvalidInput();
                break;
        }
    }

    return 0;
}

void printMenu() {
    
    printf("You are currently in the the main menu.\n");
    printf("Please select from these options: \n");
    printf("1. Start a new game \n");
    printf("2. Quit game \n");

}

void printInvalidInput() {
    
    printf("Your input is invalid. \n");
    printf("Please try again. \n");

}

void printStartGame() {
    
    printf("Starting game... \n");

    struct Match thisMatch;
    thisMatch = newMatch();
    
    //setDeckFace(&thisMatch.players[0].drawDeck, 1);
    //setDeckFace(&thisMatch.players[1].drawDeck, 1);

    startMatch(&thisMatch);
    freeMatch(&thisMatch);
}

// end of file
// game.c

