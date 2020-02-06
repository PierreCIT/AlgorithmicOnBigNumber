#include <iostream>
#include <bitset>
#include "BigInt.h"


using namespace std;

int main() {
    std::string binary = std::bitset<32>(pow(2, 31)).to_string(); //to binary
    std::cout << binary << "\n";

    cout << binary[0] << " " << binary[1] << endl;

    unsigned long decimal = std::bitset<8>(binary).to_ulong();
    std::cout << decimal << "\n";

    cout << "Begins" << endl;
    vector<uint64_t> initA = {0, 0, 0, 0, 0, 0, 0, 2147483905, 2147483905};
    vector<uint64_t> initB = {0, 0, 4294967295, 0, 0, 0, 0, 0, 4294967295};
    vector<uint64_t> primary = {0, 4294967295, 0, 0, 0, 0, 0, 0, 0};//{0, 0, 0, 0, 0, 999, 1700231273, 187355674};
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
    cout << "A * B : ";
    C = A.multiply(B);
    C.print();
    cout << "Mask A with k : ";
    C = mask_with_k(A, 64);
    C.print();
    cout << "Elementar Montgomery : ";
    C = elementar_montgomery(A, B, C, p, 200);
    C.print();

//    cout << " Test resize A to 512: ";
//    A.extend_to_size(512);
//    A.print();
    return 0;
}
