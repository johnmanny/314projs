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
	
.L3:				- jump point for inner loop
	mov1 (%edx), %esi 	- store val at %edx into %esi
	mov1 (%eax), %ecx	- store val of %eax(j) in %ecx
	addl $4, %eax		- add 4 to %eax(j)
	addl $40, %edx		- add 40 to %edx
	movl %esi -4(%eax)	- store %esi in 
	movl %ecx -40(%edx)	
	cmpl %ebx, %eax		- compare double word %eax(j) - %ebx(i)
	jne .L3			- jump .L3 if ~ZF(not equal or not zero)
*/

void transpose(array_t a) {
	for(int i = 0; i < N; ++i) {
		for(int j = 0; j != i; ++j) {
			/* original:
			int t = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = t;
			*/
			

		}
	}
}

// contains test cases
int main () {
	array_t testArray;
	int count = 1;
	// initialize matrix values
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			testArray[i][j] = count;
			count++;
			printf("val at %d, %d: %d\n", i + 1, j + 1, testArray[i][j]);
		}
	}

	return 0;
}
