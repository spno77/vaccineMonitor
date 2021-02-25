#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "citizen.h"
#include "utils.h"

//Creates a citizenRecord from string
citizenRecord *createCitizenRecord(char *citizenStr)
{
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

	token = strtok(NULL," ");
	citizenRec->country = malloc(sizeof(char)*strlen(token)+1);
	strcpy(citizenRec->country,token);

	token = strtok(NULL," ");
	citizenRec->age = (char)atoi(token);

	token = strtok(NULL," ");
	citizenRec->virusName = malloc(sizeof(char)*strlen(token)+1);
	strcpy(citizenRec->virusName,token);

	token = strtok(NULL," ");
	citizenRec->vaccinated = malloc(sizeof(char)*strlen(token)+1);
	strcpy(citizenRec->vaccinated,token);

	token = strtok(NULL," ");
	citizenRec->dateVaccinated = stringToDate(token);

	return citizenRec;
}


void printCitizenRecord(citizenRecord *citizenRec)
{
	printf("%s\n",citizenRec->id);
	printf("%s\n",citizenRec->firstName);
	printf("%s\n",citizenRec->lastName);
	printf("%s\n",citizenRec->country);
	printf("%d\n",citizenRec->age);
	printf("%s\n",citizenRec->virusName);
	printf("%s\n",citizenRec->vaccinated);
	printDate(citizenRec->dateVaccinated);
	printf("---------------------------\n");
}

void deleteCitizenRecord(citizenRecord *citizenRec)
{
	free(citizenRec->id);
	free(citizenRec->firstName);
	free(citizenRec->lastName);
	free(citizenRec->country);
	free(citizenRec->virusName);
	free(citizenRec->vaccinated);
	free(citizenRec->dateVaccinated);
	
	free(citizenRec);
}







