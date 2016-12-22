#include <stdlib.h>
#include <stdio.h>

#include "linkedList.h"

LinkedList * createList(void * data, LinkedList * next)
{
	LinkedList *new = malloc(sizeof(LinkedList));
	new->data = data;
	new->next = next;
	return new;
}

void freeList(LinkedList *list)
{
	LinkedList *prev = list;
	LinkedList *next;

	while (prev != NULL)
	{
		next = prev->next;
		free(prev);
		prev = next;
	}
}

// Add item to the end of a linked list
void listAppend(LinkedList *list, void *item)
{
	if (list == NULL)
	{
		printf("Error: cannot append to non-existant list\n");
		exit(EXIT_FAILURE);
	}

	// Traverse list
	while (list->next != NULL)
	{
		list = list->next;
	}

	// Add to list
	list->next = createList(item, NULL);
}

// Push something to the beginning of the list
LinkedList * listPush(LinkedList *orig, void *item)
{
	LinkedList *result = createList(item, orig);
	return result;
}

// Concatinate two lists
LinkedList * listConcat(LinkedList *list1, LinkedList *list2)
{
	if (list1 == NULL)
	{
		printf("listConcat: Error: cannot append to non-existant list\n");
		exit(EXIT_FAILURE);
	}

	// Start with list1
	LinkedList *result = list1;	

	// Traverse list1
	while (result->next != NULL)
	{
		result = result->next;
	}

	// Add list2 to the end
	result->next = list2;

	return result;
}
