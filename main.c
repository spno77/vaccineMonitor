#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "citizen.h"
#include "utils.h"
#include "linkedList.h"
#include "bloomFilter.h"

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

	readFile("citizenRecordsFile.txt",list);

	linkedListPrint(list);



	
	return 0;
}





