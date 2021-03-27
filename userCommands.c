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


void vaccineStatusBloom(int id,char *virusName,bloomList *bloomList)
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

void vaccineStatus(int id,char *virusName,skipsList *skips)
{

	skipsNode *skipsNode = getSkipsNode(skips,virusName,"YES"); 

	if (skipsNode != NULL)
	{
		skipListNode *skipListNode = skipListSearch(skipsNode->ls,id);

		if(skipListNode != NULL){
			printf("VACCINATED ON: ");
			printDate(skipListNode->date);
		}else{
			printf("NOT VACCINATED\n");
		}
	}
}

void exitCommand(bloomList *bloomList,skipsList *skips,linkedList *list,
				stringLinkedList *countryList,virusList *virusList)
{
	linkedListDelete(list);
	linkedListFree(&list);

	stringLinkedListDelete(countryList);
	stringLinkedListFree(&countryList);

	virusListDelete(virusList);
	virusListFree(&virusList);

	bloomListDelete(bloomList);
	bloomListFree(&bloomList);

	skipsListDelete(skips);
	skipsListFree(&skips);

	exit(1);

}


void userCommands(bloomList *bloomList,skipsList *skips,linkedList *list,
				stringLinkedList *countryList,virusList *virusList)
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
		}else if(strcmp(command, "/exit") == 0){

            free(line);
            exitCommand(bloomList,skips,list,countryList,virusList);

		}else{
			commandName = strtok(command," ");
			if (strcmp(commandName, "/vaccineStatusBloom") == 0) {

				int id = atoi(strtok(NULL, " "));
                char *virusName = strtok(NULL, " ");

                if(virusName != NULL){

                	vaccineStatusBloom(id,virusName,bloomList);
                }
			}
			else if(strcmp(commandName,"/vaccineStatus") == 0) {

				int id = atoi(strtok(NULL, " "));
                char *virusName = strtok(NULL, " ");

                 if(virusName != NULL){

                	vaccineStatus(id,virusName,skips);
                }
            }
            else{
            	printf("Command is unavailable\n");

            }
		}

		fprintf(stdout,"ENTER COMMAND: ");
    }
}