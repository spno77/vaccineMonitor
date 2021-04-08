#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

typedef struct listNode listNode;
typedef struct linkedList linkedList;
typedef struct stringLinkedList stringLinkedList;
typedef struct stringListNode stringListNode;
typedef struct dateListNode dateListNode;
typedef struct virusListNode virusListNode;
typedef struct Date Date;

typedef struct skipListNode{
	int id;				//id of the citizen
	listNode *node;		//pointer to the listnode that contains citizen's other info
	dateListNode *date;	//pointer to the dateListNode that contains the date this citizen was vaccinated
	struct skipListNode **forward; 
} skipListNode;

typedef struct skipList {
	skipListNode *header; // pointer to header node
	int maxHeight; 		  // maximum height(number of levels)
	int level; 			  // the current number of levels in the skip list 
	virusListNode *virusInfo; 
} skipList;

int levelNumber(int maxHeight);

skipList *skipListCreate(int elemNumber,virusListNode *virusInfo);

skipListNode *skipListNodeCreate(listNode *node,dateListNode *date,int level);

void skipListPrint(skipList *list);

void skipListInsert(skipList *list,int key,listNode *node,dateListNode *date);

skipListNode *createHeaderNode(int level);

listNode *getLinkedListNodePtr(skipListNode *skipListNode);

skipListNode* skipListSearch(skipList *list,int key);

void skipListDeleteNode(skipList *list,skipListNode *skipListNode);

void skipListDelete(skipList *list);

void skipListFree(skipList **list);

void skipListNodeFree(skipListNode *node);

int skipListExists(skipList *list,int key);

/******************************************************************************************/
/*                               skipsList Functions                                      */
/******************************************************************************************/

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