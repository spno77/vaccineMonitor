#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "citizen.h"

typedef struct listNode{
	citizenRecord *citizenRec;
	struct listNode *next;
	struct listNode *prev;
}listNode;

typedef struct linkedList{
	struct listNode *head;
	struct listNode *tail;
	int size;
}linkedList;

linkedList *linkedListCreate(void);

listNode *listNodeCreate(citizenRecord *citizenRec);

int isLinkedListEmpty(linkedList *list);

void linkedListInsertAtFront(linkedList *list,citizenRecord *citizenRec);

void listNodePrint(listNode *node);

void linkedListPrint(linkedList *list);

void listNodeDelete(linkedList *list, listNode *node);

void linkedListDelete(linkedList *list);

void linkedListFree(linkedList **list);

listNode *getNodeById(linkedList *list, int id);

int linkedListSearch(linkedList *list,int id);

int linkedListGetSize(linkedList *list);

#endif