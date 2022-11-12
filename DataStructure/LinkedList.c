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
	//���ǹ��� NULL�� �� �̸�, == NULL ������ �� �� �� �� ���̴�?
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
}

int main() {
	List list = { 0 };
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		push_back(&list, i);
	}
	printList(&list);
	deleteList(&list);
	return 0;
}