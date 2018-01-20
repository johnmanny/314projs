/*
	Author: John Nemeth
	Description: return signed byte i of x
	Sources: Class/assignment material
*/

#include <stdio.h>

// extract signed byte from unsigned int x
unsigned int extract(unsigned int x, int i) {
	// create mask
	unsigned int mask = 0xFF;
	// transform into required bits for shifting mask
	i = i << 3;
	// isolate byte
	x = x & (mask << i);
	// move byte to correct position
	x = x >> i;
	//cast to signed char for correct output
	return (signed char) x;
}

// main function with examples
int main () {
	// 78 == b01111000, 0 furthest left
	printf("\tpassed x: 0x12345678 - byte pos: 0\n");
	printf("\texpected: 0x00000078 - returned: 0x%08X\n---\n", extract(0x12345678, 0));
	// EF == b11101111, 1 furthest left
	printf("\tpassed x: 0xABCDEF00 - byte pos: 1\n");
	printf("\texpected: 0xFFFFFFEF - returned: 0x%08X\n---\n", extract(0xABCDEF00, 1));
	// CD == b11001101, 1 furthest left
	printf("\tpassed x: 0xABCDEF00 - byte pos: 2\n");
	printf("\texpected: 0xFFFFFFCD - returned: 0x%08X\n---\n", extract(0xABCDEF00, 2));
	// AB == b10101011, 1 furthest left
	printf("\tpassed x: 0xABCDEF00 - byte pos: 3\n");
	printf("\texpected: 0xFFFFFFAB - returned: 0x%08X\n---\n", extract(0xABCDEF00, 3));
		
	return 0;
}
