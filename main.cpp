#include <iostream>
#include "BigInt.h"

using namespace std;

int main() {
    cout << "Begins" << endl;
    vector<uint64_t> initA = {1, 0, 0, 0, 0, 0, 0, 0};
    vector<uint64_t> initB = {0, 1, 1, 1, 1, 1, 1, 1};
    vector<uint64_t> primary = {2, 0, 0, 0, 0, 0, 0, 0};//{0, 0, 0, 0, 0, 999, 1700231273, 187355674};
    BigInt A(256, initA);
    BigInt B(256, initB);
    BigInt p(256, primary);
    cout << "A : ";
    A.print();
    cout << "B : ";
    B.print();
    cout << "p : ";
    p.print();
    cout << "A > B : " << (A > B) << endl;
    BigInt C = A + B;
    cout << "A + B : ";
    C.print();
    cout << "A + B mod(p) : ";
    C = A.addModular(B, p);
    C.print();
    cout << "A - B mod(p) : ";
    C = A.substract(B, p);
    C.print();
    return 0;
}
