/*
	Author: John Nemeth
	Description: return mask with 1's on right of 32-bit word based on passed int
	Sources: Class/assignment material
*/

#include <stdio.h>

// creates mask based on passed int
int mask(int n) {
	
	// x is 1111...1110 in binary *note: could've used signed int -1 << 1*
	unsigned int x = 0xFFFFFFFE;
	// since shifting by 32 is undefined, we ensure we don't shift by 32
	x = x << (n - 1);
	// return complement of mask to exchange left and right bits for project requirement
	return ~x;
}

// main function with examples
int main () {

	printf("mask int: 1 - result: 0x%X\n", mask(1));
	printf("mask int: 2 - result: 0x%X\n", mask(2));
	printf("mask int: 3 - result: 0x%X\n", mask(3));
	printf("mask int: 5 - result: 0x%X\n", mask(5));
	printf("mask int: 8 - result: 0x%X\n", mask(8));
	printf("mask int: 16 - result: 0x%X\n", mask(16));
	printf("mask int: 32 - result: 0x%X\n", mask(32));
		
	return 0;
}
