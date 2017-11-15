// file: game.c
// description: main file for the game
// author: lazukr
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h> // for randomizing things


#include "./src/card.h"
#include "./src/deck.h"
#include "./src/player.h"
#include "./src/match.h"

#define NUM_SUITS 4 
#define NUM_RANKS 13


int main() {

    srand(time(NULL));

    printf("Hello World!\n");
        
    struct Deck thisDeck;
    struct Player player0;

    thisDeck = getDeck(NUM_SUITS*NUM_RANKS);

    for (int i = 0; i < NUM_SUITS*NUM_RANKS; i++) {
        
        insertToDeck(&thisDeck, i / NUM_RANKS, i % NUM_RANKS);
    }

    player0 = getPlayer(0, &thisDeck);
    shuffleDeck(&thisDeck);
    setDeckFace(&thisDeck, 1);
    printPlayerInfo(player0);

    for (int i = 0; i < NUM_RANKS*5; i++) {
        drawToField(&player0);
    }
    printPlayerInfo(player0);


    return 0;
}

// end of file
// game.c

