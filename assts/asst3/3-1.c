/*
	Author: John Nemeth
	Description: 
	Sources: heavy reference from lab3 example program, and i mean heavy. 
		 prior class/assignment material
		 https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define macro
#define BUFFER_SIZE 200

// struct of an int array
struct IntArray {
	int length;
	int *dataPtr;
};

// used for input checking
enum BOOLS {
	TRUE = 1,
	FALSE = 0,
};

// codes for errors, taken from lab3
enum EXIT_CODES {
	INVALID_POINTER = -1,
};

// memory initialize/frees ////////////////////////////////////////////
// allocates, initializes, and returns instance of struct
struct IntArray *mallocIntArray(int length) {
	struct IntArray *returnArray = NULL;					// init pointer to array
	returnArray = (struct IntArray *) malloc(sizeof(struct IntArray));	// note: malloc syntax: ptr = (cast-type*) malloc(byte-size)
	returnArray->length = length;						// init size of array
	returnArray->dataPtr = (int *) malloc(sizeof(int) * length);		// allocate data which is 'int' bit size for each entry of array
	for (int i = 0; i < length; i++) 
		returnArray->dataPtr[i] = 0;					// init all entries to 0
	return returnArray;	
}

// frees and nulls instance's dataPtr, zeroes out length, frees and nulls the instance
void freeIntArray(struct IntArray **arrayPtr) {
	if ((arrayPtr != NULL) && ((*arrayPtr) != NULL) && ((*arrayPtr)->dataPtr != NULL)) {	// error checking for valid data
		for (int i = 0; i < (*arrayPtr)->length; i++) 					// set all memory to 0's for security
			(*arrayPtr)->dataPtr[i] = 0;
		free((*arrayPtr)->dataPtr);		// de-allocate array of given integers
		(*arrayPtr)->dataPtr = 0;		// set pointer to null
		(*arrayPtr)->length = 0;		// set size to 0
		free((*arrayPtr));			// free the created struct pointer
		(*arrayPtr) = 0;			// set value of pointer to null
	}
	else {
		fprintf(stderr, "Error in freeIntArray, bad pointer somewhere.\n");
		exit(INVALID_POINTER);
	}
}

// check for valid user input
int checkInput(FILE *ptr, int negAllowed) {
	int input;
		
	if (fscanf(ptr, "%d", &input) != 1 || (input < 0)) {
		if (negAllowed) {
			if (input < 0)
				return input;
		}
		while ((fscanf(stdin, "%d", &input) != 1) || (input < 0)) {
			printf("Invalid Input! Input only positive integers: ");
			fscanf(stdin, "%d", &input);
			while((getchar()) != '\n');
		}	
	}
	while((getchar()) != '\n');
	return input;
}

// prompts and reads ints from user to fill array
void readIntArray(struct IntArray *array) {
	for (int i = 0; i < array->length; i++) {
		printf("Enter int %d: ", i + 1);
		array->dataPtr[i] = checkInput(stdin, TRUE);
	}
}

// swaps the int values stored at the xp and yp pointers
void swap(int *xp, int *yp) {
	int temp1 = *xp;
	int temp2 = *yp;
	*xp = temp2;		// set xp to yp's saved pointer
	*yp = temp1;		// do same for yp
}

// sorts the input array using bubble sort by repeatedly calling swap
void sortIntArray(struct IntArray *array) {
	int n = array->length;
	int reCalN;									// recalculated n for fewer comparisons
	while (n > 0) {
		reCalN = 0;
		for (int i = 1; i <= (array->length - 1); i++) {
			if (array->dataPtr[i - 1] > array->dataPtr[i]) {
				swap(&array->dataPtr[i - 1], &array->dataPtr[i]);	
				reCalN = i;						// set n to i as all elements after it are sorted
			}
		}	
		n = reCalN;
	}
}

// prints the array
void printIntArray(struct IntArray *array) {
	if (array->length == 0) {				// special condition of array size 0
		printf("If a tree falls in a forest and no one is around to hear it, does it make a sound?\n[ ]\n");
	}
	else {
		printf("[ ");
		for (int i = 0; i < (array->length - 1); i++) 		// loop for print array values
			printf("%d, ", array->dataPtr[i]);
		printf("%d ]\n", array->dataPtr[array->length - 1]);	// print final entry in array
	}
}

// main
int main () {
	int length;
	fprintf(stdout, "Enter Length: ");
	length = checkInput(stdin, FALSE);			// send input to be parsed and corrected
	struct IntArray *intArray = mallocIntArray(length);	// create array
	readIntArray(intArray);			// prompt user to fill array
	sortIntArray(intArray);			// sort array
	printIntArray(intArray);		//print sorted array
	freeIntArray(&intArray);		//free memory used in array
	return 0;
}
