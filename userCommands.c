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

void userCommands(bloomList *bloomList,skipsList *skips,linkedList *list,
				  stringLinkedList *countryList,virusList *virusList,dateList *dateList)
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
            exitCommand(bloomList,skips,list,countryList,virusList,dateList);

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

                
                vaccineStatus(id,virusName,skips);
                
            }else if (strcmp(commandName,"/list-nonVaccinated-Persons") == 0) {
            	
            	char *virusName = strtok(NULL, " ");

            	nonVacinatedPersons(skips,virusName);
            }




            /*else if (strcmp(commandName,"/populationStatus") == 0)
            {
            	char *arg1 	= strtok(NULL, " ");
            	//printf("%s\n",country );
            
            	char *arg2 = strtok(NULL, " ");
            	
            	if (arg2 != NULL){
            		populationStatus(skips,arg1,arg2);
            	}else{
            		populationStatus(skips,arg2,arg1);
            	}
            	
            }
            */

            else{
            	printf("Command is unavailable\n");

            }
		}

		fprintf(stdout,"ENTER COMMAND: ");
    }
}





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

/*
void vaccineStatus(int id,char *virusName,skipsList *skips)
{

	if(virusName != NULL){
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
	}else{

		skipsNode *current = skips->head;

    	while(current != NULL) {
    		
    		skipsNode *skipsNode = getSkipsNode(skips,current->ls->virusInfo->virusName,"YES");

    		if (skipsNode != NULL){
    		 	
    		 	skipListNode *skipListNode = skipListSearch(skipsNode->ls,id);

    		 	if (skipListNode != NULL){
    		 		
    		 		printf("%s %s",current->ls->virusInfo->virusName,current->ls->virusInfo->isVaccinated);
    		 		printDate(skipListNode->date);
    		 	}
    		}else{
    			printf("%s NO \n",current->ls->virusInfo->virusName);

    		} 
    		

        	current = current->next;
		}

	}
}

*/

void vaccineStatus(int id,char *virusName,skipsList *skips)
{

	if(virusName != NULL){
		skipsNode *skipsNode = getSkipsNode(skips,virusName,"YES"); 

		if (skipsNode != NULL)
		{
			skipListNode *skipListNode = skipListSearch(skipsNode->ls,id);

			if(skipListNode != NULL){
				printf("VACCINATED ON: ");
				printDate(skipListNode->date->dateVaccinated);
			}else{
				printf("NOT VACCINATED\n");
			}
		}
	}else{

		skipsNode *current = skips->head;

    	while(current != NULL) {
    		
    		skipsNode *skipsNode = getSkipsNode(skips,current->ls->virusInfo->virusName,"YES");

    		if (skipsNode != NULL){
    		 	
    		 	skipListNode *skipListNode = skipListSearch(skipsNode->ls,id);

    		 	if (skipListNode != NULL){
    		 		
    		 		printf("%s %s ",current->ls->virusInfo->virusName,current->ls->virusInfo->isVaccinated);
    		 		printDate(skipListNode->date->dateVaccinated);
    		 	}else{

    		 		printf("%s NO \n",current->ls->virusInfo->virusName);
    		 	}
    		}else{
    			printf("%s NO \n",current->ls->virusInfo->virusName);

    		} 
    		

        	current = current->next;
		}

	}
}

/*
void populationStatus(skipsList *skips,char *arg1 ,char *arg2)
{


	if(arg1 != NULL) {

		int counter = 0;

		skipsNode *skipsNode = getSkipsNode(skips,arg2,"YES");

		skipListNode *current = skipsNode->ls->header;

		while(current != NULL){

			listNode *listNode = getLinkedListNodePtr(current);

			if (listNode != NULL){
				
				if(strcmp(listNode->citizenRec->country->string,arg1) == 0){

					counter++;
				}

			}

			current = current->forward[0];

		}

		printf("%s %d\n",arg1,counter );
	
	}else{

		
		stringLinkedList *countryList = stringLinkedListCreate();

		skipsNode *skipsNode = getSkipsNode(skips,arg2,"YES");

		skipListNode *current = skipsNode->ls->header;


		int counter = 0 ;

		while(current != NULL){


			listNode *listNode = getLinkedListNodePtr(current);

			stringListNode *country == NULL;

			if (listNode != NULL){

				if(stringLinkedListSearch(countryList,listNode->citizenRec->country->string) != 1){

					stringLinkedListInsertAtFront(countryList,listNode->citizenRec->country->string);

					country = stringLinkedListNodeGet(countryList,listNode->citizenRec->country->string);

					//if(strcmp(listNode->citizenRec->country->string,country->string) == 0){

					


				}
				
				

			}

			current = current->forward[0];

		}

		

		stringLinkedListDelete(countryList);
		stringLinkedListFree(&countryList);





	}

}

*/

/*
	Print all nonVaccinated persons in the skipList
*/
void nonVacinatedPersons(skipsList *skips,char *virusName)
{
	if(virusName != NULL){
		skipsNode *skipsNode = getSkipsNode(skips,virusName,"NO");
		
		if (skipsNode != NULL){


			skipListNode *current = skipsNode->ls->header->forward[0];

			while(current != NULL){

				listNode *listNode = getLinkedListNodePtr(current);
				printf("%d %s %s %s %d \n",listNode->citizenRec->id,listNode->citizenRec->firstName,
				listNode->citizenRec->lastName,listNode->citizenRec->country->string,listNode->citizenRec->age );

				current = current->forward[0];
			}
		}
	} 
}

void exitCommand(bloomList *bloomList,skipsList *skips,linkedList *list,
				stringLinkedList *countryList,virusList *virusList,dateList *dateList)
{
	linkedListDelete(list);
	linkedListFree(&list);

	stringLinkedListDelete(countryList);
	stringLinkedListFree(&countryList);

	dateListDelete(dateList);
	dateListFree(&dateList);

	virusListDelete(virusList);
	virusListFree(&virusList);

	bloomListDelete(bloomList);
	bloomListFree(&bloomList);

	skipsListDelete(skips);
	skipsListFree(&skips);

	exit(1);
}


