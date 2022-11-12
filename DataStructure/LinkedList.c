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

// iterator를 구현해야 할 것인가?
// 우선은 앞에서부터 pos번째에 추가하는 것으로 구현하겠다.
// 만약 pos가 적당한 범위를 벗어난다면, 실패한 것으로 판단하여 0을 반환한다.
// 그 외의 경우 삽입에 성공하면 1을 반환한다.
int insert(List* list, int pos, int data) {
	Node* temp = makeNode(data);
	if (pos) {
		Node* cursor = list->head;
		if (!cursor) return 0;
		for (; pos > 1; pos--) {
			cursor = cursor->next;
			if (!cursor) return 0;
		}
		if (cursor->next) {
			cursor->next->prev = temp;
			temp->next = cursor->next;
			temp->prev = cursor;
			cursor->next = temp;
		}
		else {
			cursor->next = temp;
			temp->prev = cursor;
			list->tail = temp;
		}
	}
	else {
		temp->next = list->head;
		list->head->prev = temp;
		list->head = temp;
	}
	return 1;
}

void pop_back(List* list) {
	Node* temp = list->tail->prev;
	free(list->tail);
	list->tail = temp;
}

void pop_front(List* list) {
	Node* temp = list->head->next;
	free(list->head);
	list->head = temp;
}

// insert와 마찬가지로, pos번째 노드를 삭제
// 성공 시 1, 실패 시 0 반환
int erase(List* list, int pos) {
	if (pos) {
		Node* cursor = list->head;
		if (!cursor) return 0;
		for (; pos > 0; pos--) {
			cursor = cursor->next;
			if (!cursor) return 0;
		}
		if (cursor->next) {	
			cursor->prev->next = cursor->next;
			cursor->next->prev = cursor->prev;
			free(cursor);
		}
		else {
			cursor->prev->next = NULL;
			list->tail = NULL;
			free(cursor);
		}
	}
	else {
		if (list->head) {
			Node* temp = list->head->next;
			free(list->head);
			list->head = temp;
		}
	}
	return 1;
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

void deleteList(List* list) {
	Node* cursor = list->head;
	Node* next = cursor->next;
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
	deleteList(&list);
	printf("%d\n", size(&list));
	return 0;
}