#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE {
	int data;
	struct _NODE * next;
} Node;

Node* makeNode(int n) {
	Node* temp = NULL;
	while (!(temp = (Node*)malloc(sizeof(Node))));
	temp->data = n;
	temp->next = NULL;
	return temp;
}

Node* appendheadNode(Node* p, int n) {
	Node* temp = makeNode(n);
	temp->next = p;
	return temp;
}

void appendfirstNode(Node* p, int n) {
	Node* temp = makeNode(n);
	temp->next = p->next;
	p->next = temp;
	return;
}

void appendlastNode(Node* p, int n) {
	Node* temp = makeNode(n);
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = temp;
	return;
}

//�Ϲ����� ��ġ�� �߰��ϴ� �Լ�
// �Ϲ�ȭ �������� ����� �ʿ��ϴ�.
//int insertNode(Node* p, int at, int n) {
//	Node* temp = makeNode(n); 
//	if (at == 0) {
//
//	}
//	while ((p->next == NULL || at == 1)) {
//		p = p->next;
//		at--;
//	}
//	if (p->next == NULL && at != 1) {
//		return 0; //���̸� ��� �ε����� �߰��� ��û�� ���.
//	}
//	
//
//}

void printList(Node* p) {
	printf("[ ");
	while (p->next != NULL) {
		printf("%d, ", p->data);
		p = p->next;
	}
	printf("%d ]", p->data);
	return;
}

void deleteList(Node* p) {
	if (p == NULL) {
		return;
	}
	deleteList(p->next);
	free(p);
	return;
}


int main() {
	int n;
	scanf("%d", &n);
	Node* head = makeNode(n);
	for (int i = 0; i < n; i++) {
		int temp;
		scanf("%d", &temp);
		appendlastNode(head, temp);
	}
	printList(head);
	deleteList(head);
	return 0;
}