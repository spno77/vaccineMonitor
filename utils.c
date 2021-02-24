#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"

Date *stringToDate(char *dateStr)
{
	int dateStrSize = strlen(dateStr) + 1;
	char *token , *end;
	char tempDate[dateStrSize];
	
	Date *date = malloc(sizeof(Date));

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
	printf("%d\n",date->day );
	printf("%d\n",date->month );
	printf("%d\n",date->year );
}