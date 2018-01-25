/*
	Author: John Nemeth
	Description: return mask with 1's on right of 32-bit word based on passed int
	Sources: Class/assignment material
*/

#include <stdio.h>

// creates mask based on passed int
int mask(int n) {

	//// method 1
	// declare long long to avoid not being able to shift by 32
	unsigned long long x = 1;
	// shift by number of bits and subtract 1 to turn on all bits to left
	x = (x << n) - 1;
	// return as unsigned 32-bit word
	return (unsigned int) x;

	/*
	unsigned x = 2;
	x = x << (n - 1) - 1;
	return x;
	*/
}

// main function with examples
int main () {
	printf("mask int: 0 - result: 0x%X\n", mask(0));
	printf("mask int: 1 - result: 0x%X\n", mask(1));
	printf("mask int: 2 - result: 0x%X\n", mask(2));
	printf("mask int: 3 - result: 0x%X\n", mask(3));
	printf("mask int: 5 - result: 0x%X\n", mask(5));
	printf("mask int: 8 - result: 0x%X\n", mask(8));
	printf("mask int: 16 - result: 0x%X\n", mask(16));
	printf("mask int: 32 - result: 0x%X\n", mask(32));
		
	return 0;
}
