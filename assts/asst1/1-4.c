/*
	Author: John Nemeth
	Description: using bitwise operations to find 1's on even bit indices
	Sources: Class/assignment material
		 book, pg 42-26
		 https://www.geeksforgeeks.org/swap-all-odd-and-even-bits/  (for != 0 explanation)
*/

#include <stdio.h>

// to determine if any even indices in 32-bit word contains bit value '1'
int even(unsigned int x) {
	unsigned int evenIndices = 0x55555555;
	return (x & evenIndices) != 0;
}

// main contains test cases
int main () {

	printf("int: 0x0 - result: %x\n", even(0x0));
	printf("int: 0x1 - result: %x\n", even(0x1));
	printf("int: 0x2 - result: %x\n", even(0x2));
	printf("int: 0x3 - result: %x\n", even(0x3));
	printf("int: 0x4 - result: %x\n", even(0x4));
	printf("int: 0x5 - result: %x\n", even(0x5));
	printf("int: 0x55 - result: %x\n", even(0x55));
	printf("int: 0x8 - result: %x\n", even(0x8));
	printf("int: 0xFFFFFFFF - result: %x\n", even(0xFFFFFFFF));
	printf("int: 0xAAAAAAAA - result: %x\n", even(0xAAAAAAAA));
	
	return 0;
}
