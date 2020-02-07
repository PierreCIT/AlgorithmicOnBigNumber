#include "BigInt.h"

BigInt::BigInt(int siz, vector<uint64_t> vect) {
    size = siz;
    vector_size = ((int) size / 32) + 1;
    value.resize(vector_size, 0);
    for (int i = 0; i < vect.size(); i++) {
        value[vector_size - 1 - i] = vect[vect.size() - 1 - i];
    }
}

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
    for (uint i = vector_size - 1; i > 1; i--) {
        uint64_t C = value[i] + B.value[i] + carry;
        result.value[i] = (uint32_t) C;
        carry = C >> 32;
    }
    if (carry > 0) {
        result.value[0] = carry;
    }
    return result;
}

BigInt BigInt::addModular(BigInt B, const BigInt &p) {
    BigInt result = this->add(B);
    if (result > p) {
        return result.substract(p, p);
    }
    return result;
}

/// Assume that this and B are modulo p.
/// \param B
/// \param p
/// \return
BigInt BigInt::substract(BigInt B, const BigInt &p) {
    BigInt this_copy = *this;
    if (!(*this > B)) {
        this_copy = this_copy.add(p);
    }
    vector<uint64_t> t = {2};
    BigInt result(this->size, t);
    for (uint i = vector_size - 1; i > 1; i--) {
        if (this_copy.value[i] >= B.value[i]) {
            result.value[i] = this_copy.value[i] - B.value[i];
        } else {
            result.value[i] = this_copy.value[i] + 4294967296 - B.value[i];
            B.value[i - 1] += 1;
        }
    }
    return result;
}

BigInt BigInt::multiply(BigInt B) {
    uint64_t temp_mul = 0;
    vector<uint64_t> temp = {0};
    BigInt result(size * 2, temp);
    for (uint i = vector_size - 1; i > 0; i--) {
        uint64_t carry = 0;
        uint64_t carry_2 = 0;
        for (uint k = vector_size - 1; k > 0; k--) {
            uint index = (result.vector_size - 1) - (vector_size - k - 1) - (vector_size - i - 1);
            temp_mul = B.value[i] * value[k];
            uint64_t temp_add = (uint64_t) ((uint32_t) temp_mul + result.value[index]);
            result.value[index] = uint64_t((uint32_t) temp_add);
            carry = (uint32_t) (temp_add >> 32);

            temp_add = (uint64_t) ((uint32_t) (temp_mul >> 32) + result.value[index - 1]) + carry + carry_2;
            result.value[index - 1] = uint64_t((uint32_t) temp_add);
            carry_2 = (uint32_t) (temp_add >> 32);
        }
    }
    return result;
}


void BigInt::extend_to_size(int siz) {
    BigInt resized(siz, value);
    *this = resized;
}

BigInt mask_with_k(BigInt a, int k) {
    int index = (int) k / 32;
    a.value[a.vector_size - 1 - index] = a.value[a.vector_size - 1 - index] & (unsigned long) (pow(2, k % 32) - 1);
    for (uint i = a.vector_size - 2 - index; i > 0; i--) {
        a.value[i] = 0;
    }
    return a;
}

BigInt shift_to_right(BigInt a, int k) {
    vector<uint64_t> temp = {0};
    BigInt result(a.size, temp);
    string binary;
    for (int i = 0; i < a.vector_size; i++) {
        binary += bitset<32>(a.value[i]).to_string(); //to binary
    }
    string final_binary;
    for (int i = 0; i < binary.size() - k; i++) {
        final_binary += binary[i];
    }
    string add2;
    for (int i = 0; i < k; i++) {
        add2 += "0";
    }
    final_binary = add2 + final_binary;
    for (int i = 0; i < (int) (final_binary.size() / 32) + 1; i++) {
        string temp5 = final_binary.substr(i * 32, 32);
        result.value[i] = bitset<32>(final_binary.substr(i * 32, 32)).to_ulong();
    }
    return result;
}

BigInt elementar_montgomery(BigInt A, const BigInt &B, BigInt v, BigInt p, int k) {
    vector<uint64_t> temp4 = {0};
    BigInt s((int) A.size * 2, temp4);
    s = A.multiply(B);
    v.extend_to_size(s.size);
    BigInt t = s.multiply(v);
    t = mask_with_k(t, k); //operation modulo
    t.reduce_size_to(A.size);
    p.extend_to_size(t.size);
    BigInt temp = t.multiply(p);
    s.print();
    temp.print();
    BigInt m = s.add(temp);
    m = shift_to_right(m, k);
    m.reduce_size_to((int) (m.size / 2));
    return m;
}


BigInt BigInt::montgomery(BigInt B, BigInt r, const BigInt& v, const BigInt& p, int k) {
    vector<uint64_t> temp = {1};
    BigInt a_phi(size, temp);
    BigInt b_phi(size, temp);
    BigInt result_phi(size, temp);
    BigInt one(size, temp);
    this->extend_to_size(this->size * 2);
    a_phi = elementar_montgomery(*this, r.multiply(r), v, p, k);
    B.extend_to_size(B.size * 2);
    b_phi = elementar_montgomery(B, r.multiply(r), v, p, k);
    result_phi = elementar_montgomery(a_phi, b_phi, v, p, k);
    BigInt temp2 = elementar_montgomery(result_phi, one, v, p , k);
    return temp2;
}

void BigInt::reduce_size_to(int siz) {
    vector<uint64_t> temp = {0};
    BigInt reduced(siz, temp);
    for (int i = 0; i < reduced.vector_size; i++) {
        reduced.value[reduced.vector_size - 1 - i] = value[vector_size - 1 - i];
    }
    *this = reduced;
}
