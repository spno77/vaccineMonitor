#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "skipList.h"
#include "linkedList.h"

double Log2(int number)  
{  
    // log(n)/log(2) is log2.  
    return log(number) / log( 2 );  
} 


skipList *skipListCreate(int elemNumber)
{
	skipList *newSkipList = malloc(sizeof(skipList));

	if(newSkipList == NULL){
		perror("Malloc Failure !");
	}

	newSkipList->header = NULL;
	newSkipList->maxHeight = (int) Log2(elemNumber);
	newSkipList->level = 0;

	return newSkipList;
}


skipListNode *skipListNodeCreate(listNode *node,skipList *list)
{
	skipListNode *newNode = malloc(sizeof(skipListNode));

	if(newNode == NULL){
		perror("Malloc Failure !");
	}

	newNode->id = malloc(sizeof(char) * strlen(node->citizenRec->id));
	strcpy(newNode->id,node->citizenRec->id);
	
	newNode->node = node;

	newNode->forward = malloc(sizeof(skipListNode *) * (list->level + 1));
	if(newNode->forward == NULL){
		perror("Malloc Failure !");
	}

	return newNode;
}