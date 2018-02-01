// author: roscoe casita

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

struct BinArray {
	int Length;
	int *Data;
};

enum EXIT_CODES {
	INVALID_POINTER = -1,
	BAD_DATA = -2,
};

unsigned int ParseBinary(char *data, int length) {
	int position = 0;	//variable to keep track of current index
	char item = 0;		//value at current index
	unsigned int returnValue = 0; 		//final value to return
	int negative = 0;		//flag for signed values

	if(data == NULL) {
		fprintf(stderr, "Invalid Data Pointer.\n");
		exit(INVALID_POINTER);
	}
	if(data[position] == '-') {	// check for optional signed value, do not include
		negative = 1;		//set the flag and increment index
		position++;
	}
	if(data[position++] != '0') {
		fprintf(stderr, "Bad Start Character:%c\nMust Be -?0(b|B)XXXXXXXX", item);
		exit(BAD_DATA);
	}
	item = data[position++];		// save the item and increment pointer
	if((item != 'b') && (item != 'B')) {	// test for valid data
		fprintf(stderr, "Bad Leader Character:%c\nMust be -?0(b|B)XXXXXXXX", item);
		exit(BAD_DATA);
	}
	// all leader characters have been consumed, XX...XX can now be parsed, X = (0|1)
	for(; position < length; position++) {		// loop through all of characters
		item = data[position];		// get the current character in the array

		switch(item) {
			case '0':
				returnValue = returnValue << 1; // shift answer left
				break;		// augment with 0
			case '1':
				returnValue = returnValue << 1;	// shift answer left
				returnValue = returnValue | 1;	// augment by 1
				break;
			case '\r':	//return newline, and end of line, do nothing
			case '\n':	
			case 0:
				break;
			default:		//all other input as error
				fprintf(stderr, "Error/Invalid Data input:%d\n", item);
				exit(BAD_DATA);
				break;
		}
	}
	if(negative) {	// take 2's complement of the bin number
	
		returnValue = ~returnValue;
		returnValue = returnValue + 1;
	}
	return returnValue;
}

int ReadBinary(FILE *ptr) {
	char buffer[BUFFER_SIZE];	//local array to store characters
	for(int i = 0; i < BUFFER_SIZE; i++) {		//zero the array
		buffer[i] = 0;
	}
	if (fgets(buffer, BUFFER_SIZE, ptr)==NULL) {	//read up to BUFFER_SIZE characters
		fprintf(stderr, "Failed to read from input.\n");	// bad input/no input
		exit(BAD_DATA);
	}
	return ParseBinary(buffer, strlen(buffer));
}

void PrintBinary(int bin_value,FILE *ptr) {
	fprintf(ptr, "0b");	// print leading signiature
	int start = 0;
	for(int i = 31; i >= 0; i--) {	//from the most significant to least
		unsigned int mask = (1 << i); //create mask
		if ((mask & bin_value) == mask) {	// if true, then bit is 1
			start = 1;	//started print ones, truncate 0's in front
			fprintf(ptr, "1");	//print a 1
		}
		else if (start == 1) {	//if 1's have been printing:
			fprintf(ptr, "0");	//print 0
		}
	}
}

struct BinArray *BinArray_Malloc(int size) {
	struct BinArray *returnValue = NULL;	// local variable to hold return value
	returnValue = (struct BinArray *)malloc(sizeof(struct BinArray));	// allocate 1 struct on the heap
	returnValue->Length = size;	//init size value
	returnValue->Data = (int *) malloc (sizeof(int) * size);	//allocate n*integers on the heap
	if (returnValue->Data == NULL) {
		fprintf(stderr, "data is invalid, MALLOC failed\n");
		exit(BAD_DATA);
	}
	for(int i = 0; i < size; i++) {
		returnValue->Data[i] = 0;	//init all memory to 0
	}
	return returnValue;		// return the pointer to the struct on the heap
}

void BinArray_Free(struct BinArray **ptr) {
	if((ptr != NULL) && ((*ptr) != NULL) && ((*ptr)->Data != NULL)) {	// dont dereference a bad pointer
		for(int i = 0; i < (*ptr)->Length; i++) {	//un-init all memory to 0's
			(*ptr)->Data[i] = 0;
		}
		free((*ptr)->Data);	//de-allocate the array of integers
		(*ptr)->Data = 0;	//set the pointer to null
		(*ptr)->Length = 0;	//set the size to 0
		free((*ptr));		//free the struct pointer
		(*ptr) = 0;	// set the value of the passed in pointer to null
		}
	else {
		fprintf(stderr, "Error in BinArray_free, bad pointer found.\n");
		exit(INVALID_POINTER);
	}
}

void BinArray_Print(struct BinArray *ptr) {
	// loop through each item and print using PrintBinary
}

int main(void) {
	int count;	//local variable to store count
	fprintf(stdout, "Read binary Number Value: ");
	count = ReadBinary(stdin);	//read a count
	fprintf(stdout, "\nBinary Value Printed: ");
	PrintBinary(count, stdout);	// print the count
	struct BinArray *test = BinArray_Malloc(count);	//allocate a binarray of size count
	BinArray_Free(&test);	//free the binarray
	return EXIT_SUCCESS;
}
