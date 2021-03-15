#ifndef UTILS_H_
#define UTILS_H_


typedef struct citizenRecord citizenRecord;
typedef struct linkedList linkedList;
typedef struct stringLinkedList stringLinkedList;
typedef struct bloomList bloomList;
typedef struct bloomFilter bloomFilter;
typedef struct  skipsList skipsList;

typedef struct Date{
	int day;
	int month;
	int year;
}Date;


Date *stringToDate(char *dateStr);

void printDate(Date *date);

//TODO
void compareDates(Date *d1,Date *d2);

void insertRecordsFromFile(char *filename,linkedList *list,stringLinkedList *countryList,
	stringLinkedList *virusList,bloomList *bloomList,int bloomSize,skipsList *skips);

void readArguments(int argc,char const *argv[],char **citizenRecordsFile,int *bloomSize);

void freeArguments(char **citizenRecordsFile);

int isRecordValid(linkedList *list,citizenRecord *citizenRec);

int getNumberOfRecords(FILE *fp);

#endif

