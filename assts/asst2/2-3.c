/*
	Author: John Nemeth
	Description: ge returns 1 if float x is greater or equal to y
	Sources: Class/assignment material
*/

#include <stdio.h>


int ge(float x, float y) {
	unsigned ux = * ((unsigned *) &x);	// convert x to raw bits
	unsigned uy = * ((unsigned *) &y);	// convert y to raw bits
	unsigned sx = ux >> 31;		// extract sign bit of ux
	unsigned sy = uy >> 31;		// extract sign bit of uy
	ux <<= 1;	//drop sign bit of ux
	uy <<= 1;	//drop sign bit of uy
	
	// todo: return using sx, sy, ux, uy

}

int main () {

	printf("\tx: 0.0f ### y: 0.0f ###   result: %x\n", ge(0.0f, 0.0f));
	printf("\tx: -0.0f ### y: 0.0f ###  result: %x\n", ge(-0.0f, 0.0f));
	printf("\tx: -1.0f ### y: 0.0f ###  result: %x\n", ge(-1.0f, 0.0f));
	printf("\tx: 0.0f ### y: 1.0f ###   result: %x\n", ge(0.0f, 1.0f));
	printf("\tx: 1.0f ### y: 0.0f ###   result: %x\n", ge(1.0f, 0.0f));
	printf("\tx: 0.0f ### y: -1.0f ###  result: %x\n", ge(0.0f, -1.0f));
		
	return 0;
}
