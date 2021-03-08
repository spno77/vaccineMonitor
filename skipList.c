#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "skipList.h"
#include "linkedList.h"

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


skipList *skipListCreate(int elemNumber)
{
	printf("Elem number = %d\n",elemNumber );
	skipList *newSkipList = malloc(sizeof(skipList));

	if(newSkipList == NULL){
		perror("Malloc Failure !");
	}

	int maxHeight = 3 ;//(int) Log2(elemNumber);

	printf("maxHeight: %d\n",maxHeight );

	newSkipList->maxHeight = maxHeight;

	printf("AAAA: %d\n", newSkipList->maxHeight );

	newSkipList->header = createHeaderNode(maxHeight);
	newSkipList->level = 0;

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

	//int key = atoi(id);

	skipListNode *current = list->header;

	//skipListNode *updateArray[list->maxHeight+1];

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

		printf("Rand 1: %d\n",randLevel);

		if(randLevel > list->level){
			for (int i = list->level+1; i < randLevel+1; i++){
				updateArray[i] = list->header;
			}

			list->level = randLevel;
		}

		skipListNode *newNode = skipListNodeCreate(node,randLevel);

		printf("Rand 2: %d\n",randLevel);

		for (int i = 0; i <= randLevel; i++){


			newNode->forward[i] = updateArray[i]->forward[i];

		//assert(updateArray[i]->forward[i]);
			updateArray[i]->forward[i] = newNode;
	
		}

	}

}


void skipListPrint(skipList *list)
{
	for (int i = 0; i < list->level; i++){

		skipListNode *node = list->header->forward[i];
		printf("LEVEL: %d: ",i );

		while(node != NULL){
			printf("%d ",node->id);
			node = node->forward[i];
		}

		printf("\n");

	}

}