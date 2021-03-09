#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

typedef struct listNode listNode;
typedef struct linkedList linkedList;

typedef struct skipListNode{
	int id;	
	listNode *node;
	struct skipListNode **forward;
} skipListNode;


typedef struct skipList {
	skipListNode *header;
	int maxHeight; 		  // maximum height(number of levels)
	int level; 			  // the current number of levels in the skip list 
} skipList;


int levelNumber(int maxHeight);

skipList *skipListCreate(int elemNumber);

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


#endif