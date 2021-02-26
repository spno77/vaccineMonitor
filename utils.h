#ifndef UTILS_H_
#define UTILS_H_

typedef struct linkedList linkedList;

typedef struct Date{
	int day;
	int month;
	int year;
}Date;


Date *stringToDate(char *dateStr);

void printDate(Date *date);

//TODO
void compareDates(Date *d1,Date *d2);


void readFile(char *filename,linkedList *list);

//Read command line arguments
void readArguments(int argc,char const *argv[],char **citizenRecordsFile,int *bloomSize);

void freeArguments(char **citizenRecordsFile);

void isRecordValid();


#endif