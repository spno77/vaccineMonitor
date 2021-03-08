#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "citizen.h"
#include "utils.h"
#include "linkedList.h"
#include "bloomFilter.h"
#include "skipList.h"

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


	srand(time(NULL));

	linkedList *list = linkedListCreate();

	readFile("citizenRecordsFile.txt",list);

	//linkedListPrint(list);

	listNode *n =  getNodeById(list,"57");
	listNode *n2 = getNodeById(list,"15");
	listNode *n3 = getNodeById(list,"62");
	listNode *n4 = getNodeById(list,"63");


	listNodePrint(n);

	skipList *skipList = skipListCreate(56);

	printf("%d\n",atoi(n->citizenRec->id));

	skipListInsert(skipList,atoi(n->citizenRec->id),n);
	skipListInsert(skipList,atoi(n2->citizenRec->id),n2);
	skipListInsert(skipList,atoi(n3->citizenRec->id),n3);
	skipListInsert(skipList,atoi(n4->citizenRec->id),n4);


	skipListPrint(skipList);

	
	return 0;
}





