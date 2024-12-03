#include <iostream>
using namespace std;

int main(void) {

    int myArray[4] = {1,2,3,4};
    cout << (int) myArray << " " << (int )*myArray << " " << (int) (myArray + 1) << endl;

    return 0;
}