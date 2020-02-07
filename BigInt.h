//
// Created by noeim on 03/02/2020.
//

#ifndef ALGORITHMICONBIGNUMBER_BIGINT_H
#define ALGORITHMICONBIGNUMBER_BIGINT_H

#include <vector>
#include <cstring>
#include <iostream>
#include <cmath>
#include <bitset>

using namespace std;

class BigInt {
public:
    int size;
    uint vector_size = 0;
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

    BigInt addModular(BigInt B, const BigInt &p);

    BigInt substract(BigInt B,const BigInt &p);

    BigInt multiply(BigInt B);

    BigInt montgomery(BigInt B, BigInt r, const BigInt& v, const BigInt& p, int k);

    void extend_to_size(int siz);

    void reduce_size_to(int siz);
};

BigInt mask_with_k(BigInt a, int k);

BigInt elementar_montgomery(BigInt A,const BigInt &B, BigInt v, BigInt p, int k);

BigInt shift_to_right(BigInt a, int k);

#endif //ALGORITHMICONBIGNUMBER_BIGINT_H
