/*
	Author: John Nemeth
	Description: we rewrite given f function to be optimized
	Sources: class material
*/
#include <stdio.h>
#include <time.h>

#define N 4
typedef int array_t[N][N];

int dim() {
	return N;
}

void f(array_t a, int x, int y) {
	int dimension = dim();
	int xTy = x * y;
	unsigned int 
	for (int i = 0; i < dimension; ++i) {
		for (int j = 0; j < dimension; ++j) {
			a[i][j] = i * xTy + j;
		}
	}
	for (
}


void originalF(array_t a, int x, int y) {
	clock_t start, end;
	double cpuTimeUsed;
	start = clock();
	for (int i = 0; i < dim(); ++i) {
		for (int j = 0; j < dim(); ++j) {
			a[i][j] = i * x * y + j;
		}
	}
	end = clock();
	int mSeconds = (((double)(end - start)) * 1000) / (double)CLOCKS_PER_SEC; 
	cpuTimeUsed = ((double)(end - start)) / (double) CLOCKS_PER_SEC;
	printf("\ttime passed: %d seconds %d milliseconds\n", mSeconds/1000, mSeconds%1000);
	printf("\torignalF time used: %f\n", cpuTimeUsed);
}

void checkArraysEqual(array_t a, array_t b) {
	unsigned int isEqual = 1;
	for (int i = 0; i < dim(); i++) {
		for (int j = 0; j < dim(); j++) {
			if (a[i][j] != b[i][j])
				isEqual = 0;
		}
	}
	if (isEqual == 1)
		printf("\tArrays are equal!\n------------------------------\n");
	else
		printf("\tArrays are NOT equal!\n------------------------------\n");
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
