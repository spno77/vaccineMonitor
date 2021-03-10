#ifndef STRING_LIST_H_
#define STRING_LIST_H_

typedef struct stringListNode{
	char *string;
	struct stringListNode *next;
	struct stringListNode *prev;
}stringListNode;

typedef struct stringLinkedList{
	struct stringListNode *head;
	struct stringListNode *tail;
	int size;
}stringLinkedList;


stringLinkedList *stringLinkedListCreate(void);

stringListNode *stringListNodeCreate(char *string);

int isStringLinkedListEmpty(stringLinkedList *list);

void stringLinkedListInsertAtFront(stringLinkedList *list,char *string);

void stringListNodePrint(stringListNode *node);

void stringLinkedListPrint(stringLinkedList *list);

void stringListNodeDelete(stringLinkedList *list, stringListNode *node);

void stringLinkedListDelete(stringLinkedList *list);

void stringLinkedListFree(stringLinkedList **list);



#endif