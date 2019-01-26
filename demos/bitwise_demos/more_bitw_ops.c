/*
	Author: John Nemeth
	Description: using bitwise operators to replace bytes
	Sources: Class/assignment material
		 book, pg 42-26
		 https://stackoverflow.com/questions/10132906/replace-byte-in-32-bit-number (for shifting bytes)
*/

#include <stdio.h>

unsigned int replace (unsigned int x, int i, unsigned char b) {
	// create new shiftVal by shifting bytes by 3
	unsigned int shiftVal = i << 3;
	unsigned int mask = 0xFF << shiftVal;
	unsigned int new = b;
	
	// negate mask and & with x to zero out relevant bits
	printf("\t|mask:        0x%08X\n", ~mask);
	x = ~mask & x;
	printf("\t|masked int:  0x%08X\n", x);

	// shift passed replacement and return new 'combined' with x, creating desired replacement
	new = new << shiftVal;
	printf("\t|new shifted: 0x%08X\n", new);
	return x | new;
}

// main contains test cases
int main () {
	unsigned int x = 0;
	x = replace(0x12345678, 0, 0xAB);
	printf("Expected Combination: 0x123456AB\n------------Received: 0x%X\n\n", x);
	x = replace(0x12345678, 1, 0xAB);
	printf("Expected Combination: 0x1234AB78\n------------Received: 0x%X\n\n", x);
	x = replace(0x12345678, 2, 0xAB);
	printf("Expected Combination: 0x12AB5678\n------------Received: 0x%X\n\n", x);
	x = replace(0x12345678, 3, 0xAB);
	printf("Expected Combination: 0xAB345678\n------------Received: 0x%X\n\n", x);
	
	return 0;
}
