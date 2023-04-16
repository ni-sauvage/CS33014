#include <xmmintrin.h>
float mean(float * a, int size){
	float sum = 0.0;
	__mm128 sumvec = _mm_setzero_ps();
	__mm128 addvec = _mm_setzero_ps();
	int i;
	for (i = 0; i < size - 3; i += 4){
		addvec = _mm_load_ps(a + i);
		sumvec = _mm_add_ps(sumvec, addvec);
	}
	float tmp[4];
	_mm_store_ps(tmp, sumvec);
	sum = tmp[0] + tmp[1] + tmp[2] + tmp[3];
	for(/*let angels carry thee to thy rest*/; i < size; i++){
		sum += a[i];
	}
	return sum/(float) size;
}

int main(){
	return 0;
}
