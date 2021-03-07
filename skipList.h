#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

typedef struct listNode listNode;
typedef struct linkedList linkedList;

typedef struct skipListNode{
	char* id;	
	listNode *node;
	struct skiplistNode **forward;
} skipListNode;


typedef struct skipList {
	skipListNode *header;
	int maxHeight; 		  // maximum height(number of levels)
	int level; 			  // the current number of levels in the skip list 
} skipList;



skipList *skipListCreate(int elemNumber);

skipListNode *skipListNodeCreate(listNode *node,skipList *list);






#endif