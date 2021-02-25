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


linkedList *createLinkedList(void);

listNode *createListNode(citizenRecord *citizenRec);

int isLinkedListEmpty(linkedList *list);

void linkedListInsertAtFront(linkedList *list,citizenRecord *citizenRec);

void listNodePrint(listNode *node);

void linkedListPrint(linkedList *list);


#endif