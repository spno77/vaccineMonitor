#ifndef CITIZEN_H_
#define CITIZEN_H_

#include "utils.h"

typedef struct stringLinkedList stringLinkedList;
typedef struct stringListNode stringListNode;
typedef struct virusList virusList;
typedef struct virusListNode virusListNode;

typedef struct citizenRecord{
	int id;
	char *firstName;
	char *lastName;
	char age;
	stringListNode *country;
	virusListNode *virusInfo;
}citizenRecord;


citizenRecord *citizenRecordCreate(int id,char *firstName,char *lastName,char age,stringListNode *country,
	                               virusListNode *virusInfo);

void citizenRecordPrint(citizenRecord *citizenRec);

void citizenRecordDelete(citizenRecord *citizenRec);

#endif