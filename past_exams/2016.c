#include <xmmintrin.h>
#include <pmmintrin.h>
#include <stdio.h>
#include <stdlib.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

void add_scaled(float * a, float * b, float * c, float factor){
    for(int i = 0; i < 1024; i++){
        a[i] = b[i] + c[i] * factor;
    }
}

void add_scaled_vec(float * a, float * b, float * c, float factor){
    __m128 v4fac = _mm_set1_ps(factor);
    for(int i = 0; i < 1024; i+=4){
        __m128 v4b = _mm_loadu_ps(b+i);
        __m128 v4c = _mm_loadu_ps(c+i);
        v4c = _mm_mul_ps(v4c, v4fac);
        v4b = _mm_add_ps(v4b, v4c);
        _mm_storeu_ps(a+i, v4b);
    }
}