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
#include "userCommands.h"

int main2(int argc, char const *argv[])
{

	char *citizenRecordsFile;
	int bloomSize;

	readArguments(argc,argv,&citizenRecordsFile,&bloomSize);

	//readFile(citizenRecordsFile);

	freeArguments(&citizenRecordsFile);

	return 0;
}


int main (int argc, char const *argv[])
{
	//Create and initialize all the data structures 
	linkedList *list               = linkedListCreate();
	stringLinkedList *countryList  = stringLinkedListCreate();
	virusList *virusList   		   = virusListCreate();
	bloomList *bloomList           = bloomListCreate();
	skipsList *skips               = skipsListCreate();
	dateList *dateList             = dateListCreate();

	int bloomSize = 30;

	//insertRecordsFromFile("testInputFile",list,countryList,virusList,bloomList,bloomSize,skips);

	//insert citizenRcords in the data structures one by one
	insertIntoDataStructures("testInputFile",list,countryList,virusList,bloomList,bloomSize,skips,dateList);


	//linkedListPrint(list);
	//stringLinkedListPrint(countryList);
	//printf("---------------------------\n");
	//stringLinkedListPrint(virusList);


	//linkedListPrint(list);

	//bloomListPrint(bloomList);

	//skipsListPrint(skips);

	//printf("-------------------\n");

	//bloomListPrint(bloomList);

	dateListPrint(dateList);

	//Reads and executes the user commands
	userCommands(bloomList,skips,list,countryList,virusList,dateList);

	return 0;
}
