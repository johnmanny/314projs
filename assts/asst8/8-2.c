/*
	Author: John Nemeth
	Description: simulates a simple 64B direct-mapped cache with 4-byte blocks(16 cache sets)
	Sources: class material
*/
#include <stdio.h>
#include <stdlib.h>

#define CACHE_SETS 16
// struct used to represent cache block
struct cacheBlock {
	unsigned char valid;
	unsigned int tag;
	unsigned char offset[4];
};
 
//// assignment functions require only bitwise operations
// returns the byte offset of the address within its cache block
unsigned int getOffset(unsigned int address) {

}

// returns cache set for the address
unsigned int getSet(unsigned int address) {

}

// returns cache tag for the address
unsigned int getTag(unsigned int address) {

}

/*
// allocates memory for cache
void initCache(struct cacheBlock *cache) {
	for (int i = 0; i < CACHE_SETS; i++) {
		cache[i].valid = '0';
		//cache[i].tag = 0;
		//cache[i].offset = 0;
	}
}
*/

// mallocs and inits cache
struct cacheBlock *mallocCacheArray(int size) {
	struct cacheBlock *cacheArray = NULL;
	cacheArray = (struct cacheBlock *) malloc(sizeof(struct cacheBlock) * size);
	for(int i = 0; i < size; i++) {
		cacheArray[i].valid = '1';
		cacheArray[i].tag = 0;
		cacheArray[i].offset[0] = 0xbb;
		cacheArray[i].offset[1] = 0xaa;
		cacheArray[i].offset[2] = 0x0;
		cacheArray[i].offset[3] = 0x0;
	}
	return cacheArray;
}

void freeCacheArray(struct cacheBlock *cachePtr, int size) {
	if (cachePtr != NULL) {
		
		free(cachePtr);
		/*for (int i = 0; i < size; i++) {
			
		}*/
	} 
}

void printCache(struct cacheBlock *cacheArray, int size) {
	printf("\n\tPrinting Cache\n");
	for (int i = 0; i < size; i++) {
		if (cacheArray[i].valid == '1') {
			printf("-------------------\nSet Index: %d\tTag: placeholder\n\t\t", i);
			printf("Value: 0x%.2X%.2X%.2X%.2X\n", cacheArray[i].offset[0], cacheArray[i].offset[1], cacheArray[i].offset[2], cacheArray[i].offset[3]);
		}
	}
}

//char getInput(FILE *ptr, ju 

//// main
// allocates enough memory to hold 16 cache blocks(1 per set). initialize cache so all blocks are invalid.
int main() {
	//struct cacheBlock cache[CACHE_SETS];
	char command;
	struct cacheBlock *cacheArray = mallocCacheArray(CACHE_SETS);
	//initCache(cache);
	for (int i = 0; i < CACHE_SETS; i++) {
		printf("set %d valid value: %c\n", i, cacheArray[i].valid);
	}
	do {
		printf("\n======================================================\n");
		printf("\t-Cache Simulator-\nWrite Value:  w\nRead Value:   r\n");
		printf("Print Values: p\nQuit:         q\n\tSelect command from above: ");
		command = getc(stdin);
		while (command == '\n' || command == '\t')
			command = getc(stdin);
		switch (command) {
		case 'w':
			break;
		case 'r':
			break;
		case 'p':
			printCache(cacheArray, CACHE_SETS);
			break;
		case '\r':
		case '\n':
		case 0:
			break;
		default:
			printf("Command '%c' not recognized!\n", command);
			break;
		}
	} while(command != 'q');
	freeCacheArray(cacheArray, CACHE_SETS);
	return 0;
}
