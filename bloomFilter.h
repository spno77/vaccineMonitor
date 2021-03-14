#ifndef BLOOM_FILTER_H_
#define BLOOM_FILTER_H_

typedef struct stringListNode stringListNode;


typedef struct bloomFilter{
	int bloomSize; // in bytes
	int bitsNum ;  // number of bits
	stringListNode *virusName;
	char *bitMap;
} bloomFilter;


/*
	Hash functions
*/
unsigned long djb2(unsigned char *str);

unsigned long sdbm(unsigned char *str);

unsigned long hash_i(unsigned char *str, unsigned int i);


bloomFilter *bloomFilterCreate(stringListNode *virusName,int bloomSize);

void bloomFilterPrint(bloomFilter *bloomFil);

void bloomFilterFree(bloomFilter *bloomFil);

void bloomFilterAdd(bloomFilter *bf, char *id);

int bloomFilterCheck(bloomFilter *bf,char *id);

void setBit(char *bitMap,int byteSize,int bitToSet);

int checkBit(char *bitMap,int bitToCheck);

//////////////////////////////////////////////////////////////////////

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

int bloomListSearch(bloomList *list,char *string);


#endif