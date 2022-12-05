
#include "LinkedList.h"

int front(List* list) {
	assert(list->head != NULL);
	if (list->head) {
		return list->head->data;
	}
	return 0;
}

int back(List* list) {
	assert(list->tail != NULL);
	if (list->tail) {
		return list->tail->data;
	}
	return 0;
}

Node* begin(List* list) {
	return list->head;
}

Node* end(List* list) {
	return list->tail;
}

Node* push_back(List* list, int data) {
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
	list->size += 1;
	return temp;
}

Node* push_front(List* list, int data) {
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
	list->size += 1;
	return temp;
}

Node* insert(List* list, Node* pos, int data) {
	if (pos) {
		Node* temp = (Node*)calloc(1, sizeof(Node));
		temp->data = data;
		if (pos->prev) {
			pos->prev->next = temp;
			temp->prev = pos->prev;
		}
		else {
			list->head = temp;
		}
		pos->prev = temp;
		temp->next = pos;
		list->size += 1;
		return pos;
	}
	return push_back(list, data);
}

void pop_back(List* list) {
	if (list->tail) {
		Node* temp = list->tail->prev;
		free(list->tail);
		list->tail = temp;
		list->size -= 1;
	}
}

void pop_front(List* list) {
	if (list->head) {
		Node* temp = list->head->next;
		free(list->head);
		list->head = temp;
		list->size -= 1;
	}
}

Node* erase(List* list, Node* pos) {
	if (pos) {
		Node* rtn = pos->next;
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
		list->size -= 1;
		return rtn;
	}
	return NULL;
}

int size(List* list) {
	return list->size;
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
	list->size = 0;
}

void swapList(List* A, List* B) {
	List temp = { 0 };
	temp = *A;
	*A = *B;
	*B = temp;
}

//int main() {
//	List list = { 0 };
//	int n;
//	scanf("%d", &n);
//	for (int i = 0; i < n; i++) {
//		insert(&list, i%2?list.head:list.tail, i);
//	}
//	printList(&list);
//	clearList(&list);
//	printf("%d\n", size(&list));
//	return 0;
//}