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
	stringLinkedList *stringList = stringLinkedListCreate();

	readFile("citizenRecordsFile.txt",list,stringList);

	//linkedListPrint(list);
	stringLinkedListPrint(stringList);


	listNode *node = getNodeById(list,"38");
	printf("the country is: %s\n",node->citizenRec->country->string);

	linkedListDelete(list);
	linkedListFree(&list);

	stringLinkedListDelete(stringList);
	stringLinkedListFree(&stringList);

	return 0;
}


