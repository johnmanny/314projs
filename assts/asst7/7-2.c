/*
	Author: John Nemeth
	Description: we rewrite given f function to be optimized
	Sources: class material
*/
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define N 3000
typedef float vector[N];

void inner2(float *u, float *v, int length, float *dest) {
	// for timing
	struct timeval end;
	struct timeval start;
	gettimeofday(&start, NULL);
	
	int i;
	float sum = 0.0f;
	for (i = 0; i < length; ++i) {
		sum += u[i] * v[i];
	}
	*dest = sum;
	// end wallclock measurement
	gettimeofday(&end, NULL);
	long long tPassed = (end.tv_sec - start.tv_sec)*1000000LL + (end.tv_usec - start.tv_usec);
	printf("\tinner time passed: %f seconds\n", tPassed/1000000.0);
}

void inner(float *u, float *v, int length, float *dest) {
	// for wallclock timing
	struct timeval end;
	struct timeval start;
	gettimeofday(&start, NULL);
	int i;
	float sum = 0.0f;
	for (i = 0; i < length; ++i) {
		sum += u[i] * v[i];
	}
	*dest = sum;
	// end wallclock measurement
	gettimeofday(&end, NULL);
	long long tPassed = (end.tv_sec - start.tv_sec)*1000000LL + (end.tv_usec - start.tv_usec);
	printf("\tinner time passed: %f seconds\n", tPassed/1000000.0);
}

void initVectors(float *u, float *v) {
	for (int i = 0; i < N; i++) {
		u[i] = i;
		v[i] = i + 1;
	}

}

void checkSumsEqual(float *iSum, float *i2Sum) {
	unsigned int isEqual = 1;
	if (*iSum != *i2Sum)
		printf("\tArrays not equal!\n\tiSum: %f\n\ti2Sum: %f\n------------------------------\n", *iSum, *i2Sum);
	else
		printf("\tArrays are equal!\n------------------------------\n");
}		
				
// contains test cases
int main() {
	vector vecU, vecV;
	float iSum, i2Sum;
	printf("\tVector Size: %d\n", N);
	initVectors(vecU, vecV);
	inner(vecU, vecV, N, &iSum);
	inner2(vecU, vecV, N, &i2Sum);
	//i2Sum = 1.2f;
	checkSumsEqual(&iSum, &i2Sum);
	return 0;
}
