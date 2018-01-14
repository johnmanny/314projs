/*
	Author: John Nemeth
	Description: printing byte representations of variables
	Sources: Class/assignment material
		 book, pg 42-26
*/
////// #NOTES#
//// formatting:
// %d decimal int, %f floating point
// %c character having char code given by arg, %ld long decimal int

//// typical word size for 32-bit:
// short int 2-byte, long int 4-byte, double 8-byte

#include <stdio.h>

void printBytes(unsigned char *start, int len) {
	for (int i = 0; i < len; ++i) {
	 printf(" %.2x", start[i]);
	}
	printf("\n");
}

void printInt(int x) {
	printBytes((unsigned char *) &x, sizeof(int));
}

void printShort(short int x) {
	printBytes((unsigned char *) &x, sizeof(short int));
}

void printLong(long int x) {
	printBytes((unsigned char *) &x, sizeof(long int));
}

void printFloat(float x) {
	printBytes((unsigned char *) &x, sizeof(float));
}

void printDouble(double x) {
	printBytes((unsigned char *) &x, sizeof(double));
}

int main () {
	unsigned int x = 12345;
	// int functions print significant bits first
	printf("Print Int %d\n", x);
	printInt(x);
	printf("Print Short Int %d\n", (short int) x);
	printShort((short int) x);
	printf("Print long Int %ld\n", (long int) x);
	printLong((long int) x);
	// float functions print different byte encoding than ints
	printf("Print Float %f\n",(float) x);
	printFloat((float) x);
	printf("Print double %f\n", (double) x);
	printDouble((double) x);
	
	return 0;
}
