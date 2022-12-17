#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
using namespace std;

// Define Functions
FILE *get_file (char file_name[]);

// Items stolen from backpack
class Item {
    private:
        int worryLevel = 0;
        Item *next;
    public:
        Item() {
            worryLevel = 0;
            next = NULL;
        }
        Item (int worry) {
            worryLevel = worry;
            next = NULL;
        }
        void multiply(int x) {worryLevel = worryLevel * (int) x;}
        void add (int x) {worryLevel = worryLevel + x;}
        void square () {worryLevel = worryLevel * worryLevel;}
        void multiplyTwo () {worryLevel = worryLevel * 2;}
        void bored() {worryLevel = worryLevel / 3;}
        int getWorryLevel () {return worryLevel;}
        Item *getNextItem () {return next;}
        void setNextItem (Item *set) {next = set;}
        void resetNext() {next = NULL;}
};

// Monkey class
class Monkey {
    private:
        Item *headItem = NULL;
        char operation;
        int monkeyBusiness = 0;
        int operationNum;
        int testNum;
        int trueMonkey;
        int falseMonkey;
    public:
        Monkey(char operationChar, int operationNumInt, int testNumInt, int trueMonkeyInt, int falseMonkeyInt);
        void catchItem(Item *y);
        void throwItemToMonkey(Monkey *target);
        void runOperation(Monkey** monkeyList);
        int getMonkeyBusiness() {return monkeyBusiness;}
};

int main(void) {
    FILE *file_name = get_file((char*)"./sampleinput.txt");
    cout << "Assuming there are max of 8 monkeys." << endl << "assuming all the starting items are two digits large." << endl;
    Monkey **monkeys = new Monkey*[8];
    int n;
    char output[50], operationStore;
    int *numberStorage, operationNum, divCheckStore, trueMonkeyStore, falseMonkeyStore;

    while (fscanf(file_name, "Monkey %d:", &n) != EOF) {
        fgets(output, 50, file_name);
        fgets(output, 50, file_name);
        // Processing the starting items in numberStorage
        int num = (strlen(output) - 17) / 4;
        numberStorage = new int[num];
        for (int i = 0; i < num; i ++) {
            char item1 = output[18 + 4 * i], item2 = output[19 + 4 * i];
            numberStorage[i] = (((int) item1) - 48) * 10 + ((int) item2) - 48;
        }


        fgets(output, 50, file_name);
        if (output[23] == '*') {
            if (output[25] == 'o') {
                operationStore = 's';
            } else {
                operationStore = 'm';
                sscanf(output, "  Operation: new = old * %d", &operationNum);
            }
        } else if (output[23] == '+') {
            if (output[25] == 'o') {
                operationStore = 'd';
            } else {
                operationStore = 'a';
                sscanf(output, "  Operation: new = old + %d", &operationNum);
            }
        }


        fgets(output, 50, file_name);
        sscanf(output, "  Test: divisible by %d", &divCheckStore);


        fgets(output, 50, file_name);
        sscanf(output, "    If true: throw to monkey %d", &trueMonkeyStore);
        fgets(output, 50, file_name);
        sscanf(output, "    If false: throw to monkey %d", &falseMonkeyStore);

        //Blank Line
        fgets(output, 50, file_name);

        monkeys[n] = new Monkey(operationStore, operationNum, divCheckStore, trueMonkeyStore, falseMonkeyStore);

    } 

    for (int x = 0; x < 20; x ++) {
        for (int y = 0; y < n; y ++) {
            monkeys[y]->runOperation(monkeys);
        }
    }
    
    for (int y = 0; y < n; y ++) {
        cout << "Monkey " << y << ": " << monkeys[y]->getMonkeyBusiness() << endl;
    }
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

Monkey::Monkey(char operationChar, int operationNumInt, int testNumInt, int trueMonkeyInt, int falseMonkeyInt) {
    // operation char should be m or a (multiply or add) or s (square)
    operation = operationChar;
    operationNum = operationNumInt;
    // number to test if divisble
    testNum = testNumInt;
    trueMonkey = trueMonkeyInt;
    falseMonkey = falseMonkeyInt;
    cout << "New Monkey!\nDetails:\n - Operation: " ;
    cout << operationChar << ", ";
    cout << operationNum << endl;
    cout << " - Test: Divisble by " << testNum << endl;
    cout << " - T: " << trueMonkey << " - F: " << falseMonkey << endl;
}
void Monkey::catchItem(Item *y) {
    monkeyBusiness ++;
    if (headItem == NULL) {
        headItem = y;
        return;
    }
    Item *ptr = headItem;
    while (ptr->getNextItem() != NULL) {ptr = ptr->getNextItem();}
    ptr->setNextItem(y);
}
void Monkey::throwItemToMonkey(Monkey *target) {
    Item *ptr = headItem;
    headItem = headItem->getNextItem();
    target->catchItem(ptr);
}
void Monkey::runOperation(Monkey** monkeyList) {
    cout << 1 << endl;
    if (operation == 'm') {
        cout << 1 << endl;
        headItem->multiply(operationNum);
        cout << 1 << endl;
    } else if (operation == 'a') {
        headItem->add(operationNum);
    } else if (operation == 's') {
        headItem->square();
    } else if (operation == 'd') {
        headItem->multiplyTwo();
    }
    headItem->bored();
    if (headItem->getWorryLevel() % testNum != 0) {
        throwItemToMonkey(*monkeyList + falseMonkey);
    } else {
        throwItemToMonkey(*monkeyList + trueMonkey);
    }
}