#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Define Functions
FILE *get_file (char file_name[]);

class Node {
    private:
        int xvalue = 0;
        int yvalue = 0;
        Node *next = NULL;
    public:
        Node () {
            return;
        }
        Node (int intxvalue, int intyvalue) {
            xvalue = intxvalue;
            yvalue = intyvalue;
        }
        void setNext(Node *val) {
            next = val;
        }
        int getXValue () {return xvalue;}
        int getYValue () {return yvalue;}
        Node *getNext() {return next;}
};


int main (void) {
    Node rootNode = Node(0,0);
    FILE *file_name = get_file((char *)"./sampleinput.txt");
    char output[5];
    int hpos[2] = {0,0};
    int tpos[2] = {0,0};
    int num;
    char direction;
    printf("Doing calculations, this may take a while!\n");
    int c = 1;
    while (fgets(output, 5, file_name)) {
        direction = output[0];
        num = ((int) output[2]) - 48;
        while (num > 0 ) {
            hpos[0] = (direction == 'R') ? hpos[0] + 1 : (direction == 'L') ? hpos[0] - 1 : hpos[0];
            hpos[1] = (direction == 'U') ? hpos[1] + 1 : (direction == 'D') ? hpos[1] - 1 : hpos[1];
            // A A B C C
            // A       C
            // D   T   E
            // F       H
            // F F G H H
            // top right if A (r > 2)
            // up if B (r = 2)
            // top left if C (r > 2)
            // left if D (r = 2)
            // right if E (r = 2)
            // bottom left if F (r > 2)
            // down if G (r = 2)
            // bottom right if H (r > 2)
            float r = sqrt((double) pow(hpos[0] - tpos[0],2) + pow(hpos[1] - tpos[1],2));

            if (r >= 2.0) {
                if (r == 2.0) {
                    if (hpos[0] - tpos[0] == 2) { // E
                        printf("E: %d, %d\n", c, num);
                        tpos[0] ++;
                    } else if (hpos[0] - tpos[0] == -2) { // D
                        printf("D: %d, %d\n", c, num);
                        tpos[0] --;
                    } else if (hpos[1] - tpos[1] == 2) { // B
                        printf("B: %d, %d\n", c, num);
                        tpos[1] ++;
                    } else if (hpos[1] - tpos[1] == -2) { // G
                        printf("G: %d, %d\n", c, num);
                        tpos[1] --;
                    }
                }
                if (r > 2.0) {
                    if (hpos[0] - tpos[0] > 0 && hpos[1] - tpos[1] > 0) { // C
                        printf("C: %d, %d\n", c, num);
                        tpos[0] ++;
                        tpos[1] ++;
                    }
                    if (hpos[0] - tpos[0] < 0 && hpos[1] - tpos[1] > 0) { // A
                        printf("A: %d, %d\n", c, num);
                        tpos[0] --;
                        tpos[1] ++;
                    }
                    if (hpos[0] - tpos[0] > 0 && hpos[1] - tpos[1] < 0) { // H
                        printf("H: %d, %d\n", c, num);
                        tpos[0] ++;
                        tpos[1] --;
                    }
                    if (hpos[0] - tpos[0] < 0 && hpos[1] - tpos[1] < 0) { // F
                        printf("F: %d, %d\n", c, num);
                        tpos[0] --;
                        tpos[1] --;
                    }
                }
                Node *ptr  = &rootNode;
                while (1) {
                    if (ptr->getXValue() == tpos[0] && ptr->getYValue() == tpos[1]) {
                        break;
                    }
                    if (ptr->getNext() == NULL) {
                        printf("n\n");
                        Node *newptr = new Node(tpos[0], tpos[1]);
                        ptr->setNext(newptr);
                        break;
                    }
                    ptr = ptr->getNext();
                }
            }
            num --;
        }
        c ++;
    }
    Node *valptr = &rootNode;
    int counter = 0;
    while (valptr != NULL) {
        counter ++;
        valptr = valptr->getNext();
    }
    printf("The tail has been in %d positions.\n", counter);
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

