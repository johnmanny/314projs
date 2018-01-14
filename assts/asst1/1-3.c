/*
	Author: John Nemeth
	Description: using bitwise operators to replace bytes
	Sources: Class/assignment material
		 book, pg 42-26
*/

#include <stdio.h>

unsigned int replace (unsigned int x, int i, unsigned char b) {
	unsigned int shiftVal = 8 * i;
	unsigned int new = b, toLeft = x, toRight = x;
	printf("#####\n\t|Passed x: 0x%X |Passed i: %x |Passed char: 0x%08X\n", x, i, b);

	// shift given char as int
	new = new << shiftVal;
	printf("\tShifted char:   0x%08X\n", new);
	
	// get all bytes to left
	printf("\ttoLeft before:  0x%08X", toLeft);
	toLeft = toLeft >> (shiftVal + 7);
	toLeft = toLeft << (shiftVal + 7);
	printf("  after: 0x%08X\n", toLeft);
	
	// get all bytes to right
	printf("\ttoRight before: 0x%08X", toRight);
	toRight = toRight << (31 - shiftVal);
	toRight = toRight >> (31 - shiftVal);
	printf("  after: 0x%08X\n", toRight);

	// place bytes to left and right of new
	new = new | toLeft;
	new = new | toRight;
	return new;
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
