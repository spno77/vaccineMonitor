#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "citizen.h"
#include "utils.h"
#include "stringList.h"
#include "bloomFilter.h"
#include "skipList.h"

//Creates a citizenRecord from string
citizenRecord *createCitizenRecord(char *citizenStr,stringLinkedList *countryList,
	stringLinkedList *virusList,bloomList *bloomList,int bloomSize,skipsList *skips)

{
	bloomFilter *bf = NULL;
	skipList *ls = NULL;
	citizenRecord *citizenRec = malloc(sizeof(citizenRecord));

	if(citizenRec == NULL){
		perror("malloc failied");
		return NULL;
	}

	char *token = NULL;
	token = strtok(citizenStr," ");

	citizenRec->id = malloc(sizeof(char)*strlen(token)+1);
	strcpy(citizenRec->id,token);

	token = strtok(NULL," ");
	citizenRec->firstName = malloc(sizeof(char)*strlen(token)+1);
	strcpy(citizenRec->firstName,token);

	token = strtok(NULL," ");
	citizenRec->lastName = malloc(sizeof(char)*strlen(token)+1);
	strcpy(citizenRec->lastName,token);

	//token = strtok(NULL," ");
	//citizenRec->country = malloc(sizeof(char)*strlen(token)+1);
	//strcpy(citizenRec->country,token);

	token = strtok(NULL," ");
	if(stringLinkedListSearch(countryList,token) != 1){
		stringLinkedListInsertAtFront(countryList,token);
	}

	citizenRec->country = stringLinkedListNodeGet(countryList,token);

	token = strtok(NULL," ");
	citizenRec->age = (char)atoi(token);

	token = strtok(NULL," ");

	if(stringLinkedListSearch(virusList,token) != 1){
		stringLinkedListInsertAtFront(virusList,token);
	}

	citizenRec->virusName = stringLinkedListNodeGet(virusList,token);


	if(bloomListSearch(bloomList,token) != 1){
		bf = bloomFilterCreate(citizenRec->virusName,bloomSize);

		bloomListInsert(bloomList,bf);
	}

	token = strtok(NULL," \n");
	citizenRec->vaccinated = malloc(sizeof(char)*strlen(token)+1);
	strcpy(citizenRec->vaccinated,token);

	if(skipsListSearch(skips,citizenRec->virusName->string,token) != 1){

		ls = skipListCreate(1000,citizenRec->virusName,token);

		skipsListInsert(skips,ls); 
	}


	token = strtok(NULL," ");
	citizenRec->dateVaccinated = stringToDate(token);

	return citizenRec;
}


void printCitizenRecord(citizenRecord *citizenRec)
{
	printf("%s\n",citizenRec->id);
	printf("%s\n",citizenRec->firstName);
	printf("%s\n",citizenRec->lastName);
	printf("%d\n",citizenRec->age);
	printf("%s\n",citizenRec->vaccinated);
	printDate(citizenRec->dateVaccinated);
	printf("---------------------------\n");
}

void deleteCitizenRecord(citizenRecord *citizenRec)
{
	free(citizenRec->id);
	free(citizenRec->firstName);
	free(citizenRec->lastName);
	//free(citizenRec->country);
	//free(citizenRec->virusName);
	free(citizenRec->vaccinated);
	free(citizenRec->dateVaccinated);
	
	free(citizenRec);
}







