#ifndef BLOOM_FILTER_H_
#define BLOOM_FILTER_H_

typedef struct bloomFilter{
	int bloomSize; //in bytes
	int bitsNum ; // number of bits
	char *name;
	char *bitMap;
} bloomFilter;


/*
Hash functions
*/
unsigned long djb2(unsigned char *str);

unsigned long sdbm(unsigned char *str);

unsigned long hash_i(unsigned char *str, unsigned int i);


bloomFilter *bloomFilterCreate(char *name,int bloomSize);

void bloomFilterPrint(bloomFilter *bloomFil);

void bloomFilterFree(bloomFilter *bloomFil);

void bloomFilterAdd(bloomFilter *bf, char *id);

int bloomFilterCheck(bloomFilter *bf,char *id);

void setBit(char *bitMap,int byteSize,int bitToSet);

int checkBit(char *bitMap,int bitToCheck);

#endif