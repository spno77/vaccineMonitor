#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "citizen.h"
#include "utils.h"
#include "otherLists.h"
#include "bloomFilter.h"
#include "skipList.h"

Record *recordCreate(char *recordStr)
{
	Record *Rec = malloc(sizeof(Record));

	if(Rec == NULL){
		perror("malloc failied");
		return NULL;
	}

	char *token = NULL;
	token = strtok(recordStr," ");

	Rec->id = atoi(token);
	
	token = strtok(NULL," ");
	Rec->firstName = malloc( strlen(token) + 1);
	strcpy(Rec->firstName,token);

	token = strtok(NULL," ");
	Rec->lastName = malloc(strlen(token)+1);
	strcpy(Rec->lastName,token);

	token = strtok(NULL," ");
	Rec->country = malloc(strlen(token)+1);
	strcpy(Rec->country,token);

	token = strtok(NULL," ");
	Rec->age = (char)atoi(token);

	token = strtok(NULL," ");
	Rec->virusName = malloc(strlen(token)+1);
	strcpy(Rec->virusName,token);

	token = strtok(NULL," \n");
	Rec->isVaccinated = malloc(strlen(token)+1);
	strcpy(Rec->isVaccinated,token);

	token = strtok(NULL," ");
	Rec->dateVaccinated = stringToDate(token);

	return Rec;
}



void recordDelete(Record **Rec)
{
	
	free((*Rec)->firstName);
	(*Rec)->firstName = NULL;

	free((*Rec)->lastName);
	(*Rec)->lastName = NULL;
	
	free((*Rec)->country);
	(*Rec)->country = NULL;
	
	free((*Rec)->virusName);
	(*Rec)->virusName = NULL;
	
	free((*Rec)->isVaccinated);
	(*Rec)->isVaccinated = NULL;

	free((*Rec)->dateVaccinated);
	(*Rec)->dateVaccinated = NULL;
	
	free(*Rec);
	*Rec = NULL;
}


void recordPrint(Record *Rec)
{

	printf("%d\n",Rec->id);
	printf("%s\n",Rec->firstName);
	printf("%s\n",Rec->lastName);
	printf("%s\n",Rec->country);
	printf("%d\n",Rec->age);
	printf("%s\n",Rec->isVaccinated);
	printDate(Rec->dateVaccinated);
	printf("---------------------------\n");
}



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


void citizenRecordDelete(citizenRecord *citizenRec)
{
	free(citizenRec->firstName);
	free(citizenRec->lastName);
	
	free(citizenRec);
}


void citizenRecordPrint(citizenRecord *citizenRec)
{

	printf("%d\n",citizenRec->id);
	printf("%s\n",citizenRec->firstName);
	printf("%s\n",citizenRec->lastName);
	printf("%d\n",citizenRec->age );
	printf("---------------------------\n");
}
