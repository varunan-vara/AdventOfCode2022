#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Functions
FILE *get_file (char file_name[]);

int main (void) {

    FILE *file = get_file("./input.txt");
    int bigRange[2], smallRange[2], c1, c2, c3, c4, counterOne = 0, counterTwo = 0, i;
    

    for (i = 0; i < 1000; i ++) {
        fscanf(file, "%d-%d,%d-%d", &c1, &c2, &c3, &c4);
        if (c2 - c1 > c4 - c3) {
            bigRange[0] = c1, bigRange[1] = c2, smallRange[0] = c3, smallRange[1] = c4;
        } else {
            bigRange[0] = c3, bigRange[1] = c4, smallRange[0] = c1, smallRange[1] = c2;
        }
        if (smallRange[0] >= bigRange[0] && smallRange[1] <= bigRange[1]) {
            counterOne ++;
        }
        if (c4 > c2) {
            if (c3 > c2) {
                counterTwo ++;
            }
        } else if (c4 < c2){
            if (c1 > c4) {
                counterTwo ++;
            }
        }
    }

    printf("Number of Total Overlaps: %d\nNumber of Any Overlaps: %d\n", counterOne, 1000 - counterTwo);

    return 0;
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