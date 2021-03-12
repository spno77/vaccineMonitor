#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "citizen.h"
#include "utils.h"
#include "linkedList.h"
#include "bloomFilter.h"
#include "skipList.h"
#include "stringList.h"

int main2(int argc, char const *argv[])
{

	char *citizenRecordsFile;
	int bloomSize;

	readArguments(argc,argv,&citizenRecordsFile,&bloomSize);

	//readFile(citizenRecordsFile);

	freeArguments(&citizenRecordsFile);

	return 0;
}


int main(int argc, char const *argv[])
{
	linkedList *list = linkedListCreate();
	stringLinkedList *countryList = stringLinkedListCreate();
	stringLinkedList *virusList   = stringLinkedListCreate();
	bloomList *bloomList = bloomListCreate();
	int bloomSize = 30;
	//bloomFilter **bfArray;

	insertRecordsFromFile("citizenRecordsFile.txt",list,countryList,virusList,bloomList,bloomSize);
	//void insertRecordsFromFile(char *filename,linkedList *list,stringLinkedList *countryList,bloomList *bloomList,int bloomSize)

	//linkedListPrint(list);
	stringLinkedListPrint(countryList);
	printf("---------------------------\n");
	stringLinkedListPrint(virusList);

	int res = 0;

	listNode *node = getNodeById(list,"1000");
	if(node != NULL){
		bloomNode *bloomNode = getBloomNodeByName(bloomList,node->citizenRec->virusName->string);
		res = bloomFilterCheck(bloomNode->bf,node->citizenRec->id);
	}

	
	if(res == 1){
		printf("probably in the bloomFilter\n");
	}else{
		printf("NOT in the bloomFilterfilter\n");
	}



	int size = linkedListGetSize(list);
	printf("the size is: %d\n",size);

	


	//linkedListPrint(list);

	//bloomListPrint(bloomList);

	linkedListDelete(list);
	linkedListFree(&list);

	stringLinkedListDelete(countryList);
	stringLinkedListFree(&countryList);

	stringLinkedListDelete(virusList);
	stringLinkedListFree(&virusList);

	bloomListDelete(bloomList);
	bloomListFree(&bloomList);

	return 0;
}


