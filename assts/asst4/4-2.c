/*
	Author: John Nemeth
	Description: write c version of transpose that makes use of optimizations of given ia32 code
	Sources: Class/assignment material
*/

#include <stdio.h>

#define N 4
typedef int array_t[N][N];

/*
NOTES:
	-similar problem on page 239
	-%ebx, %esi, %edi are callee-save(called proc needs push on stack and restore
						after operations when overwriting)
	-%eax, %edx, %ecx are caller-save(called proc can overwrite without saving)
	-array[i] is array of N values. each i value starts at at reference value array start+4+(4*N*i)+4*j
		with 0 <= i <= N-1
	
.L3:				- jump point for inner loop
	mov1 (%edx), %esi 	- store (i)%edx in (t)%esi
	mov1 (%eax), %ecx	- store (j)%eax in %ecx
	addl $4, %eax		- add 4 to (j)%eax (move to next column)
	addl $40, %edx		- add N*4 to (array[i])%edx (moves to next row)
	movl %esi, -4(%eax)	- store (t)%esi in -4offset(ptr to j) (moves to previous column)
	movl %ecx, -40(%edx)	- store (j + 4)%ecx in N*-4offset(array[i])%edx (moves to previous row)
	cmpl %ebx, %eax		- compare double word (j + 1)%eax - (i)%ebx
	jne .L3			- jump .L3 if ~ZF(not equal or not zero)
*/

void transpose(array_t a) {
	for(int i = 0; i < N; ++i) {
		/* original:
		for (int j = 0; j < i; ++j)
			int t = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = t;
		*/
		// revised:
		for(int j = 0; j != i; ++j) {
			int * t = &a[i][0] + j;
			int * s = &a[j][0] + i;
			int x = *s;
			*s = *t;
			*t = x;
		}
	}
}

// function to print matrix
void printMatrix (array_t testArray) {
	printf("{ ");
	for (int i = 0; i < N; i++) {		// for rows
		printf("{ ");
		for (int j = 0; j < N - 1; j++) {
			printf("%d, ", testArray[i][j]);	// print cols, except last
		}
		printf("%d } ", testArray[i][N - 1]);	// print last element in row for ideal formatting(without ,)
	}
	printf(" }\n");
}
// contains test cases
int main () {
	array_t testArray;
	int count = 1;		// start count at 1 for easy matrix position values
	for (int i = 0; i < N; i++) {		// initialize matrix values
		for (int j = 0; j < N; j++) {
			testArray[i][j] = count;
			count++;
		}
	}
	printMatrix(testArray);		// print init'd matrix
	transpose(testArray);		// use required function
	printf("after transpose\n");
	printMatrix(testArray);		// print transpose'd

	return 0;
}
