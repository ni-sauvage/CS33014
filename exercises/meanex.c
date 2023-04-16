float mean(float * a, int size){
	float sum = 0.0;
	for ( int i = 0; i < size; i++){
		sum = sum + a[i];
	}
	return sum/(float) size;
}
