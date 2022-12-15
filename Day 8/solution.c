#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Functions
FILE *get_file (char file_name[]);

int main (void) {
    int squaresize = 99;
    FILE *file_name = get_file("./input.txt");
    printf ("Assuming the input is a %d x %d grid: \n", squaresize, squaresize);
    int **treegrid = malloc(squaresize * sizeof(int *));
    char output[100];
    int i,j,result = 0;
    for (i = 0; i < squaresize; i ++) {
        fgets(output, 100, file_name);
        treegrid[i] = malloc(squaresize * sizeof(int));
        for (j = 0; j < squaresize; j ++ ) {
            *(*(treegrid + i) + j) = output[j] - 48;
        }
        fgets(output, 100, file_name);
    }

    for (i = 1; i < squaresize - 1; i ++) {
        for (j = 1; j < squaresize - 1; j ++) {
            int x, counter = 0;
            for (x = i - 1; x > -1; x -- ) {
                if (treegrid[x][j] >= treegrid[i][j]) {
                    break;
                }
                if (x == 0) {
                    counter ++;
                }
            }
            for (x = j - 1; x > -1; x -- ) {
                if (treegrid[i][x] >= treegrid[i][j]) {
                    break;
                }
                if (x == 0) {
                    counter ++;
                }
            }
            for (x = i + 1; x < squaresize; x ++ ) {
                if (treegrid[x][j] >= treegrid[i][j]) {
                    break;
                }
                if (x == squaresize-1) {
                    counter ++;
                }
            }
            for (x = j + 1; x < squaresize; x ++ ) {
                if (treegrid[x][j] >= treegrid[i][j]) {
                    break;
                }
                if (x == squaresize-1) {
                    counter ++;
                }
            }
            if (counter) {result ++; break;}
        }
    }

    printf("%d trees are visible.\n", result + ((squaresize - 1) * 4));
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