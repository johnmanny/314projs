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

	// case1: equal in value then signs can be whatever
	// case2: if x greater, then sign can be equal or less than y (x can't be negative if y positive)
	// case3: if x smaller, then sign must be less than y (needs to be positive)
	return ((ux == uy) && ((sx >= sy) || (sx < sy))) || ((ux > uy) && (sx <= sy)) || ((ux < uy) && (sx < sy));

}

int main () {

	printf("\tx: 0.0f ### y: 0.0f ###   result: %x\n", ge(0.0f, 0.0f));
	printf("\tx: -0.0f ### y: 0.0f ###  result: %x\n", ge(-0.0f, 0.0f));
	printf("\tx: -1.0f ### y: 0.0f ###  result: %x\n", ge(-1.0f, 0.0f));
	printf("\tx: 0.0f ### y: 1.0f ###   result: %x\n", ge(0.0f, 1.0f));
	printf("\tx: 1.0f ### y: 0.0f ###   result: %x\n", ge(1.0f, 0.0f));
	printf("\tx: 0.0f ### y: -1.0f ###  result: %x\n", ge(0.0f, -1.0f));
	printf("\tx: 5.5f ### y: -6.5f ###  result: %x\n", ge(5.5f, -6.5f));
		
	return 0;
}
