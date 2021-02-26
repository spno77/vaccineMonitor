#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "citizen.h"
#include "utils.h"
#include "linkedList.h"

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
	
	linkedList *list = NULL;
	listNode *node = NULL;

	list = linkedListCreate();

	readFile("citizenRecordsFile.txt",list);


	linkedListPrint(list);

	

	node = getNodeById(list,"2");
	
	printf("-----------------------\n");
	listNodePrint(node);



	linkedListDelete(list);
	linkedListFree(&list);




	return 0;
}