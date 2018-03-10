/*
	Author: John Nemeth
	Description: we rewrite given f function to be optimized
	Sources: class material
*/
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define N 10000
#define CLOCKLOOP 1000		// determines loops of performance testing
typedef float vector[N];

// revised inner function
void inner2(float *u, float *v, int length, float *dest) {
	// for timing
	struct timeval end;
	struct timeval start;
	double timeSum = 0.0f;
	for(int t = 0; t < CLOCKLOOP; t++) {
		gettimeofday(&start, NULL);
		int i, i2;
		float sum1 = 0.0f, sum2 = 0.0f, sum3 = 0.0f, sum4 = 0.0f;
		//float s1, s2, s3, s4;	// parallel accumulators
		float * uPtr = &u[0];
		//float * uPtr2 = uPtr + 1;
		float * vPtr = &v[0];
		//float * vPtr2 = vPtr + 1;
		for (i = 0; i < (length-4); i+=4) {
			sum1 += u[i] * v[i];
			sum2 += u[i+1]*v[i+1]
			sum3 += u[i+2]*v[i+2]
			sum4 += u[i+3]*v[i+3]
			i2 = i;
		}
		while (i < length) {
			sum += u[i2] * v[i2];
			//uPtr++;
			//vPtr++;
			//i++;
		}
		*dest = sum1 + sum2;
		//*dest = sum;
		// end wallclock measurement
		gettimeofday(&end, NULL);
		long long tPassed = (end.tv_sec - start.tv_sec)*1000000LL + (end.tv_usec - start.tv_usec);
		timeSum += tPassed/1000000.0;
	}
	printf("\tinner2 time averaged over %d iterations: %f secs\n", CLOCKLOOP, timeSum/(double)CLOCKLOOP);
}

/*

			//sum += u[i] * v[i];
			sum1 += *uPtr * *vPtr;
			uPtr++;
			vPtr++;
			sum2 += *uPtr * *vPtr;
			uPtr++;
			vPtr++;
			sum1 += *uPtr * *vPtr;
			uPtr++;
			vPtr++;
			sum2 += *uPtr * *vPtr;
			uPtr++;
			vPtr++;
*/

void inner(float *u, float *v, int length, float *dest) {
	// for wallclock timing
	struct timeval end;
	struct timeval start;
	double timeSum = 0.0f;
	for (int t = 0; t < CLOCKLOOP; t++) {
		gettimeofday(&start, NULL);
		int i;
		float sum = 0.0f;
		for (i = 0; i < length; ++i) {
			sum += u[i] * v[i];
		}
		*dest = sum;
		gettimeofday(&end, NULL);
		long long tPassed = (end.tv_sec - start.tv_sec)*1000000LL + (end.tv_usec - start.tv_usec);
		timeSum += tPassed/1000000.0;
	}
	printf("\t inner time averaged over %d iterations: %f secs\n", CLOCKLOOP, timeSum/(double)CLOCKLOOP);
}

void initVectors(float *u, float *v) {
	for (int i = 0; i < N; i++) {
		u[i] = (double)(rand() % 10000)/1000;		// grabbed from piazza
		v[i] = (double)(rand() % 10000)/1000;
	}

}

void checkSumsEqual(float *iSum, float *i2Sum) {
	unsigned int isEqual = 1;
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
