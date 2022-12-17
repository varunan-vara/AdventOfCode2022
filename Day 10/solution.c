#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Functions
FILE *get_file (char file_name[]);
void iterateCycle(int *counter, int *x, int *outputlist);
int calculateSignalStrengths(int *outputlist, int *values, int size);


int main (void) {
    FILE *file_name = get_file((char *) "./input.txt");
    int x = 1, counter = 0, v, outputs[280];
    char output[10];

    while (fscanf(file_name, "%s %d", output, &v) != EOF) {
        if (output[0] == 'n') {
            iterateCycle(&counter, &x, outputs);
        } else if (output[0] == 'a') {
            iterateCycle(&counter, &x, outputs);
            iterateCycle(&counter, &x, outputs);
            x = x + v;
        }
    }
    int printlist[6] = {20, 60, 100, 140, 180, 220};
    printf("\n\nTotal Signal Strength Calculations: %d\n", calculateSignalStrengths(outputs, printlist, 6));

    return 0;
}

void iterateCycle(int *counter, int *x, int *outputlist) {
    if (*counter %40 == 0) {printf("\n");}
    if (abs((*counter %40) - *x) <= 1) {
        printf("# ");
    } else {printf(". ");}
    *counter = *counter + 1;
    outputlist[*counter] = *x;

}

int calculateSignalStrengths(int *outputlist, int *values, int size) {
    int returnint = 0;
    for (int i = 0; i < size; i ++ ) {
        returnint = returnint + (values[i] * outputlist[values[i]]);
    }
    return returnint;
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