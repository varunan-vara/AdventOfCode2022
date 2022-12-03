#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Functions
FILE *get_file (char file_name[]);

// Main Function
int main(void) {

    FILE *file = get_file("./input.txt");

    //Store value for current elf with greatest calories
    int biggest = 0;
    int second_biggest = 0;
    int third_biggest = 0;
    // Store current calorie value
    int current = 0;
    // Store current output of fgets
    char output[10];

    while (fgets(output, sizeof(output), file)) {
        // Convert to int
        int output_int = atoi(output);

        // If output_int is 0, it is a newline (assuming no one is carrying 0 calorie items)
        if (output_int == 0) {
            if (current > biggest) {
                third_biggest = second_biggest;
                second_biggest = biggest;
                biggest = current;
            } else if (current > second_biggest) {
                third_biggest = second_biggest;
                second_biggest = current;
            } else if (current > third_biggest) {
                third_biggest = current;
            }
            current = 0;
        } else {
            current = current + output_int;
        }
    }

    printf("Elf carrying the largest number of calories: %d\n", biggest);
    printf("Elf carrying the second largest number of calories: %d\n", second_biggest);
    printf("Elf carrying the third largest number of calories: %d\n", third_biggest);
    printf("Total sum of top three elves' calorie content: %d\n", biggest + second_biggest + third_biggest);
    return 0;
}


// Function that converts a file to a list of str's, each of which is a line
FILE *get_file (char file_name[])  {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("NULL File at %s\n", file_name);
    }
    return file;
}