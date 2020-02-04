#include <iostream>
#include "BigInt.h"

using namespace std;

int main() {
    cout << "Begins" << endl;
    vector<uint64_t> initA = {4294967295 ,4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295};
    vector<uint64_t> initB = {0, 0, 0, 0, 0, 0, 0, 1};
    vector<uint64_t> primary = {0, 0, 0, 0, 0, 0, 0, 17};
    BigInt A(256, initA);
    BigInt B(256, initB);
    BigInt p(256, primary);
    cout<< "A : ";
    A.print();
    cout<< "B : ";
    B.print();
    cout<< "p : ";
    p.print();
    cout << "A > B : "<<(A > B) << endl;
    BigInt C = A+B;
    cout << "A + B : ";
    C.print();
    cout << "A + B mod(p) : ";
    C = A.addModular(B,p);
    C.print();
    return 0;
}
