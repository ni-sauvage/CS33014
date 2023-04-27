#include <xmmintrin.h>
#include <pmmintrin.h>
#include <stdio.h>
#include <stdlib.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

void compute(float * a, float * b){
    for(int i = 0; i < 1024; i++){
        b[i] = 1/(a[i] * a[i]) + 3.14159;
    }
}

void compute_vec(float * a, float * b){
    __m128 numerator = _mm_set1_ps(1);
    __m128 pi_approx = _mm_set1_ps(3.14159);  
    __m128 vec_b;
    for(int i = 0; i < 1024; i+=4){
        vec_b = _mm_loadu_ps(a + i);
        vec_b = _mm_mul_ps(vec_b, vec_b);
        vec_b = _mm_div_ps(numerator, vec_b);
        vec_b = _mm_add_ps(vec_b, pi_approx);
        _mm_storeu_ps(b + 1, vec_b);
    }
}

float find_max(float * array, int size){
    float max = array[0];
    for(int i = 1; i < size; i++){
        if(array[i] > max){
            max = array[i];
        }
    }
}

float find_max_vec(float * array, int size){
    __m128 max, a;
    max = _mm_loadu_ps(array);
    int i = 4;
    for(; i < size-3; i+=4){
        a = _mm_loadu_ps(array + i);
        max = _mm_max_ps(a, max);
    }
    float max_tmp[4];
    _mm_storeu_ps(max_tmp, max);
    float max_val = MAX(MAX(MAX(max_tmp[0], max_tmp[1]), max_tmp[2]), max_tmp[3]);
    for(; i < size; i++){
        if(array[i] > max_val){
            max_val = array[i];
        }
    }
}

float rgb_sum_product(float * pixels){
    float sum_red = 0.0, sum_green = 0.0, sum_blue = 0.0;
    for(int i = 0; i < 1011; i += 3){
        sum_red = sum_red + pixels[i];
        sum_green = sum_green + pixels[i+1];
        sum_blue = sum_blue + pixels[i+2];
    }
    return sum_red * sum_blue * sum_green;
}

float rgb_sum_product_vec(float * pixels){
    float sum_red = 0.0, sum_green = 0.0, sum_blue = 0.0;
    __m128 rgbr, gbrg, brgb, vec_pix;
    rgbr = gbrg = brgb = _mm_set1_ps(0);
    int i;
    for(i = 0; i < 1000; i += 12){
        vec_pix = _mm_loadu_ps(pixels + i);
        rgbr = _mm_add_ps(vec_pix, rgbr);
        vec_pix = _mm_loadu_ps(pixels + i + 4);
        gbrg = _mm_add_ps(vec_pix, gbrg);
        vec_pix = _mm_loadu_ps(pixels + i + 8);
        brgb = _mm_add_ps(vec_pix, brgb);
    }
    for(; i < 1011; i += 3){
        sum_red = sum_red + pixels[i];
        sum_green = sum_green + pixels[i+1];
        sum_blue = sum_blue + pixels[i+2];
    }
    float tmp[4];
    _mm_storeu_ps(tmp, rgbr);
    sum_red += tmp[0] + tmp[3];
    sum_green += tmp[1];
    sum_blue += tmp[2];
    _mm_storeu_ps(tmp, gbrg);
    sum_green += tmp[0] + tmp[3];
    sum_blue += tmp[1];
    sum_red += tmp[2];
    _mm_storeu_ps(tmp, brgb);
    sum_blue += tmp[0] + tmp[3];
    sum_red += tmp[1];
    sum_green += tmp[2];
    return sum_red * sum_blue * sum_green;
}

void multiply(float ** restrict matrix, float * restrict vec, float * restrict result){
    for(int i = 0; i < 4096; i++){
        float sum = 0.0;
        for(int j = 0; j < 4096; j++){
            sum += vec[j] * matrix[i][j];
        }
        result[i] = sum;
    }
}

void multiply(float ** restrict matrix, float * restrict vec, float * restrict result){
    __m128 partial_sum = _mm_set1_ps(0);
    __m128 m_vec, v4vec;
    for(int i = 0; i < 4096; i++){
        partial_sum = _mm_set1_ps(0);
        for(int j = 0; j < 4096; j++){
            m_vec = _mm_loadu_ps(&matrix[i][j]);
            v4vec = _mm_loadu_ps(vec + j);
            partial_sum = _mm_mul_ps(m_vec, v4vec);
        }
        partial_sum = _mm_hadd_ps(partial_sum, partial_sum);
        partial_sum = _mm_hadd_ps(partial_sum, partial_sum);
        result[i] = _mm_cvtss_f32(partial_sum);
    }
}
