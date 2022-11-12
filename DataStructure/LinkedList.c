#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

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
};

Node* makeNode(int data) {
	Node* temp = NULL;
	while (!(temp = (Node*)calloc(1, sizeof(Node))));
	temp->data = data;
	return temp;
}

void push_back(List* list, int data) {
	Node* temp = makeNode(data);
	//조건문이 NULL일 때 이면, == NULL 연산을 한 번 더 할 것이다?
	if (list->head) {
		temp->prev = list->tail;
		list->tail->next = temp;
		list->tail = temp;
	}
	else {
		list->head = list->tail = temp;
	}
}

void push_front(List* list, int data) {
	Node* temp = makeNode(data);
	if (list->head) {
		temp->next = list->head;
		list->head->prev = temp;
		list->head = temp;
	}
	else {
		list->head = list->tail = temp;
	}
}

int size(List* list) {
	int cnt = 0;
	Node* pos = list->head;
	while (pos) {
		pos = pos->next;
		cnt++;
	}
	return cnt;
}

void printList(List* list) {
	printf("[ ");
	Node* pos = list->head;
	while (pos) {
		printf("%d, ", pos->data);
		pos = pos->next;
	}
	printf("]\n");
	return;
}

void deleteList(List* list) {
	Node* pos = NULL;
	if (list->head) {
		for (pos = list->head; pos->next != NULL; pos = pos->next) {
			free(pos->prev);
		}
		free(pos);
	}
	list->head = list->tail = NULL;
}

int main() {
	List list = { 0 };
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		if (i % 2)
			push_back(&list, i);
		else
			push_front(&list, i);
	}
	printList(&list);
	printf("%d\n", size(&list));
	deleteList(&list);
	printf("%d\n", size(&list));
	return 0;
}