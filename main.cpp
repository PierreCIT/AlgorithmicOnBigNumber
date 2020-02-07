#include <iostream>
#include "BigInt.h"


using namespace std;

int main() {
    cout << "Begins" << endl;
    int k = 108;
    vector<uint64_t> initA = {0, 0, 0, 0, 0, 3, 0, 1, 1};
    vector<uint64_t> initB = {0, 0, 20, 0, 0, 0, 0, 2, 4294967295};
    vector<uint64_t> primary = {0, 0, 0, 0, 0, 2996, 1079361799, 167341580, 2946939995};
    vector<uint64_t> initv = {0, 0, 0, 0, 0, 4056, 4153196649, 2272039187, 1605889069};
    vector<uint64_t> initr = {0, 0, 0, 0, 0, 4096, 0, 0, 0};
    BigInt A(256, initA);
    BigInt B(256, initB);
    BigInt p(256, primary);
    BigInt v(256, initv);
    BigInt r(256, initr);
    cout << "A : ";
    A.print();
    cout << "B : ";
    B.print();
    cout << "p : ";
    p.print();
    cout << "A > B : " << (A > B) << endl;
    BigInt C = A.add(B);
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
//    cout << "Mask A with k : ";
//    C = mask_with_k(A, 64);
//    C.print();
//    cout << "Shift to right B : ";
//    C = shift_to_right(B, 5);
//    C.print();
//    cout << "Elementar Montgomery : ";
//    C = elementar_montgomery(A, B, v, p, k);
//    C.print();
//    cout << " A * B mod(p) (with Montgomery) : ";
//    C = A.montgomery(B, r, v, p, k);
//    C.print();
//    vector<uint64_t> s1 = {0, 0 ,0 ,0 ,0, 0 ,0 ,0, 0 ,0 ,0, 0 ,0 ,0 ,0, 0 ,0 ,0, 0 ,0 ,0, 0, 11, 3024115137, 126482799, 238003901, 1543503872, 0, 0, 0, 0 ,0 ,0 };
//    BigInt s(1024, s);
//    vector<uint64_t> s1 = {0, 0 ,0 ,0 ,0, 0 ,0 ,0, 0 ,0 ,0, 0 ,0 ,0 ,0, 0 ,0 ,0, 0 ,0 ,0, 0, 11, 3024115137, 126482799, 238003901, 1543503872, 0, 0, 0, 0 ,0 ,0 };
//    BigInt s(1024, s);

//    cout << " Test resize A to 512: ";
//    A.extend_to_size(512);
//    A.print();
    return 0;
}
