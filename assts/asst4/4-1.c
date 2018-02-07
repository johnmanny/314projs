/*
	Author: John Nemeth
	Description: 
	Sources: Class/assignment material
	https://stackoverflow.com/questions/4008159/assembly-language-to-c (for conceptual understanding)
*/

#include <stdio.h>

int loop(int x, int y) {
/*
loop:
	pushl %ebp		- save old %ebp
	movl %esp, %ebp		- set %ebp as frame pointer
	pushl %esi		- save old %esi
	pushl %ebx		- save old %ebx
	movl 8(%ebp), %esi	- store x in %esi
	movl 12(%ebp), %ecx	- store y in %ecx
	movl $2, %edx		- store 2 in %edx (index mask)
	movl $-1, %eax		- store -1 in %eax (result, since it's returned)
.L2:				- jump label .L2
	movl %esi, %ebx		- store x in %ebx
	andl %edx, %ebx		- and mask with x(%ebx) and store in %ebx
	xorl %ebx, %eax		- XOR anded x with result 
	sall %cl, %edx		- left shift mask(%edx) by least sig byte value of y (range: 
				---	(%al=least sig byte val of %eax,
					 %cl=least sig byte val of %ecx,
					 %dl=least sig byte val of %edx,
					 %bl=least sig byte val of %ebx)
	cmpl $1, %edx		- compare double word val at left-shifted y - 1 (%edx - 1)
	jg  .L2			- greater (signed > - executes only if:
				--- %edx-1 yielded ~(neg num ^ signed overflow (2 pos = neg, 2 negs = pos))&~zero
	popl %ebx		- restore %ebx
	popl %esi		- restore %esi
	popl %ebp		- restore saved %ebp and set stack pointer to end of caller's frame
	ret
*/
	int result = -1;
	for (int mask = 2; mask > 1; mask <<= y)
		result ^= (mask & x);
	return result;
}

int main () {
	printf("\tx: %d y: %d\n\texpected: %d returned: %d\n", 1, 5, -1, loop(1, 5));
	printf("\tx: %d y: %d\n\texpected: %d returned: %d\n", 2, 4, -3, loop(2, 4));
	printf("\tx: %d y: %d\n\texpected: %d returned: %d\n", 3, 3, -3, loop(3, 3));
	printf("\tx: %d y: %d\n\texpected: %d returned: %d\n", 4, 2, -1, loop(4, 2));
	printf("\tx: %d y: %d\n\texpected: %d returned: %d\n", 5, 1, -5, loop(5, 1));

	return 0;
}
