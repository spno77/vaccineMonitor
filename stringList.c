#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stringList.h"

#include "utils.h"

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

//////////////////////////////////////////////////////////////////////////////

virusList *virusListCreate(void)
{
    virusList *newList = malloc(sizeof(virusList));

    if(newList == NULL){
        perror("Malloc Failure !");
    }

    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;

    return newList;
}


virusListNode *virusListNodeCreate(char *virusName,char *isVaccinated)
{
    virusListNode *newNode = malloc(sizeof(virusListNode));

    if(newNode == NULL){
        perror("Malloc Failure !");
    }

    newNode->virusName = malloc(strlen(virusName)+1);
    strcpy(newNode->virusName,virusName);

    newNode->isVaccinated = malloc(strlen(isVaccinated)+1);
    strcpy(newNode->isVaccinated,isVaccinated);


    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

int isVirusListEmpty(virusList *list)
{
    if(list->size == 0){
        return 1;
    }else{
        return 0;
    }
}

void virusListInsert(virusList *list,char *virusName,char *isVaccinated)
{    
    virusListNode *newNode = virusListNodeCreate(virusName,isVaccinated);

    if(newNode != NULL) {

        if(isVirusListEmpty(list)) {
            list->head = list->tail = newNode;
        }else{
            list->head->prev = newNode;
            newNode->next = list->head;
            list->head = newNode;
        }

        list->size += 1;
    }
}

void virusListNodePrint(virusListNode *node)
{ 
    if(node == NULL) return;

    printf("%s\n" , node->virusName);
    printf("%s\n" , node->isVaccinated);
}


void virusListPrint(virusList *list)
{
    virusListNode *node = list->head;

    while(node != NULL){
        virusListNodePrint(node);
        node = node->next;
    }

    printf("NULL\n");
}

void virusListNodeDelete(virusList *list, virusListNode *node)
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

    free(node->virusName);
    free(node->isVaccinated);

    free(node);
    node = NULL;
}

void virusListDelete(virusList *list)
{
    virusListNode *current = list->head;
    virusListNode *next;

    while(current != NULL) {
        next = current->next;
        virusListNodeDelete(list, current);
        current = next;
    }
    
}


void virusListFree(virusList **list)
{
    virusListDelete(*list);
    free(*list);
    *list = NULL;
}

int virusListSearch(virusList *list,char *virusName,char *isVaccinated)
{
    virusListNode *current = list->head;

    while(current != NULL) {
        if (strcmp(current->virusName,virusName) == 0){
            if (strcmp(current->isVaccinated,isVaccinated) == 0){
                return 1;
            }
        }
        
        current = current->next;
    }
}


virusListNode *virusListNodeGet(virusList *list,char *virusName,char *isVaccinated)
{
    virusListNode *current = list->head;

    while(current != NULL) {
         if (strcmp(current->virusName,virusName) == 0){
            if (strcmp(current->isVaccinated,isVaccinated) == 0){
                return current;
            }
        }

        current = current->next;
    }

    return NULL;

}

int virusListGetSize(virusList *list)
{
    if(list != NULL){
        return list->size;
    }
}

//////////////////////////////////////////////////////////////////////////////



dateList *dateListCreate(void)
{
    dateList *newList = malloc(sizeof(dateList));

    if(newList == NULL){
        perror("Malloc Failure !");
    }

    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;

    return newList;
}


dateListNode *dateListNodeCreate(Date *date)
{
    dateListNode *newNode = malloc(sizeof(dateListNode));

    if(newNode == NULL){
        perror("Malloc Failure !");
    }

    newNode->dateVaccinated = date;

    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

int isDateListEmpty(dateList *list)
{
    if(list->size == 0){
        return 1;
    }else{
        return 0;
    }
}

void dateListInsert(dateList *list,Date *date)
{    
    dateListNode *newNode = dateListNodeCreate(date);

    if(newNode != NULL) {

        if(isDateListEmpty(list)) {
            list->head = list->tail = newNode;
        }else{
            list->head->prev = newNode;
            newNode->next = list->head;
            list->head = newNode;
        }

        list->size += 1;
    }
}

void dateListNodePrint(dateListNode *node)
{ 
    if(node == NULL) return;

    printDate(node->dateVaccinated);
}


void dateListPrint(dateList *list)
{
    dateListNode *node = list->head;

    while(node != NULL){
        dateListNodePrint(node);
        node = node->next;
    }

    printf("NULL\n");
}

void dateListNodeDelete(dateList *list, dateListNode *node)
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

    free(node->dateVaccinated);
    free(node);
    node = NULL;
}

void dateListDelete(dateList *list)
{
    dateListNode *current = list->head;
    dateListNode *next;

    while(current != NULL) {
        next = current->next;
        dateListNodeDelete(list, current);
        current = next;
    }
    
}


void dateListFree(dateList **list)
{
    dateListDelete(*list);
    free(*list);
    *list = NULL;
}
