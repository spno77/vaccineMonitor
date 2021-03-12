#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stringList.h"

stringLinkedList *stringLinkedListCreate(void)
{
	stringLinkedList *newList = malloc(sizeof(stringLinkedList));

	if(newList == NULL){
		perror("Malloc Failure !");
	}

	newList->head = NULL;
	newList->tail = NULL;
	newList->size = 0;

	return newList;
}


stringListNode *stringListNodeCreate(char *string)
{
	stringListNode *newNode = malloc(sizeof(stringListNode));

	if(newNode == NULL){
		perror("Malloc Failure !");
	}

	newNode->string = malloc(strlen(string)+1);
    strcpy(newNode->string,string);

	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

int isStringLinkedListEmpty(stringLinkedList *list)
{
    if(list->size == 0){
        return 1;
    }else{
        return 0;
    }
}

void stringLinkedListInsertAtFront(stringLinkedList *list,char *string)
{    
    stringListNode *newNode = stringListNodeCreate(string);

    if(newNode != NULL) {

        if(isStringLinkedListEmpty(list)) {
            list->head = list->tail = newNode;
        }else{
            list->head->prev = newNode;
            newNode->next = list->head;
            list->head = newNode;
        }

        list->size += 1;
    }
}

void stringListNodePrint(stringListNode *node)
{ 
	if(node == NULL) return;
	printf("%s\n" , node->string);
}


void stringLinkedListPrint(stringLinkedList *list)
{
	stringListNode *node = list->head;

	while(node != NULL){
		stringListNodePrint(node);
		node = node->next;
	}

	printf("NULL\n");
}

void stringListNodeDelete(stringLinkedList *list, stringListNode *node)
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

    free(node->string);
    free(node);
    node = NULL;
}

void stringLinkedListDelete(stringLinkedList *list)
{
    stringListNode *current = list->head;
    stringListNode *next;

    while(current != NULL) {
        next = current->next;
        stringListNodeDelete(list, current);
        current = next;
    }
    
}


void stringLinkedListFree(stringLinkedList **list)
{
    stringLinkedListDelete(*list);
    free(*list);
    *list = NULL;
}

int stringLinkedListSearch(stringLinkedList *list,char *string)
{
    stringListNode *current = list->head;

    while(current != NULL) {
        if (strcmp(current->string,string) == 0){
            return 1;
        }
        
        current = current->next;
    }
}


stringListNode *stringLinkedListNodeGet(stringLinkedList *list, char *id)
{
    stringListNode *current = list->head;

    while(current != NULL) {
        if(strcmp(current->string,id) == 0) {
            return current;
        }

        current = current->next;
    }

    return NULL;

}

int stringLinkedListGetSize(stringLinkedList *list)
{
    if(list != NULL){
        return list->size;
    }
}