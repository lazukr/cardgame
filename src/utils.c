// file: utils.c
// description: implementations of all general utility functions
// author: lazukr
//
#include <stdlib.h>
#include <stdio.h>

#define SEPR_CHAR '='
#define SEPR_NUM 50
void getInput(int *input) {

    scanf("%d", input);

    // prevents buffer from staying full if scanf
    // does not pick up an integer result
    
    while (getchar() != '\n');
    printf("\n");
}

void printSeparator() {
    
    for (int i = 0; i < SEPR_NUM; i++) {
        printf("%c", SEPR_CHAR);
    }
    printf("\n");

}

// end of file
// utils.c
