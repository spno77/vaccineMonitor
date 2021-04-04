#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "utils.h"
#include "citizen.h"
#include "linkedList.h"
#include "stringList.h"
#include "bloomFilter.h"
#include "skipList.h"


/*
 	Trasforms a char* to Date data type.
 */
Date *stringToDate(char *dateStr)
{
	Date *date = malloc(sizeof(Date));

	if(dateStr == NULL){
		date->day	 = 0; 
		date->month  = 0;
		date->year   = 0;

		return date;
	}

	char *token = NULL;
	token = strtok(dateStr, "-");
	date->day = atoi(token);

	token = strtok(NULL, "-");
	date->month = atoi(token);

	token = strtok(NULL, "-");	
	date->year = atoi(token);

	return date;
}

void printDate(Date *date)
{
	printf("%d-",date->day);
	printf("%d-",date->month);
	printf("%d\n",date->year);
}


void insertIntoDateStructures(char *filename,linkedList *list,stringLinkedList *countryList,
					         virusList *virusList,bloomList *bloomList,int bloomSize,skipsList *skips,
					         dateList *dateList)
{

	Record *Rec               = NULL;
	citizenRecord *citizenRec = NULL;
	bloomFilter *bf           = NULL;
	skipList *ls              = NULL;

	FILE *fp;

	fp = fopen(filename,"r");
	if (fp == NULL){
		printf("Error opening file");
	}

	ssize_t nread;
   	size_t len = 0;
   	char *line = NULL;

   	int count = 0 ;
    while ((nread = getline(&line, &len, fp)) != -1){


    	int id 				  = atoi(strtok(line," "));
		char *firstName       = strtok(NULL, " ");
		char *lastName        = strtok(NULL, " ");
		char *country         = strtok(NULL, " ");
		char age              = (char)atoi(strtok(NULL, " "));
		char *virusName        = strtok(NULL, " ");
		char *isVaccinated    = strtok(NULL," \n");
		Date *dateVaccinated  = stringToDate(strtok(NULL, " "));

		//printf("%d ",id );
		//printf("%s ",firstName );
		//printf("%s ",lastName );
		//printf("%s ", country);
		//printf("%d ", age);
		//printf("%s ",isVaccinated );
		//printDate(dateVaccinated);

		dateListNode *dateListNode;


    	if(nread == -1){
    		return;
    	}
   			
   		//Rec = recordCreate(line);

   		if(isRecordValid2(id,isVaccinated,dateVaccinated) == 1){

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
				freeDate(dateVaccinated);
			}	


			virusListNode *virusNode = virusListNodeGet(virusList,virusName,isVaccinated);
			stringListNode *countryNode  = stringLinkedListNodeGet(countryList,country);
			//dateListNode *dateListNode = getDateNode(dateList,dateVaccinated);

		

		

   			citizenRec = citizenRecordCreate(id,firstName,lastName,age,countryNode,virusNode);

   			if(skipsListSearch(skips,citizenRec->virusInfo->virusName,citizenRec->virusInfo->isVaccinated) != 1){

   				//listNode *node = getNodeById(list,Rec->id);

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
   				
			
   				
   			skipsNode *skipsNode = getSkipsNode(skips,virusName,isVaccinated);

   	
   			//skipListNode *skipNode =  skipListSearch(skipsNode->ls,Rec->id);

   			//if we have a citizen with this id in the linked list
   			if((linkedListSearch(list,citizenRec->id) == 1)) {

   				//linkedListInsertAtFront(list,citizenRec);


   				listNode *node = getNodeById(list,citizenRec->id);

   				//skipListInsert(skipsNode->ls,citizenRec->id,node,Rec->dateVaccinated);

   				skipListNode *skipNode =  skipListSearch(skipsNode->ls,id);

   				//if this id dont exist in this skipList
   				if(skipNode == NULL){

   					skipListInsert(skipsNode->ls,citizenRec->id,node,dateListNode);
   						
   				}

   				//printf("ERROR IN RECORD %d\n",id);
   					
   				citizenRecordDelete(citizenRec);

   				//recordDelete(&Rec);

   				
   				//if(dateListSearch(dateList,dateVaccinated) == 1){
   				//	
   				//	printf("HAHAHAHAHAHAHAHAHA: ");
   				//	printDate(dateVaccinated);
   				//	//freeDate(dateVaccinated);
				//	//dateListNodeDelete(dateList,dateListNode);
			//	}


   				continue;

   			}else{
   				linkedListInsertAtFront(list,citizenRec);
   			}


   			//if(dateListSearch(dateList,dateVaccinated) == 1){
   				//	
   					//printf("HAHAHAHAHAHAHAHAHA: ");
   					//printDate(dateVaccinated);
   				//	//freeDate(dateVaccinated);
				//	//dateListNodeDelete(dateList,dateListNode);
				//}
	

   			listNode *node = getNodeById(list,citizenRec->id);
   			//dateListNode *dateListNode = getDateNode(dateList,Rec->isVaccinated);

   			skipListInsert(skipsNode->ls,citizenRec->id,node,dateListNode);

   		}
   		else{
   			freeDate(dateVaccinated);
   		}

   		//recordDelete(&Rec);
   		//freeDate(dateVaccinated);
   			
   	}

   	if (line != NULL){	
		free(line);
	}


   	fclose(fp);
}

/*

/*
 *	Read command line arguments
 */
void readArguments(int argc,char const *argv[],char **citizenRecordsFile,int *bloomSize)
{
    for (int i = 1; i < argc; i+=2){

        if(strcmp(argv[i],"-c") == 0){
            *citizenRecordsFile  = malloc(strlen(argv[i+1]) + 1);
            strcpy(*citizenRecordsFile,argv[i+1]);
        }else if(strcmp(argv[i],"-b") == 0){
            *bloomSize = atoi(argv[i+1]);
        }
    }
}

/*
 *	Free command line arguments memomry allocation
 */
void freeArguments(char **citizenRecordsFile)
{
	free(*citizenRecordsFile);
}

/*
 *	Checks for citizenRecord validity
 */

int isRecordValid(Record *Rec)
{
	if((strcmp(Rec->isVaccinated,"NO")==0) && (Rec->dateVaccinated->year != 0)){
		printf("ERROR IN RECORD %d\n",Rec->id);
		//recordDelete(Rec);
		return 0;
	}


	return 1;
}


int isRecordValid2(int id,char *isVaccinated,Date *date)
{
	if((strcmp(isVaccinated,"NO")==0) && (date->year != 0)){
		printf("ERROR IN RECORD %d\n",id);
		//recordDelete(Rec);
		return 0;
	}


	return 1;
}





/*
 *	Returns the number of records from the input file.
 */
int getNumberOfRecords(FILE *fp)
{

	size_t len = 0;
	char *line = NULL;
	ssize_t nread;
	unsigned int count = 0 ;

	while ((nread = getline(&line, &len, fp)) != -1){
		if(nread > 0){  
			count++;
		}
	}

	// It moves file pointer position to the beginning of the file.
	fseek(fp,0,SEEK_SET);

	if (line != NULL)
	{
		free(line);
	}

	return count;
} 


void freeDate(Date *date)
{
	//printDate(date);
	free(date);
}