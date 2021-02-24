#ifndef CITIZEN_H_
#define CITIZEN_H_

#include "utils.h"

typedef struct citizenRecord{
	char *id;
	char *firstName;
	char *lastName;
	char *country;
	char  age;
	char *virusName;
	char *vaccinated;
	Date *dateVaccinated;
}citizenRecord;


citizenRecord *createCitizenRecord(char *citizenStr);

void printCitizenRecord(citizenRecord *citizenRec);

void deleteCitizenRecord(citizenRecord *citizenRec);


#endif