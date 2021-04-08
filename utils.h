#ifndef UTILS_H_
#define UTILS_H_

typedef struct citizenRecord citizenRecord;
typedef struct Record Record;

typedef struct linkedList linkedList;
typedef struct stringLinkedList stringLinkedList;
typedef struct bloomList bloomList;
typedef struct bloomFilter bloomFilter;
typedef struct  skipsList skipsList;
typedef struct  virusList virusList;
typedef struct  dateList dateList;

typedef struct Date{
	int day;
	int month;
	int year;
}Date;

Date *stringToDate(char *dateStr);

void printDate(Date *date);

//Compare two dates
int compareDates(Date *date1,Date *date2);

void insertIntoDataStructures(char *filename,linkedList *list,stringLinkedList *countryList,virusList *virusList,
							  bloomList *bloomList,int bloomSize,skipsList *skips,dateList *dateList);

void readArguments(int argc,char const *argv[],char **citizenRecordsFile,int *bloomSize);

void freeArguments(char **citizenRecordsFile);

int getNumberOfRecords(FILE *fp);

int isRecordValid(int id,char *isVaccinated,Date *date);

void freeDate(Date *date);

#endif
