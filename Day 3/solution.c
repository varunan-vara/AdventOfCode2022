#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Functions
FILE *get_file (char file_name[]);
int getPriority(char item);

int main (void) {
    FILE *file = get_file("./input.txt");

    // Compartment one and two
    char c1[50];
    char c2[50];
    char totalc[100];
    int totalPriority = 0, i;
    while (fgets(totalc, sizeof(totalc), file)) {
        char *p = totalc;
        int stlen = (strlen(totalc) -1) / 2;
        memcpy(c1, p, stlen);
        c1[stlen] = '\0';
        memcpy(c2, p + stlen, stlen);
        c2[stlen] = '\0';
        for (i = 0; i < stlen; i ++) {
            if (strchr(c2, c1[i])) {
                totalPriority = totalPriority + getPriority(c1[i]);
                break;
            }
            
        }
    }
    printf("Total Sum of Priorities: %d\n", totalPriority);

    fclose(file);

    FILE *twofile = get_file("./input.txt");
    char ** elfGroup = malloc(3 * sizeof(char*));
    int counter = 0;
    char output[100];
    int j,k;
    totalPriority = 0;
    while (fgets(output, sizeof(output), file)) {
        elfGroup[counter] = output;
        counter ++;
        if (counter == 3) {

            counter = 0;
            k = 0;
            char charlist[100];

            for (i = 0; i < strlen(elfGroup[0]); i++) {
                if (strchr(elfGroup[1], *(elfGroup[0] + i))) {
                    charlist[k] = elfGroup[0][i];
                    k++;
                }
            }
            for (j = 0; j < strlen(charlist); j++) {
                if (strchr(elfGroup[2], charlist[j])) {
                    totalPriority = totalPriority + getPriority(charlist[j]);
                    break;
                }
            }
        }
    }
    printf("Total Sum of Authentic Priorities: %d\n", totalPriority);
    fclose(twofile);
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

// Simple function to return the priority
int getPriority(char item) {
    int item_ascii = (int) item;
    return (item_ascii > 96) ? item_ascii - 96 : item_ascii - 38;
}