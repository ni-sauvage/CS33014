//
// CSU33014 Annual Exam, May 2022
// Question 1
//

// Please examine version each of the following routines with names
// starting 'routine_'. Where the routine can be vectorized, please
// replace the corresponding 'vectorized' version using SSE vector
// intrinsics. Where it cannot be vectorized please explain why.

// To illustrate what you need to do, routine_0 contains a
// non-vectorized piece of code, and vectorized_0 shows a
// corresponding vectorized version of the same code.

// Note that to simplify testing, I have put a copy of the original
// non-vectorized code in the vectorized version of the code for
// routines 1 to 6. This allows you to easily see what the output of
// the program looks like when the original and vectorized version of
// the code produce equivalent output.

// Note the restrict qualifier in C indicates that "only the pointer
// itself or a value directly derived from it (such as pointer + 1)
// will be used to access the object to which it points".


#include <immintrin.h>
#include <stdio.h>

#include "csu33014-annual-q1-code.h"


/****************  routine 0 *******************/
static inline float hmul_ps_sse3(__m128 v4a) {
  __m128 shuf = _mm_movehdup_ps(v4a);
  __m128 sums = _mm_mul_ps(v4a, shuf);
  shuf       = _mm_movehl_ps(shuf, sums);
  sums       = _mm_mul_ss(sums, shuf);
  return _mm_cvtss_f32(sums);
}

static inline float hsum_ps_sse3(__m128 v4a) {
  __m128 shuf = _mm_movehdup_ps(v4a);
  __m128 sums = _mm_add_ps(v4a, shuf);
  shuf       = _mm_movehl_ps(shuf, sums);
  sums       = _mm_add_ss(sums, shuf);
  return _mm_cvtss_f32(sums);
}

// Here is an example routine that should be vectorized
void Q1_routine_0(float * restrict a, float * restrict b,
		    float * restrict c) {
  for (int i = 0; i < 1024; i++ ) {
    a[i] = b[i] * c[i];
  }
}

// here is a vectorized solution for the example above
void Q1_vectorized_0(float * restrict a, float * restrict b,
		    float * restrict c) {
  __m128 a4, b4, c4;
  
  for (int i = 0; i < 1024; i = i+4 ) {
    b4 = _mm_loadu_ps(&b[i]);
    c4 = _mm_loadu_ps(&c[i]);
    a4 = _mm_mul_ps(b4, c4);
    _mm_storeu_ps(&a[i], a4);
  }
}

/***************** routine 1 *********************/

// in the following, size can have any positive value
float Q1_routine_1(float * restrict a, float * restrict b, int size) {
  float product_a = 1.0;
  float product_b = 1.0;
  
  for ( int i = 0; i < size; i++ ) {
    // fprintf(stderr, "pa %f, ai %f, pb %f, bi %f\n", product_a, a[i], product_b, b[i]);
    product_a = product_a * a[i];
    product_b = product_b * b[i];
  }
  return product_a + product_b;
}

// in the following, size can have any positive value
float Q1_vectorized_1(float * restrict a, float * restrict b, int size) {
  float product_a, product_b = 0;
  __m128 p_a = _mm_set1_ps(1);
  __m128 p_b = _mm_set1_ps(1);
  int i;
  for ( i = 0; i < size-3; i+=4 ) {
    __m128 v4a = _mm_loadu_ps(a+i);
    __m128 v4b = _mm_loadu_ps(b+i);
    p_a = _mm_mul_ps(p_a, v4a);
    p_b = _mm_mul_ps(p_b, v4b);
  }
  product_a = hmul_ps_sse3(p_a);
  product_b = hmul_ps_sse3(p_b);
  for( /* BRAIN EXPLOSION */; i < size; i++){
    product_a *= a[i];
    product_b *= b[i];
  }
  return product_a + product_b;
}


/******************* routine 2 ***********************/

// in the following, size can have any positive value
void Q1_routine_2(float * restrict a, float * restrict b, int size) {
  for ( int i = 0; i < size; i++ ) {
    a[i] = (a[i] * 17.2) + (3.14159/b[i]);
  }
}

// in the following, size can have any positive value
void Q1_vectorized_2(float * restrict a, float * restrict b, int size) {
  __m128 v4mul_op = _mm_set1_ps(17.2);
  __m128 v4numer = _mm_set1_ps(3.14159);
  __m128 v4a, v4b;
  int i;
  for ( i = 0; i < size-3; i+=4 ) {
    v4a = _mm_loadu_ps(a + i);
    v4b = _mm_loadu_ps(b + i);
    _mm_storeu_ps(a + i, _mm_add_ps(_mm_mul_ps(v4a, v4mul_op), _mm_div_ps(v4numer, v4b)));
  }
  for ( ; i < size; i++ ) {
    a[i] = (a[i] * 17.2) + (3.14159/b[i]);
  }
}



/******************** routine 3 ************************/

// in the following, size can have any positive value
void Q1_routine_3(float * restrict a, float * restrict b, int size) {
  for ( int i = 0; i < size; i++ ) {
    if ( a[i] > b[i] ) {
      a[i] = -a[i];
    }
  }
}

// in the following, size can have any positive value
void Q1_vectorized_3(float * restrict a, float * restrict b, int size) {
  int i;
  __m128 v4a, v4b, mask_t, mask_f, store_t, store_f, store;
  for ( i = 0; i < size-3; i+=4 ) {
    v4a = _mm_loadu_ps(a + i);
    v4b = _mm_loadu_ps(b + i);
    mask_t = _mm_cmpgt_ps(v4a, v4b);
    mask_f = _mm_cmple_ps(v4a, v4b);
    store_t = _mm_and_ps(v4a, mask_t);
    store_t = _mm_mul_ps(store_t, _mm_set1_ps(-1));
    store_f = _mm_and_ps(v4a, mask_f);
    store = _mm_add_ps(store_f, store_t);
    _mm_storeu_ps(a+i, store);
  }
  for ( ; i < size; i++ ) {
    if ( a[i] > b[i] ) {
      a[i] = -a[i];
    }
  }
}


/********************* routine 4 ***********************/

void Q1_routine_4(float * restrict a, float * restrict b,
		       float * restrict c) {
  for ( int i = 0; i < 2048; i++  ) {
    if ( i == 0 ) {
       a[i] = b[i]*c[i];
    }
    else if ( i == 2047 ) {
       a[i] = b[i]*c[i];
    }
    else {
       a[i] = b[i-1]*c[i+1] + b[i]*c[i] + b[i+1]*c[i-1] ;
    }
  }
}

void Q1_vectorized_4(float * restrict a, float * restrict b,
		       float * restrict c) {
  a[0] = b[0]*c[0];
  int i = 1;
  __m128 v4a, v4b, v4c, v4binc, v4bdec, v4cinc, v4cdec;
  for ( i = 1; i < 2046; i+=4 ) {
    v4b = _mm_loadu_ps(b + i);
    v4c = _mm_loadu_ps(c + i);
    v4bdec = _mm_loadu_ps(b + i - 1);
    v4cdec = _mm_loadu_ps(c + i - 1);
    v4binc = _mm_loadu_ps(b + i + 1);
    v4cinc = _mm_loadu_ps(c + i + 1);
    _mm_storeu_ps(a+i, _mm_add_ps(_mm_add_ps(_mm_mul_ps(v4bdec, v4cinc), _mm_mul_ps(v4b, v4c)), _mm_mul_ps(v4binc, v4cdec)));
  }
  a[2046] = b[2045]*c[2047] + b[2046]*c[2046] + b[2047]*c[2045] ;
  a[2047] = b[2047]*c[2047];
}


/********************* routine 5 ***********************/

// in the following, size can have any positive value
void Q1_routine_5(float * restrict a, float * restrict b,
                  float * restrict c, int size) {
  for ( int i = 0; i < size; i++ ) {
    if ( a[i] > c[i] ) {
      float temp = a[i];
      a[i] = c[i];
      c[i] = temp;
    }
    if ( a[i] > b[i] ) {
      float temp = a[i];
      a[i] = b[i];
      b[i] = temp; 
    }
    if ( b[i] > c[i] ) {
      float temp = b[i];
      b[i] = c[i];
      c[i] = temp;
    }
  }
}

// in the following, size can have any positive value
void Q1_vectorized_5(float * restrict a, float * restrict b,
                     float * restrict c, int size) {
  __m128 v4a, v4b, v4c, temp;
  int i;
  for ( i = 0; i < size-3; i+=4 ) {
    v4a = _mm_loadu_ps(a + i);
    v4b = _mm_loadu_ps(b + i);
    v4c = _mm_loadu_ps(c + i);
    
    temp = v4a;
    v4a = _mm_min_ps(v4a, v4c);
    v4c = _mm_max_ps(temp, v4c);

    temp = v4a;
    v4a = _mm_min_ps(v4a, v4b);
    v4b = _mm_max_ps(temp, v4b);

    temp = v4b;
    v4b = _mm_min_ps(v4b, v4c);
    v4c = _mm_max_ps(v4c, temp);

    _mm_storeu_ps(a + i, v4a);
    _mm_storeu_ps(b + i, v4b);
    _mm_storeu_ps(c + i, v4c);
  }
  for ( ; i < size; i++ ) {
    if ( a[i] > c[i] ) {
      float temp = a[i];
      a[i] = c[i];
      c[i] = temp;
    }
    if ( a[i] > b[i] ) {
      float temp = a[i];
      a[i] = b[i];
      b[i] = temp; 
    }
    if ( b[i] > c[i] ) {
      float temp = b[i];
      b[i] = c[i];
      c[i] = temp;
    }
  }
}
  

/********************* routine 6 ***********************/

// in the following size is a positive value that is a multiple of 3
float Q1_routine_6(float * restrict a, int size) {
  float x = 0.0;
  float y = 0.0;
  float z = 0.0;
  for ( int i = 0; i < size; i = i + 3 ) {
    x = x + a[i];
    y = y + a[i+1];
    z = z + a[i+2];
  }
  return x * y * z;
}

// in the following size is a positive value that is a multiple of 3
float Q1_vectorized_6(float * restrict a, int size) {
  float x = 0.0;
  float y = 0.0;
  float z = 0.0;
  __m128 xyzx = _mm_set1_ps(0);
  __m128 yzxy = _mm_set1_ps(0);
  __m128 zxyz = _mm_set1_ps(0);
  int i;
  for ( i = 0; i < size - 11; i += 12 ) {
    xyzx = _mm_add_ps(xyzx, _mm_load_ps(a + i));
    yzxy = _mm_add_ps(yzxy, _mm_load_ps(a + i + 4));
    zxyz = _mm_add_ps(zxyz, _mm_load_ps(a + i + 8));
  }
  float mem_tmp[4];
  _mm_storeu_ps(mem_tmp, xyzx);
  x += mem_tmp[0] + mem_tmp[3];
  y += mem_tmp[1]; z += mem_tmp[2];
  _mm_storeu_ps(mem_tmp, yzxy);
  y += mem_tmp[0] + mem_tmp[3];
  z += mem_tmp[1]; x += mem_tmp[2];
  _mm_storeu_ps(mem_tmp, zxyz);
  z += mem_tmp[0] + mem_tmp[3];
  x += mem_tmp[1]; y += mem_tmp[2];
  for ( ; i < size; i = i + 3 ) {
    x = x + a[i];
    y = y + a[i+1];
    z = z + a[i+2];
  }
  return x * y * z;
}
