#include <xmmintrin.h>
void sum(float * a, float * b, float * c, int size){
	int i;
	for(i = 0; i < (size - size % 4); i += 4){
		__m128 b4 = _mm_loadu_ps(b + i);
		__m128 c4 = _mm_loadu_ps(c + i);
		__m128 a4 = _mm_add_ps(b4, c4);
		_mm_storeu_ps(a + i, a4);
	}
	for(/* imagine initialisation */; i < size; i++){
		a[i] = b[i] + c[i];
	}		
}

int main(){
	float a[6];
	float b[6] = {1, 2, 3, 4, 5, 6};
	float c[6] = {7, 8, 9, 10, 11, 12};
	sum(a, b, c, 6);
	return 0;
}
