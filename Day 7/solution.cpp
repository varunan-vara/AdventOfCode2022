#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string>

using namespace std;

// A file class that contains all relevant details
class FSFile {
    private:
        string name;
        int size;
    public:
        FSFile () {
            name = "";
            size = 0;
        }
        FSFile (string newname, int newsize) {
            name = newname;
            size = newsize;
        }
        string getName() {
            return name;
        }
        int getSize () {
            return size;
        }
};

class FSFolder {
    private:
        string name;
        FSFolder *upper = NULL;
        FSFolder **subFolders = NULL;
        FSFile **subFiles = NULL;
        int numFolders = 0;
        int numFiles = 0;
    public:
        int smallSizes () {
            int counter = 0;
            for (int i = 0; i < numFolders; i ++) {
                counter = counter + subFolders[i]->smallSizes();
            }
            for (int j = 0; j < numFolders; j ++) {
                int num = subFolders[j]->getSize();
                counter = (num <= 100000) ? counter + num : counter;
            }
            return counter;
        }
        int smallestSizes (int inputnum = -1) {
            int num = (inputnum == -1) ? -40000000 + getSize() : inputnum;
            int tracker = 70000000;
            for (int i = 0; i < numFolders; i ++ ) {
                int n = subFolders[i]->smallestSizes(num);
                if (n < tracker && n > num) {
                    tracker = n;
                };
            }
            for (int j = 0; j < numFolders; j ++) {
                int n = subFolders[j]->getSize();
                if (n < tracker && n > num) {
                    tracker = n;
                }
            }
            return tracker;
        }
        FSFolder() {
            name = "";
        }
        FSFolder(string folderName, FSFolder* upperFolder) {
            name = folderName;
            upper = upperFolder;
        }
        void addSubFolder (FSFolder* folder) {
            numFolders ++;
            FSFolder **newList = (FSFolder **) malloc(numFolders * sizeof(FSFolder *));
            int i;
            for (i = 0; i < numFolders - 1; i ++) {
                newList[i] = subFolders[i];
            }
            newList[i] = folder;
            subFolders = newList;
        }
        void addFile (FSFile* file) {
            numFiles ++;
            FSFile **newList = (FSFile **) malloc(numFiles * sizeof(FSFile));
            int i;
            for (i = 0; i < numFiles - 1; i++ ){
                newList[i] = subFiles[i];
            }
            newList[i] = file;
            subFiles = newList;
        }
        int getSize () {
            int sizeIt = 0;
            for (int i = 0; i < numFiles; i++) {
                sizeIt = sizeIt + subFiles[i]->getSize();
            }
            for (int j = 0; j < numFolders; j++) {
                sizeIt = sizeIt + subFolders[j]->getSize();
            }
            return sizeIt;
        }
        string getName () {
            return name;
        }
        FSFolder *getFolder(string name) {
            for (int i = 0; i < numFolders; i ++) {
                if (subFolders[i]->getName() == name) {
                    return subFolders[i];
                }
            }
            return NULL;
        }
        FSFolder *getParent() {
            return upper;
        }
};

// Initialize some functions
FILE *get_file (char file_name[]);

int main (void) {
    FILE *file_name = get_file((char *) "./input.txt");
    printf("Make sure to remove the first line if it is '$ cd /'.\n");
    cout << "Check the end of the output for the answer" << endl;

    char output[100];
    //fgets(output, 100, file_name);
    FSFolder rootFolder = FSFolder("/", NULL);
    FSFolder *currentFolder = &rootFolder;
    string dir, name; int number;

    while(fgets(output, 100, file_name)) {
        if (output == "" ) {break;}
        char c;
        if (output[0] == '$') {
            // Command
            if (output[2] == 'c' && output[3] == 'd') {
                if (output[5] == '.' && output[6] == '.') {
                    currentFolder = currentFolder->getParent();
                } else {
                    string nextFolder = "";
                    int counter = 5;
                    c = output[counter];
                    while (c != '\n') {
                        nextFolder = nextFolder + c;
                        counter ++;
                        c = output[counter];
                    }
                    currentFolder = currentFolder->getFolder(nextFolder);
                    
                }
                cout << "Current folder Name: " << currentFolder->getName() << endl;
            }
            continue;
        } 
        if (output[0] == 'd' && output[1] == 'i' && output[2] == 'r') {
            string folderName = "";
            int counter = 4;
            c = output[counter];
            while (c != '\n') {
                folderName = folderName + c;
                counter ++;
                c = output[counter];
            }
            //FSFolder newFolder = FSFolder(folderName, currentFolder);
            currentFolder->addSubFolder( (new FSFolder(folderName, currentFolder)));
            cout << "Folder Name: " << folderName << endl;
        }
        else {
            int size = 0;
            int counter = 0;
            c = output[counter];
            string fileName = "";
            while (c != ' ') {
                size = size * 10 + ((int) c) - 48;
                counter ++;
                c = output[counter];
            }
            counter ++;
            c = output[counter];
            while (c != '\n') {
                fileName = fileName + c;
                counter ++;
                c = output[counter];
            }

            FSFile newFile = FSFile(fileName, size);
            currentFolder->addFile((new FSFile(fileName, size)));
            cout << "File Name: " << fileName << ", File Size: " << size << endl;
        }
    }

    
    //cout << "Size of Root Folder: " << rootFolder.getSize() << endl;
    cout << "Part 1: " << rootFolder.smallSizes() << endl;
    cout << "Part 2: " << rootFolder.smallestSizes() << endl;
    return 0;
}

// Function that converts a file to a list of str's, each of which is a line
FILE *get_file (char file_name[])  {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("NULL File at %s", file_name);
    } else {
        printf("Successfully read file\n");
    }
    return file;
}

