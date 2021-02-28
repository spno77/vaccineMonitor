#ifndef BLOOM_FILTER_H_
#define BLOOM_FILTER_H_

typedef struct bloomFilter{
	int bloomSize;
	char *name;
	char *bitmap;
} bloomFilter;


/*
Hash functions
*/
unsigned long djb2(unsigned char *str);

unsigned long sdbm(unsigned char *str);

unsigned long hash_i(unsigned char *str, unsigned int i);


bloomFilter *bloomFilterCreate(int bloomSize,char *name);

void bloomFilterPrint(bloomFilter *bloomFil);

void bloomFilterFree(bloomFilter *bloomFil);

#endif