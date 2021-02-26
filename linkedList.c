#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "linkedList.h"

linkedList *linkedListCreate(void)
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


listNode *listNodeCreate(citizenRecord *citizenRec)
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
    listNode *newNode = listNodeCreate(citizenRec);

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
	if(node == NULL) return;
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

void listNodeDelete(linkedList *list, listNode *node)
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

    deleteCitizenRecord(node->citizenRec);
    free(node);
    node = NULL;
}

void linkedListDelete(linkedList *list)
{
    listNode *current = list->head;
    listNode *next;

    while(current != NULL) {
        next = current->next;
        listNodeDelete(list, current);
        current = next;
    }
    
}


void linkedListFree(linkedList **list){
    linkedListDelete(*list);
    free(*list);
    *list = NULL;
}


//get the node by the given id
listNode *getNodeById(linkedList *list, char *id)
{
	listNode *current = list->head;

    while(current != NULL) {
        if(strcmp(current->citizenRec->id,id) == 0) {
            return current;
        }

        current = current->next;
    }

    return NULL;

}
