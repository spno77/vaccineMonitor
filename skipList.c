#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "skipList.h"
#include "linkedList.h"
#include "stringList.h"

/*
	Calculate the log2 of a given number
*/
double Log2(int number)  
{  
    // log(n)/log(2) is log2.  
    return log(number) / log( 2 );  
} 

/*
	Create a random level in the range 0-maxHeight
*/
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

/*
	Create and initialize a skipList
*/
skipList *skipListCreate(int elemNumber,virusListNode *virusInfo)
{
	skipList *newSkipList = malloc(sizeof(skipList));

	if(newSkipList == NULL){
		perror("Malloc Failure !");
	}

	int maxHeight = (int) Log2(elemNumber);
	
	newSkipList->maxHeight = maxHeight;
	newSkipList->header = createHeaderNode(maxHeight);
	newSkipList->level = 0;
	
	newSkipList->virusInfo = virusInfo;

	return newSkipList;
}


/*
	Create and initialize the Header Node of a skipList
*/
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

/*
	Create and initialize a Node of a skipList
*/
skipListNode *skipListNodeCreate(listNode *node,Date *date,int level)
{
	skipListNode *newNode = malloc(sizeof(skipListNode));

	if(newNode == NULL){
		perror("Malloc Failure !");
	}

	newNode->id = node->citizenRec->id;
	newNode->node = node;

	newNode->date = date;

	newNode->forward = malloc(sizeof(skipListNode *) * (level + 1));
	if(newNode->forward == NULL){
		perror("Malloc Failure !");
	}

	for (int i = 0; i < level + 1; i++ ){
		newNode->forward[i] = NULL;
	}

	return newNode;
}

/*
	Insert in the skipList a new node with the given key
*/
void skipListInsert(skipList *list,int key,listNode *node,Date *date)
{
	skipListNode *current = list->header;
	skipListNode **updateArray = malloc(sizeof(skipListNode *) * (list->maxHeight + 1));

	//initialize updateArray
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

		skipListNode *newNode = skipListNodeCreate(node,date,randLevel);
		for (int i = 0; i <= randLevel; i++){

			newNode->forward[i] = updateArray[i]->forward[i];
			updateArray[i]->forward[i] = newNode;	
		}
	}

	free(updateArray);
}

/*
	Print SkipList
*/
void skipListPrint(skipList *list)
{
	if(list == NULL) return;
	printf("Virus name: %s\n",list->virusInfo->virusName);
	printf("Vaccinated status: %s\n",list->virusInfo->isVaccinated);

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

/*
	Return the pointer linkedList node pointer or NULL
*/
listNode *getLinkedListNodePtr(skipListNode *skipListNode)
{
	if (skipListNode->node != NULL){
		return skipListNode->node;
	}
	return NULL;
}

/*
	Search if the key is in the skipList.Returns the node 
	or NULL if the key is not found.
*/
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

	if((current != NULL) && (current->id == key)){
		return current;
	}else{
		return NULL;
	}
}

/*
	Free a node from the skipList
*/
void skipListNodeFree(skipListNode *node)
{
	if(node != NULL){
		if(node->forward != NULL){
			free(node->forward);
		}
		free(node);
	}
}

/*
	Delete a Node from the skipList
*/
void skipListDeleteNode(skipList *list,skipListNode *node)
{
	skipListNode **updateArray = malloc(sizeof(skipListNode *) * (list->maxHeight + 1));

	//initialize updateArray
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
	skipListNodeFree(node);
}

/*
	Free all the nodes of a skipList
*/
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

/*
	Free the pointer to skipList
*/
void skipListFree(skipList **list)
{
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
        skipListDelete(current->ls);
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
  
    while(current != NULL) {
        if (strcmp(current->ls->virusInfo->virusName,string) == 0){
        	if(strcmp(current->ls->virusInfo->isVaccinated,isVaccinated) == 0){
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
        if(strcmp(current->ls->virusInfo->virusName,virusName) == 0){
        	if(strcmp(current->ls->virusInfo->isVaccinated,isVaccinated) == 0){
            	
            	return current;
        	}
    	}

        current = current->next;
    }

    return NULL;
}
