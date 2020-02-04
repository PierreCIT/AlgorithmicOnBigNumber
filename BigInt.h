//
// Created by noeim on 03/02/2020.
//

#ifndef ALGORITHMICONBIGNUMBER_BIGINT_H
#define ALGORITHMICONBIGNUMBER_BIGINT_H

#import <vector>
#import <string>
#import <iostream>

using namespace std;

class BigInt {
public:
    int size;
    unsigned int vector_size = 0;
    vector<uint64_t> value;

    BigInt(int siz, vector<uint64_t> vect);

    friend bool operator>(BigInt A, BigInt B) {
        for (int i = 0; i < A.vector_size; i++) {
            if (A.value[i] > B.value[i]) {
                return true;
            } else if (A.value[i] < B.value[i]) {
                return false;
            }
        }
        return false;
    };

    void print();

    BigInt add(BigInt B);

    BigInt addModular(BigInt B, BigInt p);

    friend BigInt operator+(BigInt A, BigInt B) {
        return A.add(B);
    }

    BigInt substract(BigInt B, BigInt p);

    BigInt multiply(BigInt B);

    void reset();
};


#endif //ALGORITHMICONBIGNUMBER_BIGINT_H
