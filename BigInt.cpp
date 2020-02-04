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