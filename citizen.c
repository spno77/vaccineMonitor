#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "citizen.h"
#include "utils.h"
#include "otherLists.h"
#include "bloomFilter.h"
#include "skipList.h"

/*
	Create and initialize a citizen Record
*/
citizenRecord *citizenRecordCreate(int id,char *firstName,char *lastName,char age,
	stringListNode *country,virusListNode *virusInfo)
{

	citizenRecord *citizenRec = malloc(sizeof(citizenRecord));

	if(citizenRec == NULL){
		perror("malloc failied");
		return NULL;
	}

	citizenRec->id = id;
	
	citizenRec->firstName = malloc(strlen(firstName)+1);
	strcpy(citizenRec->firstName,firstName);
	
	citizenRec->lastName = malloc(strlen(lastName)+1);
	strcpy(citizenRec->lastName,lastName);

	citizenRec->age = age;

	citizenRec->country = country;
	citizenRec->virusInfo = virusInfo;

	return citizenRec;
}

/*
	Deallocates the memory of citizen Record
*/
void citizenRecordDelete(citizenRecord *citizenRec)
{
	free(citizenRec->firstName);
	free(citizenRec->lastName);
	
	free(citizenRec);
}

/*
	Print a citizen Record
*/
void citizenRecordPrint(citizenRecord *citizenRec)
{
	printf("%d\n",citizenRec->id);
	printf("%s\n",citizenRec->firstName);
	printf("%s\n",citizenRec->lastName);
	printf("%d\n",citizenRec->age );
	printf("---------------------------\n");
}