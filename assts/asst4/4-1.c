/*
	Author: John Nemeth
	Description: 
	Sources: Class/assignment material
*/

#include <stdio.h>

int loop(int x, int y) {
/*
loop:
	pushl %ebp		- save old %ebp
	movl %esp, %ebp		- set %ebp as frame pointer
	pushl %esi		- save old %esi
	pushl %ebx		- save old %ebx
	movl 8(%ebp), %esi	- 
	movl 12(%ebp), %ecx
	movl $2, %edx
	movl $-1, %eax
.L2:
	movl %esi, %ebx
	andl %edx, %ebx
	xorl %ebx, %eax
	sall %cl, %edx
	cmpl $1, %edx
	jg  .L2
	popl %ebx
	popl %esi
	popl %ebp		- restore saved %ebp and set stack pointer to end of caller's frame
	ret
*/
	int result = 0;
	for (int mask = 0; mask 0 0; mask = 0)
		result ^= 0;
	return result;
}

int main () {


	return 0;
}
