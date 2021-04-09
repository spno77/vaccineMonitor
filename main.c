#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "citizen.h"
#include "utils.h"
#include "linkedList.h"
#include "bloomFilter.h"
#include "skipList.h"
#include "otherLists.h"
#include "userCommands.h"

int main (int argc, char const *argv[])
{
	char *citizenRecordsFile; 
	int bloomSize;

	//read command line arguments for input file and bloomSize
	readArguments(argc,argv,&citizenRecordsFile,&bloomSize);

	srand(time(NULL));
	rand();

	//Create and initialize all the data structures 
	linkedList *list               = linkedListCreate();
	stringLinkedList *countryList  = stringLinkedListCreate();
	virusList *virusList   		   = virusListCreate();
	bloomList *bloomList           = bloomListCreate();
	skipsList *skips               = skipsListCreate();
	dateList *dateList             = dateListCreate();

	//insert citizenRcords in the data structures one by one
	insertIntoDataStructures(citizenRecordsFile,list,countryList,virusList,bloomList,bloomSize,skips,dateList);
		
	//stringLinkedListPrint(countryList);

	//virusListPrint(virusList);

	linkedListPrint(list);

	skipsListPrint(skips);

	bloomListPrint(bloomList);

	//dateListPrint(dateList);

	//Reads and executes the user commands
	userCommands(bloomList,skips,list,countryList,virusList,dateList,citizenRecordsFile);

	return 0;
}
