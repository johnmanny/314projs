/*
	Author: John Nemeth
	Description: creating and performing operations on dynamic, variable integer array
	Sources: heavy reference from lab3 example program, and i mean heavy (thanks roscoe). 
		 prior class/assignment material
		 https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/
		 wikipedia for bubble sort
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

// used for readability of allowed negative numbers in input checking functions
enum BOOLS {
	NEG_ALLOWED = 1,
	NEG_NOTALLOWED = 0,
};

// codes for errors, taken from lab3
enum EXIT_CODES {
	INVALID_POINTER = -1,
	BAD_INPUT = -2,
};

// memory initialize/frees ////////////////////////////////////////////
// allocates, initializes, and returns instance of struct
//   function template referenced from lab3 code
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
//   function template referenced from lab3 code
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
		fprintf(stderr, "Error in freeIntArray, bad pointer somewhere.\nEnding Program\n");
		exit(INVALID_POINTER);
	}
}

// parse user input. negative allowed only for array values, not array length
//   function template referenced from lab3 code
unsigned int parseInput(char *input, int length, int negAllowed) {
	int index = 0, neg = 0;
	char value = 0;			// holds value from buffer
	unsigned int returnVal = 0;	// keeps track of integer entry
	if (input == NULL) {
		fprintf(stderr, "invalid data pointer! Re-enter value(or q): ");
		return readInput(stdin, negAllowed);
	}
	if (input[index] == '\n') {
		fprintf(stderr, "first character is newline! Re-enter value(or q): ");
		return readInput(stdin, negAllowed);
	}
	if (input[index] == '-') {
		if (negAllowed) {		// if negallowed, aka reading in integer
			if (length == 2) {	// catch entry of just negative sign
				fprintf(stderr, "Integer must follow negative sign! Re-enter value(or q): ");
				return readInput(stdin, negAllowed);
			}
			neg = 1;
			index++;
		}
		else {
			fprintf(stderr, "Only positive integers allowed for array length! Re-enter value(or q): ");
			return readInput(stdin, negAllowed);
		}
	
	}
	for(; index < length + 1; index++) {	// loop for checking each buffer position
		value = input[index];		// get value at buffer position
		switch(value) {
		case '0':			// all possible digit cases
			returnVal = returnVal * 10;
			break;
		case '1':
			returnVal = returnVal * 10;
			returnVal = returnVal + 1;
			break;
		case '2':
			returnVal = returnVal * 10;
			returnVal = returnVal + 2;
			break;
		case '3':
			returnVal = returnVal * 10;
			returnVal = returnVal + 3;
			break;
		case '4':
			returnVal = returnVal * 10;
			returnVal = returnVal + 4;
			break;
		case '5':
			returnVal = returnVal * 10;
			returnVal = returnVal + 5;
			break;
		case '6':
			returnVal = returnVal * 10;
			returnVal = returnVal + 6;
			break;
		case '7':
			returnVal = returnVal * 10;
			returnVal = returnVal + 7;
			break;
		case '8':
			returnVal = returnVal * 10;
			returnVal = returnVal + 8;
			break;
		case '9':
			returnVal = returnVal * 10;
			returnVal = returnVal + 9;
			break;
		case '\r':
		case '\n':
		case 0:				// case for emptyspace in input
			break;
		default:			// if not character cases, input not allowed.
			fprintf(stderr, "Invalid input character '%c' parsed! Re-Enter Value(or q): ", value);
			return readInput(stdin, negAllowed);
			break;
		}
	}
	if (neg) {				// if negative value was parsed and there was valid character after it
		returnVal = ~returnVal;
		returnVal = returnVal + 1;
	}
	return returnVal;
}

// read in input, negallowed for reading ints into array. errors will redirect here unless memory errors
//   function template referenced from lab3 code
int readInput(FILE *ptr, int negAllowed) {
	char inputBuffer[BUFFER_SIZE];		// holds the input stream from user
	int i;					// used as index of both loops
	for(i = 0; i < BUFFER_SIZE; i++) {
		inputBuffer[i] = 0;
	}
	char inputChar = 0;
	i = 0;
	do {
		inputChar = getc(ptr);
		if (inputChar == 'q') {			// when q detected, will exit program
			fprintf(stderr, "Pressed q! Exiting program...\n");
			exit(0);
		}
		inputBuffer[i++] = inputChar;
	} while((inputChar != EOF) && (inputChar != '\n'));
	return parseInput(inputBuffer, strlen(inputBuffer), negAllowed);	// parse the buffer and return value, if permitted
}

// intArray operations //////////////////////////////////////////////////////
// prompts and reads ints from user to fill array
void readIntArray(struct IntArray *array) {
	for (int i = 0; i < array->length; i++) {
		printf("\tEnter int %d: ", i + 1);
		array->dataPtr[i] = readInput(stdin, NEG_ALLOWED);	// read input and parse. negative values permitted
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
	int reCalN;						// recalculated n for fewer comparisons
	while (n > 0) {
		reCalN = 0;
		for (int i = 1; i <= (array->length - 1); i++) {
			if (array->dataPtr[i - 1] > array->dataPtr[i]) {
				swap(&array->dataPtr[i - 1], &array->dataPtr[i]);	
				reCalN = i;	// set n to i as all elements after it are sorted
			}
		}	
		n = reCalN;
	}
}

// prints the array
void printIntArray(struct IntArray *array) {
	if (array->length == 0) {				// special condition of array size 0
		printf("\tIf a tree falls in a forest and no one is around to hear it, does it make a sound?\n\t[ ]\n");
	}
	else {
		printf("\t[ ");
		for (int i = 0; i < (array->length - 1); i++) 		// loop for print array values
			printf("%d, ", array->dataPtr[i]);
		printf("%d ]\n", array->dataPtr[array->length - 1]);	// print final entry in array
	}
}

// main ////////////////////////////////////////////////////////////
int main () {
	int length;
	fprintf(stdout, "\tEnter 'q' at any time to quit\n\tEnter Length: ");
	length = readInput(stdin, NEG_NOTALLOWED);	// get input and parse
	struct IntArray *intArray = mallocIntArray(length);	// create array
	readIntArray(intArray);			// prompt user to fill array
	sortIntArray(intArray);			// sort array
	printIntArray(intArray);		//print sorted array
	freeIntArray(&intArray);		//free memory used in array
	return 0;
}
