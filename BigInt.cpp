#include "BigInt.h"

BigInt::BigInt(int siz, vector<uint64_t> vect) {
    size = siz;
    vector_size = ((int) size / 32) + 1;
    value.resize(vector_size, 0);
    for (int i = 0; i < vect.size(); i++) {
        value[vector_size - 1 - i] = vect[vect.size() - 1 - i];
    }
};

void BigInt::print() {
    for (auto &it: value) {
        cout << it << " ";
    }
    cout << endl;
}

BigInt BigInt::add(BigInt B) {
    vector<uint64_t> A = {2, 3};
    BigInt result(this->size, A);
    uint64_t carry = 0;
    for (int i = vector_size - 1; i > 1; i--) {
        uint64_t C = value[i] + B.value[i] + carry;
        result.value[i] = (uint32_t) C;
        carry = C >> 32;
    }
    if (carry > 0) {
        result.value[0] = carry;
    }
    return result;
}

BigInt BigInt::addModular(BigInt B, BigInt p) {
    BigInt result = this->add(B);
    if (result > p) {
        return result.substract(p, p);
    }
    return result;
}


BigInt BigInt::substract(BigInt B, BigInt p) {
    if (!(*this > B)) {
        *this = *this + p;
    }
    vector<uint64_t> t = {2};
    BigInt result(this->size, t);
    for (int i = vector_size - 1; i > 1; i--) {
        if (value[i] >= B.value[i]) {
            result.value[i] = value[i] - B.value[i];
        } else {
            result.value[i] = value[i] + 4294967296 - B.value[i];
            B.value[i - 1] += 1;
        }
    }
    return result;
}

BigInt BigInt::multiply(BigInt B) {
    vector<uint64_t> temp = {0};
    BigInt result(size * 2, temp);
    BigInt finalResult(size * 2, temp);
    uint64_t temp_mul = 0;
    for (int i = vector_size - 1; i > 0; i--) {
        uint64_t carry = 0;
        uint64_t carry_2 = 0;
        for (int k = vector_size - 1; k > 0; k--) {
            int index = (result.vector_size - 1) - (vector_size - k - 1) - (vector_size - i - 1);
            cout << index << " ";
            temp_mul = B.value[i] * value[k];
            uint64_t temp_add = (uint64_t) ((uint32_t) temp_mul + result.value[index]);
            result.value[index] = uint64_t((uint32_t) temp_add);
            carry = (uint32_t) (temp_add >> 32);

            temp_add = (uint64_t) ((uint32_t) (temp_mul >> 32) + result.value[index - 1]) + carry + carry_2;
            result.value[index - 1] = uint64_t((uint32_t) temp_add);
            carry_2 = (uint32_t) (temp_add >> 32);
        }
        cout << endl;
//        finalResult = finalResult + result;
//        finalResult.print();
//        result.reset();
    }
    return result;
}

void BigInt::reset() {
    for (int i = 0; i < vector_size; i++) {
        value[i] = 0;
    }
}

BigInt mask_with_k(BigInt a, int k) {
    int index = (int) k / 32;
    a.value[a.vector_size - 1 - index] = a.value[a.vector_size - 1 - index] & (unsigned long) (pow(2, k % 32) - 1);
    for (int i = a.vector_size - 2 - index; i > 0; i--) {
        a.value[i] = 0;
    }
    return a;
}

BigInt shift_to_right(BigInt a, int k) {
    for (int i = 0; i < a.vector_size - 1; i++) {
        a.value[i + 1] = a.value[i];
    }
    return a;
}

BigInt elementar_montgomery(BigInt A, BigInt B, BigInt r, BigInt v, BigInt p, int k) {
    BigInt s = A.multiply(B);
    BigInt t = mask_with_k(s.multiply(v), k);
    t = mask_with_k(t, k); //operation modulo
    BigInt m = s + t.multiply(p);
    //return m >> 32; //TODO: Change
}

BigInt BigInt::montgomery(BigInt B, BigInt r, BigInt v, BigInt p) {
    vector<uint64_t> temp = {0};
    BigInt a_phi(size, temp);
    BigInt b_phi(size, temp);

}