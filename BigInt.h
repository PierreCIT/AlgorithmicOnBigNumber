//
// Created by noeim on 03/02/2020.
//

#ifndef ALGORITHMICONBIGNUMBER_BIGINT_H
#define ALGORITHMICONBIGNUMBER_BIGINT_H

#import <vector>
#include <cstring>
#import <iostream>
#include <cmath>
#include <bitset>

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

    BigInt montgomery(BigInt B, BigInt r, BigInt v, BigInt p);

    void extend_to_size(int size);

    void reduce_size_to(int size);
};

BigInt mask_with_k(BigInt a, int k);

BigInt elementar_montgomery(BigInt A, BigInt B, BigInt v, BigInt p, int k);

BigInt shift_to_right(BigInt a, int k);

#endif //ALGORITHMICONBIGNUMBER_BIGINT_H
