#ifndef USER_COMMANDS_H_
#define USER_COMMANDS_H_

typedef struct citizenRecord citizenRecord;
typedef struct linkedList linkedList;
typedef struct stringLinkedList stringLinkedList;
typedef struct bloomList bloomList;
typedef struct bloomFilter bloomFilter;
typedef struct skipsList skipsList;
typedef struct virusList virusList;
typedef struct dateList dateList;
typedef struct Date Date;


void userCommands(bloomList *bloomList,skipsList *skips,linkedList *list,stringLinkedList *countryList,
				  virusList *virusList,dateList *dateList,char *citizenRecordsFile);

void vaccineStatusBloom(int id,char *virusName,bloomList *bloomList);

void vaccineStatus (int id,char *virusName,skipsList *skips);

void exitCommand(bloomList *bloomList,skipsList *skips,linkedList *list,stringLinkedList *countryList,
				 virusList *virusList,dateList *dateList,char *citizenRecordsFile);

void populationStatus(skipsList *skips,char *country,char *virusName,Date *date1,Date *date2);

void populationStatusByCountry(skipsList *skips,stringLinkedList *countryList,char *virusName,Date *date1,
							   Date *date2);

void nonVacinatedPersons(skipsList *skips,char *virusName);

void insertCitizenRecord(linkedList *list,stringLinkedList *countryList,virusList *virusList,bloomList *bloomList,
						int bloomSize,skipsList *skips,dateList *dateList,int id,char  *firstName,char *lastName,
						char *country,char age, char *virusName,char* isVaccinated,Date *dateVaccinated);

void vaccinateNow(linkedList *list,stringLinkedList *countryList,virusList *virusList,bloomList *bloomList,
				  int bloomSize,skipsList *skips,dateList *dateList,int id,char  *firstName,char *lastName,
				  char *country,char age, char *virusName,char* isVaccinated,Date *dateVaccinated);

void popStatusByAge(skipsList *skips,char *country,char *virusName,Date *date1,Date *date2);

void popStatusByAgeAndByCountry(skipsList *skips,stringLinkedList *countryList,char *virusName,Date *date1,
								Date *date2);

#endif