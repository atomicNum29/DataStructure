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

// 존재하지 않을 시 0 반환
int front(List* list) {
	if (list->head) {
		return list->head->data;
	}
	return 0;
}

int back(List* list) {
	if (list->head) {
		return list->tail->data;
	}
	return 0;
}

void push_back(List* list, int data) {
	Node* temp = NULL;
	temp = (Node*)calloc(1, sizeof(Node));
	temp->data = data;
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
	Node* temp = NULL;
	temp = (Node*)calloc(1, sizeof(Node));
	temp->data = data;
	if (list->head) {
		temp->next = list->head;
		list->head->prev = temp;
		list->head = temp;
	}
	else {
		list->head = list->tail = temp;
	}
}

int insert(List* list, Node* pos, int data) {
	Node* temp = calloc(1, sizeof(Node));
	temp->data = pos;
	if (pos->prev) {
		pos->prev->next = temp;
		temp->prev = pos->prev;
	}
	else {
		list->head = temp;
	}
	pos->prev = temp;
	temp->next = pos;
	return 1;
}

int pop_back(List* list) {
	if (list->head) {
		Node* temp = list->tail->prev;
		free(list->tail);
		list->tail = temp;
		return 1;
	}
	return 0;
}

int pop_front(List* list) {
	if (list->head) {
		Node* temp = list->head->next;
		free(list->head);
		list->head = temp;
		return 1;
	}
	return 0;
}

int erase(List* list, Node* pos) {
	if (pos) {
		if (pos->prev && pos->next) {
			pos->prev->next = pos->next;
			pos->next->prev = pos->prev;
		}
		else if (pos->prev) {
			list->tail = pos->prev;
			pos->prev->next = NULL;
		}
		else if (pos->next) {
			list->head = pos->next;
			pos->next->prev = NULL;
		}
		else {
			list->head = NULL;
			list->tail = NULL;
		}
		free(pos);
		return 1;
	}
	return 0;
}

int size(List* list) {
	int cnt = 0;
	Node* cursor = list->head;
	while (cursor) {
		cursor = cursor->next;
		cnt++;
	}
	return cnt;
}

void printList(List* list) {
	printf("[ ");
	Node* cursor = list->head;
	while (cursor) {
		printf("%d, ", cursor->data);
		cursor = cursor->next;
	}
	printf("]\n");
	return;
}

void clearList(List* list) {
	Node* cursor = list->head;
	Node* next;
	while (cursor) {
		next = cursor->next;
		free(cursor);
		cursor = next;
	}
	list->head = list->tail = NULL;
}

int main() {
	List list = { 0 };
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		push_back(&list, i);
	}
	printList(&list);
	printf("%d\n", size(&list));
	for (int i = 0; i < n; i++) {
		int cmd, pos, data;
		scanf("%d%d%d", &cmd, &pos, &data);
		if (cmd) {
			insert(&list, pos, data);
		}
		else {
			erase(&list, pos);
		}
		printList(&list);
	}
	clearList(&list);
	printf("%d\n", size(&list));
	return 0;
}