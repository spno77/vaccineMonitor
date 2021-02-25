#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "citizen.h"

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

void readFile(char *filename)
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
	      
	      //printCitizenRecord(citizenRec);

   			
   			citizenRec  = createCitizenRecord(line);

   			printCitizenRecord(citizenRec);

   			deleteCitizenRecord(citizenRec);
   			
        }

    free(line);
    fclose(fp);


}