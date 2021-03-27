#ifndef STRING_LIST_H_
#define STRING_LIST_H_


typedef struct Date Date;



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

int stringLinkedListSearch(stringLinkedList *list,char *string);

stringListNode *stringLinkedListNodeGet(stringLinkedList *list, char *id);

int stringLinkedListGetSize(stringLinkedList *list);


/////////////////////////////////////////////////////////////////////

typedef struct virusListNode{
	
	char *virusName;
	char *isVaccinated;

	struct virusListNode *next;
	struct virusListNode *prev;

}virusListNode;


typedef struct virusList{
	
	struct virusListNode *head;
	struct virusListNode *tail;
	
	int size;

}virusList;


virusList *virusListCreate(void);

virusListNode *virusListNodeCreate(char *virusName,char *isvaccinated);

int isVirusListEmpty(virusList *list);

void virusListInsert(virusList *list,char *virusName,char *isVaccinated);

void virusListNodePrint(virusListNode *node);

void virusListPrint(virusList *list);

void virusListNodeDelete(virusList *list, virusListNode *node);

void virusListDelete(virusList *list);

void virusListFree(virusList **list);

int virusListSearch(virusList *list,char *virusName,char *isVaccinated);

virusListNode *virusListNodeGet(virusList *list,char *virusName,char *isVaccinated);


/////////////////////////////////////////////////////////////////////////////


typedef struct dateListNode{
	
	Date *dateVaccinated;

	struct dateListNode *next;
	struct dateListNode *prev;

}dateListNode;


typedef struct dateList{
	
	struct dateListNode *head;
	struct dateListNode *tail;
	
	int size;

}dateList;


dateList *dateListCreate(void);

dateListNode *dateListNodeCreate(Date *dateVaccinated);

int isDateListEmpty(dateList *list);

void dateListInsert(dateList *list,Date *date);

void dateListNodePrint(dateListNode *node);

void dateListPrint(dateList *list);

void dateListNodeDelete(dateList *list, dateListNode *node);

void dateListDelete(dateList *list);

void dateListFree(dateList **list);

int dateListSearch(dateList *list,char *string);






#endif