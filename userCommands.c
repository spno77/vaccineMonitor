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

void userCommands(bloomList *bloomList,skipsList *skips,linkedList *list,stringLinkedList *countryList
				  ,virusList *virusList,dateList *dateList)
{
	char* command = NULL;
	char* commandName = NULL;
	char* line = NULL;

	size_t length = 0;

	printf("ENTER COMMAND: ");
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

				insertCitizenRecord(list,countryList,virusList,bloomList,1000,skips,dateList,
									id,firstName,lastName,country,age,virusName,isVaccinated,dateVaccinated);

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

				vaccinateNow(list,countryList,virusList,bloomList,1000,skips,dateList,
					     	 id,firstName,lastName,country,age,virusName,"YES",dateVaccinated);

			}
            else if (strcmp(commandName,"/populationStatus") == 0)
            {

            	char* arg[4]; char *str = "a";
            	int count = 0 ;
     			Date *date1;
     			Date *date2;

            	while(str != NULL){
            		
            		str = strtok(NULL, " ");
            		
            		if (str == NULL){
            			break;
            		}

            		arg[count] = malloc(strlen(str)+1);
					strcpy(arg[count],str);

            		printf("arg %d is: %s\n",count,arg[count]);
            		count++;
            	}

            	
            	if (count == 4){
            		
            		date1 = stringToDate(arg[2]);
            		date2 = stringToDate(arg[3]);

            		populationStatus(skips,arg[0],arg[1],date1,date2);

            	}else{
            		date1 = stringToDate(arg[1]);
            		date2 = stringToDate(arg[2]);

            		populationStatusByCountry(skips,countryList,arg[0],date1,date2);
            	}
            
            	for (int i = 0; i < count; i++)
            	{
            		free(arg[i]);
            	}

            	freeDate(date1);
            	freeDate(date2);
            }else if (strcmp(commandName,"/popStatusByAge") == 0)
            {
            	char* arg[4]; char *str = "a";
            	int count = 0 ;
     			Date *date1;
     			Date *date2;

            	while(str != NULL){
            		
            		str = strtok(NULL, " ");
            		
            		if (str == NULL){
            			break;
            		}

            		arg[count] = malloc(strlen(str)+1);
					strcpy(arg[count],str);

            		printf("arg %d is: %s\n",count,arg[count]);
            		count++;
            	}

            	if (count == 4){	
            		date1 = stringToDate(arg[2]);
            		date2 = stringToDate(arg[3]);
            		popStatusByAge(skips,arg[0],arg[1],date1,date2);
            	}else{

            		date1 = stringToDate(arg[1]);
            		date2 = stringToDate(arg[2]);

            		popStatusByAgeAndByCountry(skips,countryList,arg[0],date1,date2);
            	}

            	for (int i = 0; i < count; i++)
            	{
            		free(arg[i]);
            	}

            	freeDate(date1);
            	freeDate(date2);
            	
            }





            else{
            	printf("Command is unavailable\n");

            }
		}

		printf("ENTER COMMAND: ");
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

		if (skipsNode != NULL){
			skipListNode *skipListNode = skipListSearch(skipsNode->ls,id);

			if(skipListNode != NULL){
				printf("VACCINATED ON: ");
				printDate(skipListNode->date->dateVaccinated);
			}else{
				printf("NOT VACCINATED\n");
			}
		}
	}else{
		//point to the head of skips List
		skipsNode *current = skips->head;
		//traverse skipsNodes one by one
    	while(current != NULL) {
    		//check if this id is in the skipList of this skipsNode
    		skipListNode *skipListNode = skipListSearch(current->ls,id);
    		
    		if (skipListNode != NULL){
    			if(strcmp(current->ls->virusInfo->isVaccinated,"YES") == 0){
    				printf("%s %s ",current->ls->virusInfo->virusName,current->ls->virusInfo->isVaccinated );
    				printDate(skipListNode->date->dateVaccinated);
    			}else{
    				printf("%s %s\n",current->ls->virusInfo->virusName,current->ls->virusInfo->isVaccinated );
    			}
    		}
    		//go to the next node
        	current = current->next;
		}
	}
}


void populationStatus(skipsList *skips,char *country,char *virusName,Date *date1,Date *date2)
{
	if(date1 == NULL){
		if (date2 == NULL){
			printf("ERROR please provide the 2 date arguments\n");
			return;
		}
	}

	int count1 = 0;
	int count2 = 0;
	
	skipsNode *skipsNode = getSkipsNode(skips, virusName,"YES");

	if(skipsNode != NULL){

		skipListNode *current = skipsNode->ls->header->forward[0];

		while(current != NULL){

			if(compareDates(current->date->dateVaccinated,date1) == 1){
				if(compareDates(date2,current->date->dateVaccinated) == 1){

					if( strcmp(current->node->citizenRec->country->string,country) == 0){

						count1++;
					}

				}
			}	


			current = current->forward[0];
		}

	}

		
	skipsNode  = getSkipsNode(skips, virusName,"NO");

	if(skipsNode != NULL){

		skipListNode *current = skipsNode->ls->header->forward[0];

		while(current != NULL){

			
			if( strcmp(current->node->citizenRec->country->string,country) == 0){

				count2++;
			}

			current = current->forward[0];
		}
	}

	float vacPer = ( (float)count1 / (count1 + count2) ) * 100; 

	printf("%s %d %.2f%%\n",country,count1,vacPer);

}

void populationStatusByCountry(skipsList *skips,stringLinkedList *countryList,char *virusName,
								Date *date1,Date *date2)
{

	stringListNode *currentCountry = countryList->head;

	while(currentCountry != NULL){

		int count1 = 0;
		int count2 = 0;
	
		skipsNode *skipsNode = getSkipsNode(skips, virusName,"YES");

		if(skipsNode != NULL){

			skipListNode *current = skipsNode->ls->header->forward[0];

			while(current != NULL){

				if(compareDates(current->date->dateVaccinated,date1) == 1){
					if(compareDates(date2,current->date->dateVaccinated) == 1){

						if( strcmp(current->node->citizenRec->country->string,currentCountry->string) == 0){

							count1++;
						}

					}
				}	

				current = current->forward[0];
			}
		}
		skipsNode  = getSkipsNode(skips, virusName,"NO");
		if(skipsNode != NULL){

			skipListNode *current = skipsNode->ls->header->forward[0];

			while(current != NULL){

			
				if( strcmp(current->node->citizenRec->country->string,currentCountry->string) == 0){

					count2++;
				}

				current = current->forward[0];
			}

		}


		float vacPer = ( (float)count1 / (count1 + count2) ) * 100;

		if ((count1 + count2) == 0 ){
		 	vacPer = 0;
		} 

		printf("%s %d %.2f%%\n",currentCountry->string,count1,vacPer);


		currentCountry = currentCountry->next;
	}
}


void popStatusByAge(skipsList *skips,char *country,char *virusName,Date *date1,Date *date2)
{
	if(date1 == NULL){
		if (date2 == NULL){
			printf("ERROR please provide the 2 date arguments\n");
			return;
		}
	}

	int countAge1 = 0; // count the numbet of citizens between the ages 0-20
	int countAge2 = 0; // count the numbet of citizens between the ages 20-40
	int countAge3 = 0; // count the numbet of citizens between the ages 40-60
	int countAge4 = 0; // count the numbet of citizens between the ages 60+

	int count2 = 0;    // count the number of people in the non Vaccinated skiplist of this virus
	
	skipsNode *skipsNode = getSkipsNode(skips, virusName,"YES");
	if(skipsNode != NULL){
		skipListNode *current = skipsNode->ls->header->forward[0];
		while(current != NULL){

			if(compareDates(current->date->dateVaccinated,date1) == 1){
				if(compareDates(date2,current->date->dateVaccinated) == 1){

					if( strcmp(current->node->citizenRec->country->string,country) == 0){
						if ( (current->node->citizenRec->age > 0) && (current->node->citizenRec->age < 20)){
							countAge1 ++;
						}else if ((current->node->citizenRec->age > 20) && (current->node->citizenRec->age < 40)){
							countAge2 ++;
						}else if ((current->node->citizenRec->age > 40) && (current->node->citizenRec->age < 60)){
							countAge3 ++;
						}else{
							countAge4 ++;
						}
					}
				}
			}	

			current = current->forward[0];
		}
	}

	skipsNode  = getSkipsNode(skips, virusName,"NO");
	if(skipsNode != NULL){

		skipListNode *current = skipsNode->ls->header->forward[0];
		while(current != NULL){
			if( strcmp(current->node->citizenRec->country->string,country) == 0){
				count2++;
			}
			current = current->forward[0];
		}
	}

	int countAll = countAge1 + countAge2 + countAge3 + countAge4;

	float vacPer1 = ( (float)countAge1 / (countAll + count2) ) * 100;
	if ((countAll + count2) == 0 ){
		vacPer1 = 0;
	} 

	float vacPer2 = ( (float)countAge2 / (countAll + count2) ) * 100;
	if ((countAll + count2) == 0 ){
		vacPer2 = 0;
	}

	float vacPer3 = ( (float)countAge3 / (countAll + count2) ) * 100;
	if ((countAll + count2) == 0 ){
		vacPer3 = 0;
	}

	float vacPer4 = ( (float)countAge4 / (countAll + count2) ) * 100;
	if ((countAll + count2) == 0 ){
		vacPer4 = 0;
	}  

	printf("%s\n",country );
	printf("0-20  %d %.2f%%\n",countAge1,vacPer1);
	printf("20-40 %d %.2f%%\n",countAge2,vacPer2);
	printf("40-60 %d %.2f%%\n",countAge3,vacPer3);
	printf("60+   %d %.2f%%\n",countAge4,vacPer4);
}


void popStatusByAgeAndByCountry(skipsList *skips,stringLinkedList *countryList,char *virusName,
								Date *date1,Date *date2)
{

	stringListNode *currentCountry = countryList->head;

	while(currentCountry != NULL){

		int countAge1 = 0; // count the numbet of citizens between the ages 0-20
		int countAge2 = 0; // count the numbet of citizens between the ages 20-40
		int countAge3 = 0; // count the numbet of citizens between the ages 40-60
		int countAge4 = 0; // count the numbet of citizens between the ages 60+

		int count2 = 0;    // count the number of people in the non Vaccinated skiplist of this virus
	
		skipsNode *skipsNode = getSkipsNode(skips, virusName,"YES");
		if(skipsNode != NULL){
			skipListNode *current = skipsNode->ls->header->forward[0];
			while(current != NULL){

				if(compareDates(current->date->dateVaccinated,date1) == 1){
					if(compareDates(date2,current->date->dateVaccinated) == 1){

						if( strcmp(current->node->citizenRec->country->string,currentCountry->string) == 0){
							if ( (current->node->citizenRec->age > 0) && (current->node->citizenRec->age < 20)){
								countAge1 ++;
							}else if ((current->node->citizenRec->age > 20) && (current->node->citizenRec->age < 40)){
								countAge2 ++;
							}else if ((current->node->citizenRec->age > 40) && (current->node->citizenRec->age < 60)){
								countAge3 ++;
							}else{
								countAge4 ++;
							}
						}
					}
				}	

				current = current->forward[0];
			}
		}

		skipsNode  = getSkipsNode(skips, virusName,"NO");
		if(skipsNode != NULL){

			skipListNode *current = skipsNode->ls->header->forward[0];
			while(current != NULL){
				if( strcmp(current->node->citizenRec->country->string,currentCountry->string) == 0){
					count2++;
				}
				current = current->forward[0];
			}
		}

		int countAll = countAge1 + countAge2 + countAge3 + countAge4;

		float vacPer1 = ( (float)countAge1 / (countAll + count2) ) * 100;
		if ((countAll + count2) == 0 ){
		vacPer1 = 0;
		} 

		float vacPer2 = ( (float)countAge2 / (countAll + count2) ) * 100;
		if ((countAll + count2) == 0 ){
			vacPer2 = 0;
		}

		float vacPer3 = ( (float)countAge3 / (countAll + count2) ) * 100;
		if ((countAll + count2) == 0 ){
			vacPer3 = 0;
		}

		float vacPer4 = ( (float)countAge4 / (countAll + count2) ) * 100;
		if ((countAll + count2) == 0 ){
			vacPer4 = 0;
		}	  

		printf("%s\n",currentCountry->string );
		printf("0-20  %d %.2f%%\n",countAge1,vacPer1);
		printf("20-40 %d %.2f%%\n",countAge2,vacPer2);
		printf("40-60 %d %.2f%%\n",countAge3,vacPer3);
		printf("60+   %d %.2f%%\n",countAge4,vacPer4);

		currentCountry = currentCountry->next;
	}
}


/*
	Print all nonVaccinated persons in the skipLists.Will print citizens that have a record
	in the non Vaccinated skip lists.
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


