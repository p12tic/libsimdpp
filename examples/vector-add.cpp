#include <simdpp/simd.h>
#include <iostream>

// Initializes vector to store values
void init_vector(float* a, float* b, size_t size) {
    for (int i=0; i<size; i++) {
        a[i] = i;
        b[i] = size - i - 1;
    }
}

// Test result of SIMD operations on vector
void test_result(float* result, size_t size) {
    for (int i=0; i<size; i++) {
        assert(result[i] == size - 1);
    }
}

using namespace simdpp;
int main() {
    const size_t SIZE = 1024;
    float vec_a[SIZE];
    float vec_b[SIZE];
    float result[SIZE];
    init_vector(vec_a, vec_b, SIZE);

    for (int i=0; i<SIZE; i+=4) {
        float32<4> xmmA = load(vec_a + i);  //loads 4 floats into xmmA
        float32<4> xmmB = load(vec_b + i);  //loads 4 floats into xmmB
        float32<4> xmmC = add(xmmA, xmmB);  //Vector add of xmmA and xmmB
        store(result + i, xmmC);            //Store result into the vector
    }
    
    test_result(result, SIZE);
    return 0;
}