#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

typedef struct listNode listNode;
typedef struct linkedList linkedList;
typedef struct stringLinkedList stringLinkedList;
typedef struct stringListNode stringListNode;

typedef struct skipListNode{
	int id;	
	listNode *node;
	struct skipListNode **forward;
} skipListNode;


typedef struct skipList {
	skipListNode *header;
	int maxHeight; 		  // maximum height(number of levels)
	int level; 			  // the current number of levels in the skip list 
	stringListNode *virusName;
	char *isVaccinated;
} skipList;


int levelNumber(int maxHeight);

skipList *skipListCreate(int elemNumber,stringListNode *virusName,char *isVaccinated);

skipListNode *skipListNodeCreate(listNode *node,int level);

void skipListPrint(skipList *list);

void skipListInsert(skipList *list,int key,listNode *node);

skipListNode *createHeaderNode(int level);

listNode *getLinkedListNodePtr(skipListNode *skipListNode);

skipListNode* skipListSearch(skipList *list,int key);

void skipListDeleteNode(skipList *list,skipListNode *skipListNode);

void skipListDelete(skipList *list);

void skipListFree(skipList **list);

void skipListNodeFree(skipListNode *node);



//////////////////////////////////////////////////////////

typedef struct skipsNode{
	skipList *ls;
	struct skipsNode *next;
	struct skipsNode *prev;
}skipsNode;

typedef struct skipsList{
	struct skipsNode *head;
	struct skipsNode *tail;
	int size;
}skipsList;


skipsList *skipsListCreate(void);

skipsNode *skipsNodeCreate(skipList *ls);

int isSkipsListEmpty(skipsList *list);

void skipsListInsert(skipsList *list,skipList *sl);

void skipsNodePrint(skipsNode *node);

void skipsListPrint(skipsList *list);

void skipsNodeDelete(skipsList *list, skipsNode *node);

void skipsListDelete(skipsList *list);

void skipsListFree(skipsList **list);

int skipsListSearch(skipsList *list,char *string,char *isVaccinated);

skipsNode *getSkipsNode(skipsList *list, char *virusName,char *isVaccinated);


#endif