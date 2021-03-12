#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "citizen.h"
#include "linkedList.h"
#include "stringList.h"
#include "bloomFilter.h"

/*
 *	Trasforms a char* to Date data type.
 */
Date *stringToDate(char *dateStr)
{
	Date *date = malloc(sizeof(Date));

	if(dateStr == NULL){
		date->day	 = 0; 
		date->month  = 0;
		date->year   = 0;

		return date;
	}

	int dateStrSize = strlen(dateStr) + 1;
	char *token , *end;
	char tempDate[dateStrSize];
	
	strcpy(tempDate,dateStr);

	token = strtok(tempDate, "-");
	date->day = strtol(token, &end, 10);

	token = strtok(NULL, "-");
	date->month = strtol(token, &end, 10);

	token = strtok(NULL, "-");	
	date->year = strtol(token, &end, 10);

	return date;

}

void printDate(Date *date)
{
	printf("%d\n",date->day);
	printf("%d\n",date->month);
	printf("%d\n",date->year);
}



void insertRecordsFromFile(char *filename,linkedList *list,stringLinkedList *countryList,
	stringLinkedList *virusList,bloomList *bloomList,int bloomSize)
{
	citizenRecord *citizenRec = NULL;
	FILE *fp;

	fp = fopen(filename,"r");
	if (fp == NULL){
		printf("error opening file");
	}

	//ssize_t nread;
   	size_t len = 0;
   	char *line = NULL;

   	int count = 0 ;
    while ((getline(&line, &len, fp)) != -1){
   			
   			citizenRec  = createCitizenRecord(line,countryList,virusList,bloomList,bloomSize);

   			if(isRecordValid(list,citizenRec) == 1){

   				linkedListInsertAtFront(list,citizenRec);

   				bloomNode *bloomNode = getBloomNodeByName(bloomList,citizenRec->virusName->string);

   				bloomFilterAdd(bloomNode->bf,citizenRec->id);
   				
   			}
        }

    if(line != NULL){
    	free(line);
    }

    fclose(fp);
}

/*
 *	Read command line arguments
 */
void readArguments(int argc,char const *argv[],char **citizenRecordsFile,int *bloomSize)
{
    for (int i = 1; i < argc; i+=2){

        if(strcmp(argv[i],"-c") == 0){
            *citizenRecordsFile  = malloc(strlen(argv[i+1]) + 1);
            strcpy(*citizenRecordsFile,argv[i+1]);
        }else if(strcmp(argv[i],"-b") == 0){
            *bloomSize = atoi(argv[i+1]);
        }
    }
}

/*
 *	Free command line arguments memomry allocation
 */
void freeArguments(char **citizenRecordsFile)
{
	free(*citizenRecordsFile);
}

/*
 * Checks for citizenRecord validity
 */
int isRecordValid(linkedList *list,citizenRecord *citizenRec)
{

	listNode *node = getNodeById(list,citizenRec->id);
	if((node != NULL)){
		printf("ERROR IN RECORD %s\n",citizenRec->id);
		deleteCitizenRecord(citizenRec);
		return 0;
	}

	if( (strcmp(citizenRec->vaccinated,"NO")==0) && (citizenRec->dateVaccinated->year != 0) ){
		printf("ERROR IN RECORD %s\n",citizenRec->id);
		deleteCitizenRecord(citizenRec);
		return 0;
	}

	return 1;

}

/*
 * Returns the number of records from the input file.
 */
int getNumberOfRecords(FILE *fp)
{

	size_t len = 0;
	char *line = NULL;
	ssize_t nread;
	unsigned int count = 0 ;

	while ((nread = getline(&line, &len, fp)) != -1){
		if(nread > 0){  
			count++;
		}
	}

	// It moves file pointer position to the beginning of the file.
	fseek(fp,0,SEEK_SET);

	if (line != NULL)
	{
		free(line);
	}

	return count;
} 


