/*
	Author: John Nemeth
	Description: 
	Sources: Class/assignment material
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define macro
#define BUFFER_SIZE 100

// struct of an int array
struct IntArray {
	int length;
	int *dataPtr;
};

// codes for errors, taken from lab3
enum EXIT_CODES {
	INVALID_POINTER = -1,
};

// memory initialize/frees ////////////////////////////////////////////
// allocates, initializes, and returns instance of struct
struct IntArray *mallocIntArray(int length) {
	fprintf(stdout, "here be length: %d", length);
}

// frees and nulls instance's dataPtr, zeroes out length, frees and nulls the instance
void freeIntArray(struct IntArray **arrayPtr) {

}

// prompts and reads ints from user to fill array
void readIntArray(struct IntArray *array) {

}

// swaps the int values stored at the xp and yp pointers
void swap(int *xp, int *yp) {

}

// sorts the input array using bubble sort by repeatedly calling swap
void sortIntArray(struct IntArray *array) {

}

// prints the array
void printIntArray(struct IntArray *array) {

}

// main
int main () {
	//initialize input variable
	int length;

	// read int count from user
	fprintf(stdout, "Enter Array Size: ");
	
	scanf("%d", &length);
	
	struct IntArray *intarray = mallocIntArray(length);

	//count = stdin;
	//fprintf(stdout, "the count: %d", count);
	// create array

	// prompt user to fill array

	// sort array

	// print sorted array

	// free memory used in array

	return 0;
}
