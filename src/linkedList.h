#ifndef CCHESS_LINKED_LIST
#define CCHESS_LINKED_LIST

// Create a linked list type
typedef struct LinkedList LinkedList;

// Generic structure for a linked list
struct LinkedList {
	// Generic pointer
	void *data;
	LinkedList *next;
};

LinkedList * createList(void * data, LinkedList * next);
void freeList(LinkedList *list);
void listAppend(LinkedList *, void *);
LinkedList * listPush(LinkedList *, void *);
LinkedList * listConcat(LinkedList *, LinkedList *);

#endif
