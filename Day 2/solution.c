#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Functions
FILE *get_file (char file_name[]);
int game_calculator (char move, char oponent_move);
int prediction_calculator (char outcome, char oponent_move);

int main (void) {
    FILE *file = get_file("./input.txt");
    // Initialize Variables
    char output[10];
    int pscore = 0;
    int iscore = 0;

    while (fgets(output, sizeof(output), file)) {
        iscore = game_calculator(output[2], output[0]) + iscore;
        pscore = prediction_calculator(output[2], output[0]) + pscore;
    }

    printf("Gameplay Score: %d\n", iscore);
    printf("Predicted Score: %d\n", pscore);
    fclose(file);
}

// Function that converts a file to a list of str's, each of which is a line
FILE *get_file (char file_name[])  {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("NULL File at %s\n", file_name);
    } else {
        printf("Successfully read file\n");
    }
    return file;
}

int game_calculator (char move, char oponent_move) {
    // Convert char to ascii then reduce to 0 (rock), 1 (paper), and 2 (scissors)

    int imove = ((int) move) - 88;
    int ioponent_move = ((int) oponent_move) - 65;

    if (ioponent_move == imove + 1 || ioponent_move == imove - 2) {
        // This is a loss
        return (imove + 1);
    } else if (ioponent_move == imove) {
        // This is a tie
        return (imove + 4);
    } else if (ioponent_move == imove - 1 || ioponent_move == imove + 2) {
        // This is a win
        return (imove + 7);
    }
    return 0;
}

int prediction_calculator (char outcome, char oponent_move) {
    // Convert char to ascii then reduce to 0 (rock), 1 (paper), and 2 (scissors)
    int ioponent_move = ((int) oponent_move) - 65;
    int imove;

    if (outcome == 'X') {
        imove = (ioponent_move < 1) ? 2 : ioponent_move - 1;
        return (imove + 1);
    } else if (outcome == 'Y') {
        imove = ioponent_move;
        return (imove + 4);
    } else if (outcome == 'Z') {
        imove = (ioponent_move > 1) ? 0 : ioponent_move + 1;
        return (imove + 7);
    }


    return 0;
}