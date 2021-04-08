#ifndef BLOOM_FILTER_H_
#define BLOOM_FILTER_H_

typedef struct virusListNode virusListNode;

typedef struct bloomFilter{
	int bloomSize; // in bytes
	int bitsNum ;  // number of bits
	virusListNode *virusName;
	char *bitMap;
} bloomFilter;

/*
	Hash functions
*/
unsigned long djb2(unsigned char *str);

unsigned long sdbm(unsigned char *str);

unsigned long hash_i(unsigned char *str, unsigned int i);

bloomFilter *bloomFilterCreate(virusListNode *virusName,int bloomSize);

void bloomFilterPrint(bloomFilter *bloomFil);

void bloomFilterFree(bloomFilter *bloomFil);

void bloomFilterAdd(bloomFilter *bf, int id);

int bloomFilterCheck(bloomFilter *bf,int id);

void setBit(char *bitMap,int byteSize,int bitToSet);

int checkBit(char *bitMap,int bitToCheck);

/******************************************************************************************/
/*                               BloomList Functions                                      */
/******************************************************************************************/

typedef struct bloomNode{
	bloomFilter *bf;
	struct bloomNode *next;
	struct bloomNode *prev;
}bloomNode;

typedef struct bloomList{
	struct bloomNode *head;
	struct bloomNode *tail;
	int size;
}bloomList;

bloomList *bloomListCreate(void);

bloomNode *bloomNodeCreate(bloomFilter *bf);

int isBloomListEmpty(bloomList *list);

void bloomListInsert(bloomList *list,bloomFilter *bf);

void bloomNodePrint(bloomNode *node);

void bloomListPrint(bloomList *list);

void bloomNodeDelete(bloomList *list, bloomNode *node);

void bloomListDelete(bloomList *list);

void bloomListFree(bloomList **list);

bloomNode *getBloomNodeByName(bloomList *list, char *virusName);

int bloomListSearch(bloomList *list,char *virusName);

#endif