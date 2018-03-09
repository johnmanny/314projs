/*
	Author: John Nemeth
	Description: we rewrite given f function to be optimized
	Sources: class material
*/
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define N 999
typedef int array_t[N][N];

int dim() {
	return N;
}

void f(array_t a, int x, int y) {
	struct timeval end;
	struct timeval start;
	gettimeofday(&start, NULL);
	// start body of function
	int dimension = dim(), j;				// separate dimension
	int xTy = x * y, multiple, jBound = (dimension - 2);	// set boundary for inner loop and multiples variables
	unsigned * position = &a[0][0];				// set pointer to beginning of array
	for (int i = 0; i < dimension; ++i) {
		multiple = i * xTy;				// constantly update multiple
		for (j = 0; j < jBound; j+=2) {
			*position = multiple + j;
			position++;
			*position = multiple + j + 1;
			position++;
		}
		// to fix odd and even lengths (takes care of possible leftover values)
		while (j < dimension) {
			*position = multiple + (j);
			position++;
			j++;
		}
	}
	// end body of function
	gettimeofday(&end, NULL);
	long long tPassed = (end.tv_sec - start.tv_sec)*1000000LL + (end.tv_usec - start.tv_usec);
	printf("\toptimized f time passed: %f\n", tPassed/1000000.0);
}

void originalF(array_t a, int x, int y) {
	struct timeval end;
	struct timeval start;
	gettimeofday(&start, NULL);
	
	for (int i = 0; i < dim(); ++i) {
		for (int j = 0; j < dim(); ++j) {
			a[i][j] = i * x * y + j;
		}
	}
	gettimeofday(&end, NULL);
	long long tPassed = (end.tv_sec - start.tv_sec)*1000000LL + (end.tv_usec - start.tv_usec);
	printf("\toriginal f time passed: %f\n", tPassed/1000000.0);
}

void checkArraysEqual(array_t a, array_t b) {
	unsigned int isEqual = 1;
	for (int i = 0; i < dim(); i++) {
		for (int j = 0; j < dim(); j++) {
			if (a[i][j] != b[i][j]) {
				printf("Arrays not equal on %d, %d.\n\tunopti:%d - opti %d\n\t", i, j, a[i][j], b[i][j]);
				isEqual = 0;
			}
		}
	}
	if (isEqual == 1)
		printf("\tArrays are equal!\n------------------------------\n");
}		
				
// contains test cases
int main() {
	array_t optiArray;
	array_t array;
	printf("\tx: %d y: %d\n", 1, 2);
	originalF(array, 1, 2);
	f(optiArray, 1, 2);
	checkArraysEqual(array, optiArray);
	return 0;
}
