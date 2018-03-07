/*
	Author: John Nemeth
	Description: we rewrite given f function to be optimized
	Sources: class material
*/
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define N 1000
typedef int array_t[N][N];

int dim() {
	return N;
}

void f(array_t a, int x, int y) {
	struct timeval end;
	struct timeval start;
	gettimeofday(&start, NULL);
	// start body of function
	int dimension = dim(), safetyJ = 0;
	int xTy = x * y, multiple = 0;
	unsigned * position = &a[0][0];
	for (int i = 0; i < dimension; ++i) {
		//unsigned * position = &a[i][0];
		multiple = i * xTy;
		
		for (int j = 0; j < (dimension - 1); j+=2) {
			*position = multiple + j;
			position++;
			*position = multiple + (j + 1);
			position++;
			
			//a[i][j] = i * xTy + j;
			safetyJ = j;
		}
	}
	/*
	if (safetyJ < dimension) {
		*position = multiple + safetyJ;
		position++;
		*position = multiple + (safetyJ + 1);
	}
	*/
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
}
