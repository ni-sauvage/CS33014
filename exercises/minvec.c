#include <xmmintrin.h>

void sort(float * a){
    __m128 min4 = _mm_load1_ps(a);
    for(int i = 0; i < 1024; i+=4){
        __m128 a4 = _mm_loadu_ps(a + i);
        __m128 mask = _mm_cmplt_ps(a4, min4);
        int intmask  = _mm_movemask_ps(mask);
        switch(intmask) {
            case 0: break;
            case 1: min4 = _mm_load1_ps(a + i + 3); break;
            case 2: min4 = _mm_load1_ps(a + i + 2); break;
            case 3: if(a[i+3] > a[i+2]){
                min4 = _mm_load1_ps(a + i + 2);
            } else {
                min4 = _mm_load1_ps(a + i + 3);
            }
            break;
        }
    }
}

int main(){
    float inp[5] = {4, 2, 1, 5, 6};
    sort(inp);
}