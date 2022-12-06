#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Functions
FILE *get_file (char file_name[]);
int isRepeat(char vals[], int len);
char* cutOff(char vals[], int cutoffPoint);

int main (void) {

    FILE *file_name = get_file("./input.txt");

    // If two letters are detected, then skip to until the character just after the first of the repeated character.
    // CAN NOT RUN IN VS CODE EXTENSION~
    int firstMarkerLength;
    printf("Input Marker Length (4 for Part One, 14 for Part Two): ");
    scanf("%d", &firstMarkerLength);
    char c;
    int i, j, counter = 0, testCounter = 0;
    char test[100];
    while ((c = fgetc(file_name)) != EOF) {
        test[testCounter] = c;
        test[testCounter + 1] = '\0';
        testCounter ++;
        counter ++;
        if (strlen(test) == firstMarkerLength) {
            i = isRepeat(test, firstMarkerLength);
            if (i == -1) {
                break;
            } else {
                char *newOne = cutOff(test, i);
                for (j = 0; j < firstMarkerLength - 1 - i; j ++) {
                    test[j] = newOne[j];
                }
                test[j] = '\0';
                testCounter = firstMarkerLength - 1 - i;
            }
        } 
    }

    printf("Number of Characters processed: %d\nFirst Marker: %s\n", counter, test);

    fclose(file_name);

    //printf("Number of Characters processed: %d\nFirst Marker: %s\n", counter, testTwo);

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

// Returns the point where the first of two or more repeated characters are found in a four character string, else returns -1
int isRepeat(char vals[], int len) {
    int i, j;
    for (i = 0; i < len; i ++) {
        for (j = i + 1; j < len; j ++) {
            if (vals[i] == vals[j]) {
                return i;
            }
        }
    }
    return -1;
}

// Returns a cut off version of a string
char* cutOff(char vals[], int cutoffPoint) {
    return vals + 1 + cutoffPoint;
}