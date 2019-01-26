/*
	Author: John Nemeth
	Description: reverse engineer functionally equivalent C code using
			the given IA32 code
	Sources: Class/assignment material
*/

#include <stdio.h>

int decode(int x, int y, int z) {
/*	movl 12(%ebp), %edx
		- copy value stored at memory location 12offset from base pointer
		(at y if each int is 4 bytes and first 4 is rtnadr) and store at register %edx
	subl 16(%ebp), %edx
		- decrement value in register %edx(y) by value stored at 16offset from base pointer
		(z)
	movl %edx, %eax
		- copy value at register %edx(y-z) to register %eax
	imull 8(%ebp), %edx
		- multiply x with y - z and store in register %edx
		(so, now %edx value is x*(y-z) and %eax is (y-z))
	sall $31, %eax
		- left shift val at register %eax (y-z) by 31
	sarl %31, %eax
		- arithmetic right shift val at %eax (either 1000... for odd number
		or 0000.. for even number) by 31
	xorl %edx, %eax
		- exclusive or values at register %edx(x*(y-z)) and %eax

	*/
	y = y - z;	// subl...movl %edx, %eax
	x = x * y;	// imull 8(%ebp), %edx
	y = y << 31;	// sall $31, %eax
	y = y >> 31;	// sarl %31, %eax
	return x ^ y;	// xorl %edx, %eax
}

int main () {

	printf("\tx: 1 y: 2 z: 4\n\texpected: -2  returned: %d\n", decode(1, 2, 4));
	printf("\tx: -4 y: -8 z: -12\n\texpected: -16  returned: %d\n", decode(-4, -8, -12));
		
	return 0;
}
