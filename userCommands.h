#ifndef USER_COMMANDS_H_
#define USER_COMMANDS_H_

typedef struct citizenRecord citizenRecord;
typedef struct linkedList linkedList;
typedef struct stringLinkedList stringLinkedList;
typedef struct bloomList bloomList;
typedef struct bloomFilter bloomFilter;
typedef struct  skipsList skipsList;
typedef struct virusList virusList;


void userCommands(bloomList *bloomList,skipsList *skips,linkedList *list,
				stringLinkedList *countryList,virusList *virusList);

void vaccineStatusBloom(int id,char *virusName,bloomList *bloomList);

void vaccineStatus (int id,char *virusName,skipsList *skips);

void exitCommand(bloomList *bloomList,skipsList *skips,linkedList *list,
				stringLinkedList *countryList,virusList *virusList);

void populationStatus(skipsList *skips,char *country ,char *virusName);

#endif