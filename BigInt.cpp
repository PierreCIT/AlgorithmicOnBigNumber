#include "BigInt.h"

BigInt::BigInt(int siz, vector<unsigned long int> vect) {
    size = siz;
    vector_size = ((int)size/32)+1;
    value.resize(vector_size, 0);
    for(int i=0; i<vect.size();i++){
        value[vector_size-1-i] = vect[vect.size()-1-i];
    }
};

void BigInt::print() {
    for(auto &it: value){
        cout<<it<<" ";
    }
    cout<<endl;
}