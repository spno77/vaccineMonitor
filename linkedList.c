#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "linkedList.h"

linkedList *createLinkedList(void)
{
	linkedList *newList = malloc(sizeof(linkedList));

	if(newList == NULL){
		perror("Malloc Failure !");
	}

	newList->head = NULL;
	newList->tail = NULL;
	newList->size = 0;

	return newList;
}


listNode *createListNode(citizenRecord *citizenRec)
{
	listNode *newNode = malloc(sizeof(listNode));

	if(newNode == NULL){
		perror("Malloc Failure !");
	}

	newNode->citizenRec = citizenRec;
	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

int isLinkedListEmpty(linkedList *list)
{
    if(list->size == 0){
        return 1;
    }else{
        return 0;
    }
}

void linkedListInsertAtFront(linkedList *list,citizenRecord *citizenRec)
{    
    listNode *newNode = createListNode(citizenRec);

    if(newNode != NULL) {

        if(isLinkedListEmpty(list)) {
            list->head = list->tail = newNode;
        }else{
            list->head->prev = newNode;
            newNode->next = list->head;
            list->head = newNode;
        }

        list->size += 1;
    }
}

void listNodePrint(listNode *node)
{
	 printCitizenRecord(node->citizenRec);
}

void linkedListPrint(linkedList *list)
{
	listNode *node = list->head;

	while(node != NULL){
		listNodePrint(node);
		node = node->next;
	}

	printf("NULL\n");

}