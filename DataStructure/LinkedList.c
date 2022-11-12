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

int front(List* list) {
	return list->head->data;
}

int back(List* list) {
	return list->tail->data;
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

// iterator�� �����ؾ� �� ���ΰ�?
// �켱�� �տ������� pos��°�� �߰��ϴ� ������ �����ϰڴ�.
// ���� pos�� ������ ������ ����ٸ�, ������ ������ �Ǵ��Ͽ� 0�� ��ȯ�Ѵ�.
// �� ���� ��� ���Կ� �����ϸ� 1�� ��ȯ�Ѵ�.
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

// insert�� ����������, pos��° ��带 ����
// ���� �� 1, ���� �� 0 ��ȯ
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
	if (list->head == NULL) return;
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