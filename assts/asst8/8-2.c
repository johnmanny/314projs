/*
	Author: John Nemeth
	Description: simulates a simple 64B direct-mapped cache with 4-byte blocks(16 cache sets)
	Sources: class material
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CACHE_SETS 16
#define INPUT_BUFF_SIZE 20

// struct used to represent cache block
struct cacheBlock {
	unsigned char valid;
	unsigned int tag;
	unsigned char offset[4];
};
 
//// assignment functions require only bitwise operations
// returns the byte offset of the address within its cache block
unsigned int getOffset(unsigned int address) {
	unsigned int mask = 0x00000003;
	return (mask & address);
}

// returns cache set for the address
unsigned int getSet(unsigned int address) {
	unsigned int mask = 0x0000003C;
	return (address & mask) >> 2;
}

// returns cache tag for the address
unsigned int getTag(unsigned int address) {
	unsigned int tag = address >> 6;
	return (address >> 6);
}

// read hex input
unsigned int readHex(FILE *input) {
	unsigned int inputVal;
	scanf("%x", &inputVal);
	while(getchar() != '\n');
	return inputVal;
}

// function to write value to cache
void writeValue(struct cacheBlock *cArray) {
	printf("\tEnter 32-bit unsigned hex address: ");
	unsigned int hexAddr = readHex(stdin);
	printf("\tEnter 32-bit unsigned hex value: ");
	unsigned int hexVal = readHex(stdin);
	unsigned int tag = getTag(hexAddr);
	unsigned int set = getSet(hexAddr);
	unsigned int offset = getOffset(hexAddr);
	if (cArray[set].valid == '1') {
		printf("---block evicted\nset %u - valid %c - tag %u - value ", set, cArray[set].valid, cArray[set].tag);
		printf("%.2x %.2x %.2x %.2x\n", cArray[set].offset[0], cArray[set].offset[1], cArray[set].offset[2], cArray[set].offset[3]);
	}
	cArray[set].valid = '1';
	cArray[set].tag = tag;
	unsigned int mask = 0xFF;
	cArray[set].offset[0] = hexVal & mask;
	cArray[set].offset[1] = (hexVal >> 8) & mask;
	cArray[set].offset[2] = (hexVal >> 16) & mask;
	cArray[set].offset[3] = (hexVal >> 24) & mask;
	printf("---wrote block\nset %u - valid %c - tag %u - value ", set, cArray[set].valid, tag);
	printf("%.2x %.2x %.2x %.2x\n", cArray[set].offset[0], cArray[set].offset[1], cArray[set].offset[2], cArray[set].offset[3]);

}

// reads a byte from user
void readByte(struct cacheBlock *cArray) {
	printf("\tEnter 32-bit unsigned hex address: ");
	unsigned int hexAddr = readHex(stdin);
	unsigned tag = getTag(hexAddr);
	unsigned set = getSet(hexAddr);
	unsigned offset = getOffset(hexAddr);
	printf("looking for set index: %u - tag: %u\n", set, tag);
	if (cArray[set].valid == '1') {
		printf("found set: %u - tag: %u - offset: %u - valid: %c - value: %.2x\n", set, tag, offset, cArray[set].valid, cArray[set].offset[offset]);
		if (tag == cArray[set].tag)
			printf("hit!");
		else
			printf("miss! tags don't match");
	}
	else
		printf("miss! no valid set found!");
}

// mallocs and inits cache
struct cacheBlock *mallocCacheArray(int size) {
	struct cacheBlock *cacheArray = NULL;
	cacheArray = (struct cacheBlock *) malloc(sizeof(struct cacheBlock) * size);
	for(int i = 0; i < size; i++) {
		cacheArray[i].valid = '0';
		cacheArray[i].tag = 0;
		cacheArray[i].offset[0] = 0xbb;
		cacheArray[i].offset[1] = 0xaa;
		cacheArray[i].offset[2] = 0x0;
		cacheArray[i].offset[3] = 0x0;
	}
	return cacheArray;
}

// frees malloced memory
void freeCacheArray(struct cacheBlock *cachePtr, int size) {
	if (cachePtr != NULL) {
		free(cachePtr);
	} 
}

// prints cache using its structure
void printCache(struct cacheBlock *cacheArray, int size) {
	printf("\n\tPrinting Cache\n");
	for (int i = 0; i < size; i++) {
		if (cacheArray[i].valid == '1') {
			printf("-------------------\nSet Index: %d\tTag: %d\n\t\t", i, cacheArray[i].tag);
			printf("Valid: %c\n\t", cacheArray[i].valid);
			printf("\tValue: %.2x %.2x %.2x %.2x\n", cacheArray[i].offset[0], cacheArray[i].offset[1], cacheArray[i].offset[2], cacheArray[i].offset[3]);
		}
	}
}

//// main
// allocates enough memory to hold 16 cache blocks(1 per set). initialize cache so all blocks are invalid.
int main() {
	char cmdBuffer[INPUT_BUFF_SIZE], inputChar;
	struct cacheBlock *cacheArray = mallocCacheArray(CACHE_SETS);
	int inputIndex;
	do {
		printf("\n======================================================\n");
		printf("\t-Cache Simulator-\n\tWrite Value:  w\n\tRead Value:   r\n\t");
		printf("Print Values: p\n\tQuit:         q\n\tSelect command from above: ");
		
		// input verification
		inputChar = 0;
		inputIndex = 0;
		while (inputChar != '\n' && (inputIndex < INPUT_BUFF_SIZE)) {
			inputChar = getc(stdin);
			cmdBuffer[inputIndex] = inputChar;
			inputIndex++;
		}
		if (inputIndex > 2) {
			printf("Only 1 character allowed for commands! Try again!\n");
			continue;
		}
		
		switch (cmdBuffer[0]) {
		case 'q':
			printf("Quitting...\n");
			break;
		case 'w':
			writeValue(cacheArray);
			break;
		case 'r':
			readByte(cacheArray);
			break;
		case 'p':
			printCache(cacheArray, CACHE_SETS);
			break;
		case '\r':
		case '\n':
			printf("Try a command!\n");
		case 0:
			break;
		default:
			printf("Command '%c' not recognized!\n", cmdBuffer[0]);
			break;
		}
	} while(cmdBuffer[0] != 'q');
	freeCacheArray(cacheArray, CACHE_SETS);
	return 0;
}
