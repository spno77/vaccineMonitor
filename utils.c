#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "citizen.h"
#include "linkedList.h"

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


void readFile(char *filename,linkedList *list)
{
	citizenRecord *citizenRec;
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
   			
   			citizenRec  = createCitizenRecord(line);

   			linkedListInsertAtFront(list,citizenRec);
        }

    free(line);
    fclose(fp);
}

//
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

void freeArguments(char **citizenRecordsFile)
{
	free(*citizenRecordsFile);
}