#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

// Define classes
class Item {
    public:
        int worryAmount;
        Item (int worryInt) {worryAmount = worryInt;}
        void add(int num) {worryAmount = worryAmount + num;}
        void multiply(int num) {worryAmount = worryAmount * num;}
        void divide(int num) {worryAmount = worryAmount / num;}
};

class Monkey {
    private:
        int inspections = 0;
        vector<Item> itemList;
        bool isOperationMultiply; // True means multiply, false means add
        bool isOperationValueOld = false; // True means add or multiply by old, false means use value below
        int operationValue, divisibleValue;
        Monkey *trueMonkey;
        Monkey *falseMonkey;

    public:
        Monkey () {}
        // -1 at operationValue means operation is done using old
        Monkey(vector<Item> startingItemList, bool intIsOperationMultiply, int intOperationValue, int checkValue, Monkey *pTrueMonkey, Monkey *pFalseMonkey) {
            itemList = startingItemList;
            isOperationMultiply = intIsOperationMultiply;
            if (intOperationValue == -1) 
                isOperationValueOld = true;
            else 
                operationValue = intOperationValue;
            divisibleValue = checkValue;
            trueMonkey = pTrueMonkey, falseMonkey = pFalseMonkey;
        }

        void inheritItem(Item item) {
            itemList.push_back(item);
        }

        void inspect() {
            while (itemList.size() > 0) {
                Item sItem = itemList[itemList.size() - 1];

                // Increment Inspections
                inspections++;

                // Adjust Worry Value
                int temp;
                if (isOperationValueOld) 
                    temp = sItem.worryAmount;
                else
                    temp = operationValue;
                
                if (isOperationMultiply)
                    sItem.multiply(temp);
                else
                    sItem.add(temp);

                // Get Bored
                sItem.divide(3);

                // Check divisible value
                if(sItem.worryAmount % divisibleValue != 0) 
                    trueMonkey->inheritItem(sItem);
                else
                    falseMonkey->inheritItem(sItem);
                
                itemList.pop_back();
            }
            cout << "Monkey has inspected" << endl;
        }

        int getInspectionNumber () {return inspections;}
};

// Define Functions
FILE *get_file (char file_name[]);

int main (void) {

    FILE *file = get_file((char *) "./sampleinput.txt");
    char output[100];
    Monkey *monkey[10]; int monkeyIndex = 0;

    while (fgets(output, sizeof(output), file)) {
        // First line is Monkey Number, we can skip this
        // Second Line Contains starting Items
        fgets(output, sizeof(output), file);
        string outputString = output;
        outputString.erase(0,17);

        vector<Item> itemList;
        string temp;
        for (stringstream sst(outputString); getline(sst, temp, ','); ) {
            itemList.push_back(Item(stoi(temp)));
        }

        // Third Line Contains operation
        fgets(output, sizeof(output), file);
        bool multiplication = (output[23] == '*');
        string outputString2 = output; 
        outputString2.erase(0,25);
        int opNumber = (outputString2[0] == 'o') ? -1 : stoi(outputString2);

        // Fourth Line Contains boolean statement
        fgets(output, sizeof(output), file);
        string outputString3 = output;
        outputString3.erase(0,20);
        int divNum = stoi(outputString3);

        // Fifth and Sixth Line Contain monkeys
        fgets(output, sizeof(output), file);
        string outputString4 = output;
        outputString4.erase(0,28);
        int trueMonkey = stoi(outputString4);
        fgets(output, sizeof(output), file);
        string outputString5 = output;
        outputString5.erase(0,30);
        int falseMonkey = stoi(outputString5);

        // Skip last line
        fgets(output, sizeof(output), file);

        monkey[monkeyIndex] = new Monkey(
            itemList, 
            multiplication,
            opNumber, 
            divNum, 
            monkey[trueMonkey], 
            monkey[falseMonkey]
        );
    }

    int rounds = 20;
    for (int i = 0; i < rounds; i++) {
        for (Monkey *m : monkey) {
            m->inspect();
        }
    }

    vector<Monkey*> monkeyVector(monkey, monkey + sizeof(monkey) / sizeof(monkey[0]));
    sort(monkeyVector.begin(), monkeyVector.end(), [](Monkey *m1, Monkey *m2) -> bool {return m1->getInspectionNumber() < m2->getInspectionNumber();});

    cout << monkeyVector[0]->getInspectionNumber();

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