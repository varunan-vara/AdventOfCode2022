#include <iostream>
#include <stdlib.h>

using namespace std;

class Stack {
    private: 
        char containers[100];
        int size = 0;
    public:
        Stack();
        void setVar(char containerlist[], int containersize);
        int getSize();
        void addContainers( char containerList[], int containerCount );
        void moveContainers( Stack *toStack, int num );
        void moveContainersTwo( Stack *toStack, int num );
        char topContainer ();
};

// Initialize some functions
FILE *get_file (char file_name[]);

int main() {
    // Define Variables
    int number_of_stacks = 9;
    char stack_contents[9][8] = {
        {'F', 'T', 'C', 'L', 'R', 'P', 'G', 'Q'},
        {'N', 'Q', 'H', 'W', 'R', 'F', 'S', 'J'},
        {'F', 'B', 'H', 'W', 'P', 'M', 'Q'},
        {'V', 'S', 'T', 'D', 'F'},
        {'Q', 'L', 'D', 'W', 'V', 'F', 'Z'},
        {'Z', 'C', 'L', 'S'},
        {'Z', 'B', 'M', 'V', 'D', 'F'},
        {'T', 'J', 'B'},
        {'Q', 'N', 'B', 'G', 'L', 'S', 'P', 'H'}
    };
    int stack_content_sizes[number_of_stacks] = {8, 8, 7, 5, 7, 4, 6, 3, 8};
    FILE *file_name = get_file((char *) "./input.txt");
    Stack *stack_list = new Stack[number_of_stacks];
    Stack *part_two_list = new Stack[number_of_stacks];
    int i;

    for (i = 0; i < number_of_stacks; i ++) {
        stack_list[i].setVar(stack_contents[i], stack_content_sizes[i]);
        part_two_list[i].setVar(stack_contents[i], stack_content_sizes[i]);
    }

    int num, from, to;

    for (i = 0; i < 501; i ++) {
        fscanf(file_name, "move %d from %d to %d", &num, &from, &to);
        fgetc(file_name);
        stack_list[from - 1].moveContainers(&stack_list[to - 1], num);
        part_two_list[from - 1].moveContainersTwo(&part_two_list[to - 1], num);
    }



    // Pure formatting  
    cout << "Model 5000" << endl;
    for (i = 0; i < number_of_stacks; i ++) {cout << "Top Container for Stack " << i + 1 << ": " << stack_list[i].topContainer() << endl;}

    cout << endl << "Total: " << endl;
    for (i = 0; i < number_of_stacks; i ++) {cout << stack_list[i].topContainer();}
    cout << endl << endl;

    cout << "Model 5001" << endl;
    
    for (i = 0; i < number_of_stacks; i ++) {cout << "Top Container for Stack " << i + 1 << ": " << part_two_list[i].topContainer() << endl;}

    cout << endl << "Total: " << endl;
    for (i = 0; i < number_of_stacks; i ++) {cout << part_two_list[i].topContainer();}
    cout << endl << endl;
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

Stack::Stack() {
    return;
}

int Stack::getSize() {return size;}

void Stack::addContainers( char containerList[], int containerCount ) {
    for (int i = 0; i < containerCount; i ++) {
        containers[size + i] = containerList[i];
    }
    size = size + containerCount;
}

void Stack::moveContainers( Stack *toStack, int num ) {
    char moveList[num];
    for (int i = 0; i < num; i++) {
        moveList[i] = containers[size - 1 - i];
    }
    size = size - num;
    toStack->addContainers(moveList, num);
}

void Stack::setVar(char containerlist[], int containersize) {
    for (int i = 0; i < containersize; i++ ) {
        containers[i] = containerlist[i];
    }
    size = containersize;
}

char Stack::topContainer () {
    if (size == 0) {return '?';}
    return containers[size - 1];
}

void Stack::moveContainersTwo( Stack *toStack, int num ) {
    char movelist[num];
    for (int i = 0; i < num; i++) {
        movelist[i] = containers[size - 1 - i];
    }
    int temp;
    for (int i = 0, j = num - 1; i < num/2; i ++, j--) {
        temp = movelist[i];
        movelist[i] = movelist[j];
        movelist[j] = temp;
    }
    size = size - num;
    toStack->addContainers(movelist, num);
}