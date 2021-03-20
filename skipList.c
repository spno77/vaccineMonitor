#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "skipList.h"
#include "linkedList.h"
#include "stringList.h"

double Log2(int number)  
{  
    // log(n)/log(2) is log2.  
    return log(number) / log( 2 );  
} 


int levelNumber(int maxHeight)
{
	int level = 0 ;
	int randNum; 
	
	for(int i = 0; i < maxHeight; i++){
		randNum = rand() % 2;
		if(randNum == 1){
			level++;
		}
	}

	return level;
}


skipList *skipListCreate(int elemNumber,stringListNode *virusName,char *isVaccinated)
{
	skipList *newSkipList = malloc(sizeof(skipList));

	if(newSkipList == NULL){
		perror("Malloc Failure !");
	}

	int maxHeight = (int) Log2(elemNumber);
	
	newSkipList->maxHeight = maxHeight;
	newSkipList->header = createHeaderNode(maxHeight);
	newSkipList->level = 0;
	newSkipList->virusName = virusName;

	newSkipList->isVaccinated = malloc(strlen(isVaccinated)+1);
	strcpy(newSkipList->isVaccinated,isVaccinated);

	return newSkipList;
}

skipListNode *createHeaderNode(int level)
{
	skipListNode *newNode = malloc(sizeof(skipListNode));

	if(newNode == NULL){
		perror("Malloc Failure !");
	}

	newNode->id   = -1;
	newNode->node = NULL;

	newNode->forward = malloc(sizeof(skipListNode *) * (level + 1));
	if(newNode->forward == NULL){
		perror("Malloc Failure !");
	}

	for (int i = 0; i < level + 1; i++ ){
		newNode->forward[i] = NULL;
	}

	return newNode;
}

skipListNode *skipListNodeCreate(listNode *node,int level)
{
	skipListNode *newNode = malloc(sizeof(skipListNode));

	if(newNode == NULL){
		perror("Malloc Failure !");
	}

	/*newNode->id = malloc(sizeof(char) * strlen(node->citizenRec->id) +1 );
	if(newNode == NULL){
		perror("Malloc Failure !");
	}
	strcpy(newNode->id,node->citizenRec->id);
	*/
	newNode->id = atoi(node->citizenRec->id);
	newNode->node = node;

	newNode->forward = malloc(sizeof(skipListNode *) * (level + 1));
	if(newNode->forward == NULL){
		perror("Malloc Failure !");
	}

	for (int i = 0; i < level + 1; i++ ){
		newNode->forward[i] = NULL;
	}

	return newNode;
}

void skipListInsert(skipList *list,int key,listNode *node)
{

	skipListNode *current = list->header;

	//skipListNode *updateArray[list->maxHeight+1];

	//dont forget to free it later
	skipListNode **updateArray = malloc(sizeof(skipListNode *) * (list->maxHeight + 1));

	for (int i = 0; i < list->maxHeight + 1; i++ ){
		updateArray[i] = NULL;
	}

	for (int i = list->level; i >= 0; i--){

		while(current->forward[i] != NULL && current->forward[i]->id < key ){
			current = current->forward[i];
		}

		updateArray[i] = current;
	}

	current = current->forward[0];

	if(current == NULL || current->id != key){
	
		int randLevel = levelNumber(list->maxHeight);
		if(randLevel > list->level){
			for (int i = list->level+1; i < randLevel+1; i++){
				updateArray[i] = list->header;
			}

			list->level = randLevel;
		}

		skipListNode *newNode = skipListNodeCreate(node,randLevel);
		for (int i = 0; i <= randLevel; i++){

			newNode->forward[i] = updateArray[i]->forward[i];
			updateArray[i]->forward[i] = newNode;	
		}
	}

	free(updateArray);
}


void skipListPrint(skipList *list)
{
	if(list == NULL) return;
	printf("Virus name: %s\n",list->virusName->string);
	printf("Vaccinated status: %s\n",list->isVaccinated );

	for (int i = 0; i < list->level; i++){

		skipListNode *node = list->header->forward[i];
		printf("LEVEL: %d: ",i );

		while(node != NULL){
			printf("%d ",node->id);
			node = node->forward[i];
		}

		printf("\n");
	}

	printf("--------------------\n");
}


listNode *getLinkedListNodePtr(skipListNode *skipListNode)
{
	return skipListNode->node;
}


skipListNode* skipListSearch(skipList *list,int key)
{
	skipListNode *current = list->header;

	for(int i = list->level; i >= 0; --i){
		while(current->forward[i] &&
				current->forward[i]->id < key){
			
			current = current->forward[i];
		}
	}

	current = current->forward[0];

	if(current->id == key){
		return current;
	}else{
		return NULL;
	}
}

void skipListNodeFree(skipListNode *node)
{
	if(node != NULL){
		if(node->forward != NULL){
			free(node->forward);
		}
		free(node);
	}
}


void skipListDeleteNode(skipList *list,skipListNode *node)
{
	skipListNode **updateArray = malloc(sizeof(skipListNode *) * (list->maxHeight + 1));

	for (int i = 0; i < list->maxHeight + 1; i++ ){
		updateArray[i] = NULL;
	}

	skipListNode *current = list->header;

	for(int i = list->level; i >= 0; i--){

		while(current->forward[i] != NULL &&
			current->forward[i]->id < node->id ){ 
			
			current = current->forward[i];
		}

		updateArray[i] = current;
	}

	current = current->forward[0];

	if (current->id == node->id && current != NULL){ 
		
		for (int i = 0; i <= list->level; i++){
			if (updateArray[i]->forward[i] != current){
				break;
			}
			updateArray[i]->forward[i] = current->forward[i];	
		}
	}	

	
	while(list->level > 0 && list->header->forward[list->level] == NULL){
		list->level = list->level - 1 ;
	}

	free(updateArray);

	//free(node->forward);
	skipListNodeFree(node);

	//node = NULL;
}


void skipListDelete(skipList *list)
{
	skipListNode *current = list->header;
	skipListNode *next = NULL;

	while(current != NULL){
		next = current->forward[0];
		skipListNodeFree(current);
		current = next;
	}
}


void skipListFree(skipList **list)
{
    //skipListDelete(*list);
    free((*list)->isVaccinated);
    free(*list);
    *list = NULL;
}



//////////////////////////////////////////////////////////


skipsList *skipsListCreate(void)
{
	skipsList *newList = malloc(sizeof(skipsList));

	if(newList == NULL){
		perror("Malloc Failure !");
	}

	newList->head = NULL;
	newList->tail = NULL;
	newList->size = 0;

	return newList;
}


skipsNode *skipsNodeCreate(skipList *ls)
{
	skipsNode *newNode = malloc(sizeof(skipsNode));

	if(newNode == NULL){
		perror("Malloc Failure !");
	}

	newNode->ls = ls;
	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

int isSkipsListEmpty(skipsList *list)
{
    if(list->size == 0){
        return 1;
    }else{
        return 0;
    }
}

void skipsListInsert(skipsList *list,skipList *ls)
{    
    skipsNode *newNode = skipsNodeCreate(ls);

    if(newNode != NULL) {

        if(isSkipsListEmpty(list)) {
            list->head = list->tail = newNode;
        }else{
            list->head->prev = newNode;
            newNode->next = list->head;
            list->head = newNode;
        }

        list->size += 1;
    }
}

void skipsNodePrint(skipsNode *node)
{ 
	if(node == NULL) return;
	skipListPrint(node->ls);
}


void skipsListPrint(skipsList *list)
{
	skipsNode *node = list->head;

	while(node != NULL){
		skipsNodePrint(node);
		node = node->next;
	}

	printf("NULL\n");
}

void skipsNodeDelete(skipsList *list, skipsNode *node)
{
    if(node->next != NULL) {
        node->next->prev = node->prev;
    }else{
        list->tail = node->prev;
    }

    if(node->prev != NULL) {
        node->prev->next = node->next;
    }else{
        list->head = node->next;
    }

    list->size -= 1;

   	skipListFree(&node->ls);
    free(node);
    node = NULL;
}

void skipsListDelete(skipsList *list)
{
    skipsNode *current = list->head;
    skipsNode *next;

    while(current != NULL) {
        next = current->next;
        skipsNodeDelete(list, current);
        current = next;
    }
}

void skipsListFree(skipsList **list)
{
    skipsListDelete(*list);
    free(*list);
    *list = NULL;
}


int skipsListSearch(skipsList *list,char *string,char *isVaccinated)
{
    skipsNode *current = list->head;

    //printf("string is : %s\n",string );
    //printf("%s-->len of isVaccinated: %ld\n",isVaccinated,strlen(isVaccinated));

    while(current != NULL) {
        if (strcmp(current->ls->virusName->string,string) == 0){
        	if(strcmp(current->ls->isVaccinated,isVaccinated) == 0){
            	return 1;
       	    }
        }
    	
        current = current->next;
    }
}


skipsNode *getSkipsNode(skipsList *list, char *virusName,char *isVaccinated)
{
	skipsNode *current = list->head;

    while(current != NULL) {
        if(strcmp(current->ls->virusName->string,virusName) == 0){
        	if(strcmp(current->ls->isVaccinated,isVaccinated) == 0){
            	
            	return current;
        	}
    	}

        current = current->next;
    }

    return NULL;
}