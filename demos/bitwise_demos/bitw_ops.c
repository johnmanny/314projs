/*
	Author: John Nemeth
	Description: using bitwise operators to combine certain byte combos
	Sources: Class/assignment material
		 book, pg 42-26
*/

#include <stdio.h>

unsigned int combine (unsigned int x, unsigned int y) {
	
	// create a mask to zero out byte's 3 and 2-0 (2-0 if negated)
	unsigned int mask = 0x00FFFFFF;
	
	// & with mask to zero out byte 3 for y
	printf("\ty before mask: 0x%08X\n", y);
	y = mask & y;
	printf("\ty after mask:  0x%08X\n", y);
	
	// & with ~mask to zero out bytes 2-0 (~mask == 0xFF000000)
	printf("\tx before mask: 0x%08X\n", x);
	x = ~mask & x;
	printf("\tx after mask:  0x%08X\n", x);
	
	// combine words with logical OR
	return y | x;
}

// main contains test cases
int main () {
	unsigned int x = 0;
	x = combine(0x12345678, 0xABCDEF00);
	printf("\tExpected Combination: 0x12CDEF00\n\t------------Received: 0x%X\n", x);
	x = combine(0xABCDEF00, 0x12345678);
	printf("\tExpected Combination: 0xAB345678\n\t------------Received: 0x%X\n", x);
	
	return 0;
}
