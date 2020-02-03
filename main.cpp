#include <iostream>
#include "BigInt.h"

using namespace std;

int main() {
    cout << "Begins" << endl;
    vector<unsigned long int> initA = {0, 0, 0, 0, 0, 20, 100};
    vector<unsigned long int> initB = {0, 0, 0, 0, 0, 20, 100};
    BigInt A(256, initA);
    BigInt B(256, initB);
    A.print();
    B.print();
    cout << (A > B) << endl;
    return 0;
}
