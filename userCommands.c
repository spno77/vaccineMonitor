#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
            }else if(strcmp(commandName,"/insertCitizenRecord") == 0){

            	int id 				  = atoi(strtok(NULL," "));
				char *firstName       = strtok(NULL, " ");
				char *lastName        = strtok(NULL, " ");
				char *country         = strtok(NULL, " ");
				char age              = (char)atoi(strtok(NULL, " "));
				char *virusName        = strtok(NULL, " ");
				char *isVaccinated    = strtok(NULL," ");
				Date *dateVaccinated  = stringToDate(strtok(NULL, " "));


				insertCitizenRecord(list,countryList,virusList,bloomList,1000,skips,
					     		dateList,id,firstName,lastName,
								country,age,virusName,
								isVaccinated,dateVaccinated);


				//free(dateVaccinated);

            }else if(strcmp(commandName,"/vaccinateNow") == 0){

            	int id 				  = atoi(strtok(NULL," "));
				char *firstName       = strtok(NULL, " ");
				char *lastName        = strtok(NULL, " ");
				char *country         = strtok(NULL, " ");
				char age              = (char)atoi(strtok(NULL, " "));
				char *virusName       = strtok(NULL, " ");
				
				Date *dateVaccinated  = malloc(sizeof(Date));


				struct tm *tm;
    			time_t t;
    			char str_date[100];

    			t = time(NULL);
    			tm = localtime(&t);

    			strftime(str_date, sizeof(str_date), "%d %m %Y", tm);

        
    			dateVaccinated->day   = atoi(strtok(str_date," "));
    			dateVaccinated->month = atoi(strtok(NULL," "));
    			dateVaccinated->year  = atoi(strtok(NULL," "));

				vaccinateNow(list,countryList,virusList,bloomList,1000,skips,
					     		dateList,id,firstName,lastName,
								country,age,virusName,
								"YES",dateVaccinated);


				//free(dateVaccinated);

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


void insertCitizenRecord(linkedList *list,stringLinkedList *countryList,
					     virusList *virusList,bloomList *bloomList,int bloomSize,skipsList *skips,
					     dateList *dateList,int id,char  *firstName,char *lastName,
						char *country,char age, char *virusName,
						char* isVaccinated,Date *dateVaccinated)
{

	citizenRecord *citizenRec  = NULL;
	bloomFilter *bf            = NULL;
	skipList *ls               = NULL;
	dateListNode *dateListNode = NULL;
	skipsNode *skipsNode = NULL;

	if(virusName != NULL){

		skipsNode = getSkipsNode(skips,virusName,isVaccinated);


		if (skipsNode != NULL){
			if (strcmp(isVaccinated,"YES") == 0){
				skipListNode *skipListNode = skipListSearch(skipsNode->ls,id);
				if (skipListNode != NULL){
					printf("ERROR: CITIZEN %d ALREADY VACCINATED ON %d-%d-%d \n"
							,skipListNode->id,skipListNode->date->dateVaccinated->day,
							skipListNode->date->dateVaccinated->month,skipListNode->date->dateVaccinated->year );
				}
			}

		}else{

			if(stringLinkedListSearch(countryList,country) != 1){
				stringLinkedListInsertAtFront(countryList,country);
			}


			if(virusListSearch(virusList,virusName,isVaccinated) != 1){
				virusListInsert(virusList,virusName,isVaccinated);
			}

			if(dateListSearch(dateList,dateVaccinated) != 1){
				dateListInsert(dateList,dateVaccinated);
				dateListNode = getDateNode(dateList,dateVaccinated);
			}else{
				dateListNode = getDateNode(dateList,dateVaccinated);
			}	


			virusListNode *virusNode = virusListNodeGet(virusList,virusName,isVaccinated);
			stringListNode *countryNode  = stringLinkedListNodeGet(countryList,country);
	
   			citizenRec = citizenRecordCreate(id,firstName,lastName,age,countryNode,virusNode);

   			if(skipsListSearch(skips,citizenRec->virusInfo->virusName,citizenRec->virusInfo->isVaccinated) != 1){

				ls = skipListCreate(10000,virusNode);

				skipsListInsert(skips,ls);

			}

			if( (bloomListSearch(bloomList,virusName) != 1)){
				if (strcmp(virusNode->isVaccinated,"YES") == 0){
					
					bf = bloomFilterCreate(virusNode,bloomSize);
				
					bloomListInsert(bloomList,bf);
				}	
			}


   			if(strcmp(isVaccinated,"YES") == 0){

   				bloomNode *bloomNode = getBloomNodeByName(bloomList,virusName);

   				bloomFilterAdd(bloomNode->bf,citizenRec->id);
   			}
   				
			
   				
   			skipsNode = getSkipsNode(skips,virusName,isVaccinated);



   			//if we have a citizen with this id in the linked list
   			if((linkedListSearch(list,citizenRec->id) == 1)) {

   				listNode *node = getNodeById(list,citizenRec->id);
   				skipListNode *skipNode =  skipListSearch(skipsNode->ls,id);

   				//if this id dont exist in this skipList
   				if(skipNode == NULL){

   					skipListInsert(skipsNode->ls,citizenRec->id,node,dateListNode);
   						
   				}

   				citizenRecordDelete(citizenRec);

   			}else{
   				linkedListInsertAtFront(list,citizenRec);
   			}

   			listNode *node = getNodeById(list,citizenRec->id);
   		
   			skipListInsert(skipsNode->ls,citizenRec->id,node,dateListNode);
   		}


	}

}



void vaccinateNow(linkedList *list,stringLinkedList *countryList,virusList *virusList,bloomList *bloomList,
				  int bloomSize,skipsList *skips,dateList *dateList,int id,char  *firstName,char *lastName,
				  char *country,char age, char *virusName,char* isVaccinated,Date *dateVaccinated)
{
	
	citizenRecord *citizenRec  = NULL;
	bloomFilter *bf            = NULL;
	skipList *ls               = NULL;
	dateListNode *dateListNode = NULL;
	skipsNode *skipsNode 	   = NULL;

	//get the skipNode
	skipsNode = getSkipsNode(skips,virusName,isVaccinated);

	//check if this skipsNode exist
	if (skipsNode != NULL){
		skipListNode *skipListNode = skipListSearch(skipsNode->ls,id);
		//check if the id is in the skipList of this virus
		if (skipListNode != NULL){
			printf("ERROR: CITIZEN %d ALREADY VACCINATED ON %d-%d-%d \n"
					,skipListNode->id,skipListNode->date->dateVaccinated->day,
					skipListNode->date->dateVaccinated->month,skipListNode->date->dateVaccinated->year );
		}else{
			//get the bloomFilter with the given virusName and Insert the id
			bloomNode *bloomNode = getBloomNodeByName(bloomList,virusName);
   			bloomFilterAdd(bloomNode->bf,id);

   			//get the dateListNode and linkeklist node
   			listNode *node = getNodeById(list,id);
   			if(dateListSearch(dateList,dateVaccinated) != 1){
				dateListInsert(dateList,dateVaccinated);
				dateListNode = getDateNode(dateList,dateVaccinated);
			}else{
				dateListNode = getDateNode(dateList,dateVaccinated);
			}
			//insert the citizen id in the skipList
   			skipListInsert(skipsNode->ls,id,node,dateListNode);

   			//search if the id is in the nonVaccinated skiplist of this virus and remove it
   			skipsNode = getSkipsNode(skips,virusName,"NO");
   			if (skipsNode != NULL){
				skipListNode = skipListSearch(skipsNode->ls,id);
				if (skipListNode != NULL){
					//Delete this id from the skipList
					skipListDeleteNode(skipsNode->ls,skipListNode);
				}
			}
		}
	}
}

	









void exitCommand(bloomList *bloomList,skipsList *skips,linkedList *list,stringLinkedList *countryList
				 ,virusList *virusList,dateList *dateList)
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


