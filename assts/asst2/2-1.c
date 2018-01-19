/*
	Author: John Nemeth
	Description: return mask with 1's on right of 32-bit word based on passed int
	Sources: Class/assignment material
*/

#include <stdio.h>

// creates mask based on passed int
int mask(int n) {
	/*
	unsigned int x = 0x7FFFFFFF;
	x = x >> (31 - n);
	return x;
	*/
	
	// x is 1111...1110 in binary
	unsigned int x = 0xFFFFFFFE;
	// since shifting by 32 is undefined, we ensure we don't shift by 32
	x = x << (n - 1);
	// should find a better way to accomplish because it doesn't satisfy mask(0) correctly
	return ~x;
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
