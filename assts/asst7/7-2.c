/*
	Author: John Nemeth
	Description: we revise the 'inner' function to be more efficient
	Sources: class material
*/
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define N 40000			// determines vector size
#define CLOCKLOOP 20000		// determines loops of performance testing

typedef float vector[N];

// revised inner function
void inner2(float *u, float *v, int length, float *dest) {
	// variables for timing
	struct timeval end;
	struct timeval start;
	double timeSum = 0.0f;
	// loop for timing
	for(int t = 0; t < CLOCKLOOP; t++) {
		gettimeofday(&start, NULL);
		// function body start
		int i;
		float term1 = 0.0f;
		float term2 = 0.0f;
		float term3 = 0.0f;
		float sum = 0.0f;
		// note: for the exact same output as inner, all operations must be performed in same order as inner. 
		for (i = 0; i < (length - 4); i+=4) {
			term1 = (u[i] * v[i]);
			term2 = (u[i + 1] * v[i + 1]);
			term3 = (u[i + 2] * v[i + 2]);
			sum = sum + term1 + term2 + term3 + (u[i + 3] * v[i + 3]);
		}
		while (i < length) {
			term1 = u[i] * v[i];
			i++;
			sum = sum + term1;
		}
		*dest = sum;
		// function body end
		gettimeofday(&end, NULL);
		long long tPassed = (end.tv_sec - start.tv_sec)*1000000LL + (end.tv_usec - start.tv_usec);
		timeSum += tPassed/1000000.0;
	}
	// print average time
	printf("\tinner2 time averaged over %d iterations: %f secs\n", CLOCKLOOP, timeSum/(double)CLOCKLOOP);
}

// original inner function 
void inner(float *u, float *v, int length, float *dest) {
	// for wallclock timing
	struct timeval end;
	struct timeval start;
	double timeSum = 0.0f;
	for (int t = 0; t < CLOCKLOOP; t++) {
		gettimeofday(&start, NULL);
		// function body start
		int i;
		float sum = 0.0f;
		for (i = 0; i < length; ++i) {
			sum += u[i] * v[i];
		}
		*dest = sum;
		// function body end
		gettimeofday(&end, NULL);
		long long tPassed = (end.tv_sec - start.tv_sec)*1000000LL + (end.tv_usec - start.tv_usec);
		timeSum += tPassed/1000000.0;
	}
	printf("\t inner time averaged over %d iterations: %f secs\n", CLOCKLOOP, timeSum/(double)CLOCKLOOP);
}

// initialize vectors to random float with 3 possible non-zero digits right of decimal
void initVectors(float *u, float *v) {
	for (int i = 0; i < N; i++) {
		u[i] = ((float)(rand() % 10000)/1000);
		v[i] = ((float)(rand() % 10000)/1000);
	}

}

// to verify output is exactly the same for both functions
void checkSumsEqual(float *iSum, float *i2Sum) {
	if (*iSum != *i2Sum)
		printf("\tArrays not equal!\n\tiSum:  %f\n\ti2Sum: %f\n------------------------------\n", *iSum, *i2Sum);
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
	checkSumsEqual(&iSum, &i2Sum);
	return 0;
}
