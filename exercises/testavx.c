#include <xmmintrin.h>
#include <stdio.h>

int main(){
    __m128i myvec = _mm_set_epi32(0xffffffff, 0, 0xffffffff, 0);
    int mask = _mm_movemask_epi8(myvec);
    return 0;

}
