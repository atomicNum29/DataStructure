#ifndef __LinkedList_h__
#define __LinkedList_h__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _NODE Node;
struct _NODE {
	int data;
	Node* prev;
	Node* next;
};

typedef struct _LIST List;
struct _LIST {
	Node* head;
	Node* tail;
	int size;
};

int front(List* list);
int back(List* list);
Node* begin(List* list);
Node* end(List* list);
Node* push_back(List* list, int data);
Node* push_front(List* list, int data);
Node* insert(List* list, Node* pos, int data);
void pop_back(List* list);
void pop_front(List* list);
Node* erase(List* list, Node* pos);
int size(List* list);
void printList(List* list);
void clearList(List* list);
void swapList(List* A, List* B);
void copyList(List* to, List* from);

#endif