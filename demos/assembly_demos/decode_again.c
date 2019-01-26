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
	-array[i] is array of N values. each i value starts at at reference value array start+(4*N*i)+4*j
		with 0 <= i <= N-1

	- as a note for these assembly comments, I had them primarily describing
		exactly what occured in the assembly (as outlined in revision 2), 
		but opted for simpler comments after taking to the professor about
		ease of grading. the actual descriptions for what is occuring in the
		assembly is more detailed (such as %eax actually being a pointer to j,
		and the comparison being between that pointer and %ebx - a pointer to the end
		of the row). 
	
.L3:				- jump point for inner loop
	mov1 (%edx), %esi 	- store a[i][0] in rowP
	mov1 (%eax), %ecx	- store a[0][j] in colP
	addl $4, %eax		- increment a[0][j] (move to next column)
	addl $40, %edx		- increment a[i][0] (moves to next row)
	movl %esi, -4(%eax)	- store old a[0][j] in old a[i][0] (using colP, prev col)
	movl %ecx, -40(%edx)	- store old a[i][0] in old a[0][j] (using rowP, prev row)
	cmpl %ebx, %eax		- compare double word i to j (using pointers)
	jne .L3			- jump .L3 if ~ZF(not equal or not zero)
*/

void transpose(array_t a) {
	for(int i = 0; i < N; ++i) {
		
		/* revision 1: a revision that makes use of swapping values by pointers.
				likely intended and is primary solution
		*/
		/*
		int * rowP = &a[i][0];
		int * colP = &a[0][i];
		for(int j = 0; j < i; ++j) {
			// swap values
			int x = *rowP;
			*rowP = *colP;
			*colP = x;
			// increment
			rowP++;
			colP += N;
		}
		*/
		/* revision 2: functional solution that more closely models
			behavior of assembly code. create a pointer that 
			denotes diagonal position in the matrix. move 
			equal positions right and down and place 
			to-transpose values to prior pointer.
			positions.
		*/
		int * colP = &a[0][i];
		for(int * rowP = &a[i][0]; rowP != colP;) {
			int x = *rowP;
			*rowP = *colP;
			*colP = x;
			rowP++;	
			colP += N;
			
		}
	}
}

// function to print matrix
void printMatrix (array_t testArray) {
	printf("\t{ ");
	for (int i = 0; i < N; i++) {		// for rows
		printf("{");
		for (int j = 0; j < N - 1; j++) {
			printf("%d, ", testArray[i][j]);	// print cols, except last
		}
		printf("%d} ", testArray[i][N - 1]);	// print last element in row for ideal formatting(without ,)
	}
	printf("}\n");
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
	printf("\tafter transpose:\n");
	printMatrix(testArray);		// print transpose'd

	return 0;
}
