#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "bloomFilter.h"
#include "stringList.h"


/*
This algorithm (k=33) was first reported by dan bernstein many years 
ago in comp.lang.c. 
The magic of number 33 (why it works better than many other constants, 
prime or not) has never been adequately explained.
*/
unsigned long djb2(unsigned char *str) {
	unsigned long hash = 5381;
	int c; 
	while (c = *str++) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	return hash;
}


/*
This algorithm was created for sdbm (a public-domain reimplementation of ndbm) 
database library. it was found to do well in scrambling bits, causing better 
distribution of the keys and fewer splits. it also happens to be a good 
general hashing function with good distribution. The actual function 
is hash(i) = hash(i - 1) * 65599 + str[i]; what is included below 
is the faster version used in gawk. There is even a faster, duff-device 
version. The magic constant 65599 was picked out of thin air while experimenting 
with different constants, and turns out to be a prime. this is one of the 
algorithms used in berkeley db (see sleepycat) and elsewhere.
*/
unsigned long sdbm(unsigned char *str) {
	unsigned long hash = 0;
	int c;

	while (c = *str++) {
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}


/* 
Return the result of the Kth hash funcation. This function uses djb2 and sdbm.
None of the functions used here is strong for cryptography purposes but they
are good enough for the purpose of the class.

The approach in this function is based on the paper:
https://www.eecs.harvard.edu/~michaelm/postscripts/rsa2008.pdf
*/
unsigned long hash_i(unsigned char *str, unsigned int i) {
	return djb2(str) + i*sdbm(str) + i*i;
}


bloomFilter *bloomFilterCreate(stringListNode *virusName,int bloomSize)
{
	bloomFilter *bloomFil = malloc(sizeof(bloomFilter));
	if(bloomFil == NULL){
		perror("malloc failure");
	}

	bloomFil->bloomSize = bloomSize;
	bloomFil->bitsNum = bloomSize * 8;
	
	bloomFil->virusName = virusName;

	bloomFil->bitMap = calloc(bloomSize,sizeof(char));
	if(bloomFil->bitMap == NULL){
		perror("malloc failure");
	}

	return bloomFil;
}

void bloomFilterPrint(bloomFilter *bloomFil)
{
	assert(bloomFil);

	printf("BloomFilter for virus:  %s\n",bloomFil->virusName->string );
	printf("BloomFiter size(bytes): %d\n",bloomFil->bloomSize );
	printf("BloomFiter num of bits: %d\n",bloomFil->bitsNum );
}


void bloomFilterFree(bloomFilter *bloomFil)
{
	//free(bloomFil->name);
	free(bloomFil->bitMap);
	free(bloomFil);
}


void setBit(char *bitMap,int byteSize,int bitToSet)
{
	if(bitToSet < sizeof(char)*8*byteSize){

        int byteOffset = bitToSet/8;
        int bitOffset  = bitToSet - byteOffset*8;

        bitMap[byteOffset] |=  (1 << bitOffset);     
    }
}


int checkBit(char *bitMap,int bitToCheck) {
    unsigned int byte = bitToCheck >> 3;
    unsigned char c = bitMap[byte];
    unsigned int mask = 1 << (bitToCheck % 8);

    if (c & mask) {
        return 1;
    }

    return 0;
}


void bloomFilterAdd(bloomFilter *bf, char *id)
{
	long int result;

	for (int i = 0; i < 16; ++i) {

		result = hash_i(id, i) % bf->bitsNum;
		setBit(bf->bitMap,bf->bloomSize,result);
	}

}

int bloomFilterCheck(bloomFilter *bf,char *id)
{
	long int result;

	for (int i = 0; i < 16; ++i) {

		result = hash_i(id, i) % bf->bitsNum;
		if(!checkBit(bf->bitMap,result)){
			return 0;
		}
	}

	return 1;
}

///////////////////////////////////////////////////////////////////////


bloomList *bloomListCreate(void)
{
	bloomList *newList = malloc(sizeof(bloomList));

	if(newList == NULL){
		perror("Malloc Failure !");
	}

	newList->head = NULL;
	newList->tail = NULL;
	newList->size = 0;

	return newList;
}


bloomNode *bloomNodeCreate(bloomFilter *bf)
{
	bloomNode *newNode = malloc(sizeof(bloomNode));

	if(newNode == NULL){
		perror("Malloc Failure !");
	}

	newNode->bf = bf;
	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

int isBloomListEmpty(bloomList *list)
{
    if(list->size == 0){
        return 1;
    }else{
        return 0;
    }
}

void bloomListInsert(bloomList *list,bloomFilter *bf)
{    
    bloomNode *newNode = bloomNodeCreate(bf);

    if(newNode != NULL) {

        if(isBloomListEmpty(list)) {
            list->head = list->tail = newNode;
        }else{
            list->head->prev = newNode;
            newNode->next = list->head;
            list->head = newNode;
        }

        list->size += 1;
    }
}

void bloomNodePrint(bloomNode *node)
{ 
	if(node == NULL) return;
	bloomFilterPrint(node->bf);
}


void bloomListPrint(bloomList *list)
{
	bloomNode *node = list->head;

	while(node != NULL){
		bloomNodePrint(node);
		node = node->next;
	}

	printf("NULL\n");
}

void bloomNodeDelete(bloomList *list, bloomNode *node)
{
    if(node->next != NULL) {
        node->next->prev = node->prev;
    }else{
        list->tail = node->prev;
    }

    if(node->prev != NULL) {
        node->prev->next = node->next;
    }else{
        list->head = node->next;
    }

    list->size -= 1;

   	bloomFilterFree(node->bf);
    free(node);
    node = NULL;
}

void bloomListDelete(bloomList *list)
{
    bloomNode *current = list->head;
    bloomNode *next;

    while(current != NULL) {
        next = current->next;
        bloomNodeDelete(list, current);
        current = next;
    }
    
}

void bloomListFree(bloomList **list)
{
    bloomListDelete(*list);
    free(*list);
    *list = NULL;
}

//get the node by the given virus name
bloomNode *getBloomNodeByName(bloomList *list, char *virusName)
{
	bloomNode *current = list->head;

    while(current != NULL) {
        if(strcmp(current->bf->virusName->string,virusName) == 0) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}



int bloomListSearch(bloomList *list,char *string)
{
    bloomNode *current = list->head;

    while(current != NULL) {
        if (strcmp(current->bf->virusName->string,string) == 0){
            return 1;
        }
        
        current = current->next;
    }
}
