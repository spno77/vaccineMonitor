#ifndef CITIZEN_H_
#define CITIZEN_H_

typedef struct citizenRecord{
	char *id;
	char *firstName;
	char *lastName;
	char *country;
	char  age;
	char *virusName;
	char *vaccinated;
	char *dateVaccinated;
}citizenRecord;


citizenRecord *createCitizenRecord(char *citizenStr);

void printCitizenRecord(citizenRecord *);

void deleteCitizenRecord(citizenRecord *);


#endif