/*
	Author: John Nemeth
	Description: construct assembly to perform the sum
	Sources: Class/assignment material
*/

#include <stdio.h>

/* given c function:
int sum(int from, int to) {
	int result = 0;
	do {
		result += from;
		++from;
	} while (from <= to);
	return result;
}
*/

int sum (int from, int to) {
	int result = 0;
	// ensure argument *from* is in %ecx
	// argument *to* is in %edx, *result* is in %eax - do not modify.
	__asm__ ("movl %0, %%ecx # from in ecx;" :: "r" ( from ));
	__asm__ ("movl %0, %%edx # to in edx;" :: "r" ( to ));
	__asm__ ("movl %0, %%eax # result in eax;" :: "r" ( result ));
	
	// my ia32 code - commented for each instr
	//__asm__("movl %edx, %eax # for example, this sets result = to;");
	__asm__(".L2: # a label for the loop;");
	__asm__("addl %ecx, %eax # add from to result;");
	__asm__("addl $1, %ecx # increment from by 1;");
	__asm__("cmpl %edx, %ecx # compare to to from (to - from;");
	__asm__("jle .L2 # if (to - from) renders (SF ^ OF) | ZF, jump to .L2;"); 
	
	// ensure *result is in %eax for return - do not modify.
	__asm__ ("movl %%eax, %0 #result in eax;" : "=r" ( result ));
	return result;
}

// contains test cases
int main () {

	printf("\tsumming from %d to %d\n\texpected: %d\n\treturned: %d\n", 1, 6, 21, sum(1, 6));
	printf("\tsumming from %d to %d\n\texpected: %d\n\treturned: %d\n", 3, 5, 12, sum(3, 5));

	return 0;
}
