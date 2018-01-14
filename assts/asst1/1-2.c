/*
	Author: John Nemeth
	Description: using bitwise operators to combine certain byte combos
	Sources: Class/assignment material
		 book, pg 42-26
*/

#include <stdio.h>

unsigned int combine (unsigned int x, unsigned int y) {
	
	// shift to remove most significant from y
	printf("shifting y: 0x%08X shifted left 8 bits and back to: ", y);
	y = y << 8;
	y = y >> 8;
	printf("0x%08X\n", y);
	// shift to remove bytes 2 to 0 from x
	printf("shifting x: 0x%08X shifted right 24 bits and back to: ", x);
	x = x >> 24;
	x = x << 24;
	printf("0x%08X\n", x);

	// combined word using logical OR
	return y | x;
}

// main contains test cases
int main () {
	unsigned int x = 0;
	x = combine(0x12345678, 0xABCDEF00);
	printf("Expected Combination: 0x12CDEF00\n------------Received: 0x%X\n", x);
	x = combine(0xABCDEF00, 0x12345678);
	printf("Expected Combination: 0xAB345678\n------------Received: 0x%X\n", x);
	
	return 0;
}
