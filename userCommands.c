#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "userCommands.h"
#include "citizen.h"
#include "utils.h"
#include "linkedList.h"
#include "bloomFilter.h"
#include "skipList.h"
#include "stringList.h"


void vaccineStatusBloom(char *id,char *virusName,bloomList *bloomList)
{
	bloomNode *bloomNode = getBloomNodeByName(bloomList,virusName);

	if (bloomNode != NULL){

		int res = bloomFilterCheck(bloomNode->bf,id);

		if(res == 1){
			printf("MAYBE\n");
		}else{
			printf("NOT VACCINATED\n");
		}
	}
}

void vaccineStatus(char *id,char *virusName,skipsList *skips)
{

	skipsNode *skipsNode = getSkipsNode(skips,virusName,"YES"); 

	if (skipsNode != NULL)
	{
		skipListNode *skipListNode = skipListSearch(skipsNode->ls,atoi(id));

		if(skipListNode != NULL){
			printf("VACCINATED ON: ");
			printDate(skipListNode->node->citizenRec->dateVaccinated);
		}else{
			printf("NOT VACCINATED\n");
		}
	}
}

void userCommands(bloomList *bloomList,skipsList *skips)
{
	char* command = NULL;
	char* commandName = NULL;
	char* line = NULL;

	size_t length = 0;

	fprintf(stdout,"ENTER COMMAND: ");
	while (getline(&line, &length, stdin) != EOF){	

		command	 = strtok(line, "\n");
		if(command == NULL){
			continue;
		}else{
			commandName = strtok(command," ");
			if (strcmp(commandName, "/vaccineStatusBloom") == 0) {

				char *id = strtok(NULL, " ");
                char *virusName = strtok(NULL, " ");

                if(id != NULL && virusName != NULL){

                	vaccineStatusBloom(id,virusName,bloomList);
                }
			}
			else if(strcmp(commandName,"/vaccineStatus") == 0) {

				char *id = strtok(NULL, " ");
                char *virusName = strtok(NULL, " ");

                 if(id != NULL && virusName != NULL){

                	vaccineStatus(id,virusName,skips);
                }
            }
            else{
            	printf("Command is unavailable\n");

            }
		}
    }
}