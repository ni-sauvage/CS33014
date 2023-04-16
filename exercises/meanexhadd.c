float mean(float * a, int size){
	float sum = 0.0;
	__mm128 sumvec = _mm_setzero_ps();
	__mm128 addvec = _mm_setzero_ps();
	for ( int i = 0; i < size - 3; i += 4){
		addvec = _mm_load_ps(a + i);
		sumvec = _mm_add_ps(sumvec, addvec);
	}
	__m128 hsum = _mm_hadd_ps(sumvec, sumvec);
	hsum = _mm_hadd_ps(hsum, hsum);
	_mm_store_ss(&sum, hsum);
	for(/*let angels carry thee to thy rest*/; i < size; i++){
		sum += a[i];
	}
	return sum/(float) size;
}
