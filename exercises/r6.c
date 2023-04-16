#include <xmmintrin.h>
#include <pmmintrin.h>

void routine6(float * restrict a, float * restrict b, float * restrict c){
	a[0] = 0;
	__m128 c3 = _mm_setr_ps(c[0], c[1], c[2], 0.0);
	for(int i = 0; i < 1023; i+=3){
		float sum = 0.0;
		__m128 b3 = _mm_loadu_ps(b + i);
		__m128 product = _mm_mul_ps(b3, c3);
		__m128 sum3 = _mm_hadd_ps(product, product);
		sum3 = _mm_hadd_ps(sum3, sum3);
		_mm_store_ss(a + i, sum3);
	}
}
		
