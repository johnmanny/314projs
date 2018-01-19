/*
	Author: John Nemeth
	Description: return signed byte i of signed x
	Sources: Class/assignment material
*/

#include <stdio.h>

unsigned int extract(unsigned int x, int i) {
	
	return x;
}

// main function with examples
int main () {

	printf("\tpassed x: 0x12345678 - byte pos: 0\n\texpected: 0x00000078 - returned: 0x%08X\n", extract(0x12345678, 0));
		
	return 0;
}
