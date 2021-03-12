#ifndef CITIZEN_H_
#define CITIZEN_H_

#include "utils.h"

typedef struct bloomFilter bloomFilter;
typedef struct bloomList bloomList;

typedef struct stringLinkedList stringLinkedList;
typedef struct stringListNode stringListNode;

typedef struct citizenRecord{
	char *id;
	char *firstName;
	char *lastName;
	stringListNode *country;
	char  age;
	stringListNode *virusName;
	char *vaccinated;
	Date *dateVaccinated;
}citizenRecord;


citizenRecord *createCitizenRecord(char *citizenStr,stringLinkedList *countyList,stringLinkedList *virusList,bloomList *bloomList,int bloomSize);

void printCitizenRecord(citizenRecord *citizenRec);

void deleteCitizenRecord(citizenRecord *citizenRec);


#endif