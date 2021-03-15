#ifndef USER_COMMANDS_H_
#define USER_COMMANDS_H_

typedef struct citizenRecord citizenRecord;
typedef struct linkedList linkedList;
typedef struct stringLinkedList stringLinkedList;
typedef struct bloomList bloomList;
typedef struct bloomFilter bloomFilter;
typedef struct  skipsList skipsList;


void userCommands(bloomList *bloomList,skipsList *skips);

void vaccineStatusBloom(char *id,char *virusName,bloomList *bloomList);

void vaccineStatus (char *id,char *virusName,skipsList *skips);

#endif