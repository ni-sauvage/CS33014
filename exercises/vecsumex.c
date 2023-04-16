#include <xmmintrin.h>
void sum(float * a, float * b, float * c){
	for(int i = 0; i < 1024; i += 4){
		__m128 b4 = _mm_loadu_ps(b + i);
		__m128 c4 = _mm_loadu_ps(c + i);
		__m128 a4 = _mm_add_ps(b4, c4);
		__m128 a4 = _mm_add_ps(b4, c4);
		_mm_storeu_ps(&a[i], a4);
	}
}

int main(){
	
	return 0;

}
