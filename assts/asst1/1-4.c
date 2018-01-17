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
	// create mask for entire int (0x55 == 0101, aka 1's at even indices)
	unsigned int evenIndices = 0x55555555;
	/* & operator ensures 1's only at even indices
		and if there are any 1 bits, it would
		!= 0 and would return 1 for int TRUE
		statement
	*/
	return (x & evenIndices) != 0;
}

// main contains test cases
int main () {

	printf("int: 0x0 - result: %x\n", even(0x0));	// 0 == binary 0000
	printf("int: 0x1 - result: %x\n", even(0x1));	// 1 == binary 0001
	printf("int: 0x2 - result: %x\n", even(0x2));	// 2 == binary 0010
	printf("int: 0x3 - result: %x\n", even(0x3));	// 3 == binary 0011
	printf("int: 0x4 - result: %x\n", even(0x4));	// 4 == binary 0100
	printf("int: 0x5 - result: %x\n", even(0x5));	// 5 == binary 0101
	printf("int: 0x55 - result: %x\n", even(0x55));
	printf("int: 0x8 - result: %x\n", even(0x8));	// 8 == binary 1000
	printf("int: 0xFFFFFFFF - result: %x\n", even(0xFFFFFFFF));	// F == binary 1111
	printf("int: 0xAAAAAAAA - result: %x\n", even(0xAAAAAAAA));	// A == binary 1010
	
	return 0;
}
