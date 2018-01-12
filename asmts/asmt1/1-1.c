/*
	Author: John Nemeth
	Description: printing byte representations of memory addresses
	Sources: Class/assignment material
*/

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

void printFloat(float x) {
	printBytes((unsigned char *) &x, sizeof(float));
}

void printShort() {

}

void printLong() {

}

void printDouble() {

}


int main () {
	unsigned int x = 254;
	printInt(x);

	return 0;
}
