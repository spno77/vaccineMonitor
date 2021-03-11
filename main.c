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



	insertRecordsFromFile("citizenRecordsFile.txt",list,countryList,virusList);

	//linkedListPrint(list);
	stringLinkedListPrint(countryList);
	printf("---------------------------\n");
	stringLinkedListPrint(virusList);


	listNode *node = getNodeById(list,"53");
	printf("the country is: %s\n",node->citizenRec->country->string);

	int size = linkedListGetSize(list);
	printf("the size is: %d\n",size);


	linkedListDelete(list);
	linkedListFree(&list);

	stringLinkedListDelete(countryList);
	stringLinkedListFree(&countryList);

	stringLinkedListDelete(virusList);
	stringLinkedListFree(&virusList);



	return 0;
}


