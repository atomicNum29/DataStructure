#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LinkedList.h"

void selectionSort(List* list);
void bubbleSort(List* list);
void quickSort(List* list, Node* left, Node* right);

int isSorted(List* list);
void test(int t);

int main() {
	int t;
	scanf("%d", &t);

	test(t);

	return 0;
}

void test(int t) {
	srand(time(NULL));
	while (t--) {

		List list = { 0 };
		List temp = { 0 };
		int n = 100;
		//scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			int temp = rand();
			push_back(&list, temp);
		}

		copyList(&temp, &list);
		selectionSort(&temp);
		printf("%-17s%d -> %d\n", "selectionSort: ", isSorted(&list), isSorted(&temp));
		if (!isSorted(&temp)) {
			printList(&list);
			printList(&temp);
		}

		copyList(&temp, &list);
		bubbleSort(&temp);
		printf("%-17s%d -> %d\n", "bubbleSort: ", isSorted(&list), isSorted(&temp));
		if (!isSorted(&temp)) {
			printList(&list);
			printList(&temp);
		}

		copyList(&temp, &list);
		quickSort(&temp, begin(&temp), end(&temp));
		printf("%-17s%d -> %d\n", "quickSort: ", isSorted(&list), isSorted(&temp));
		if (!isSorted(&temp)) {
			printList(&list);
			printList(&temp);
		}

		clearList(&temp);
		clearList(&list);
	}
}

int isSorted(List* list) {
	for (Node* i = begin(list); i; i = i->next) {
		if (i->next == NULL) {
			break;
		}
		if (i->data > i->next->data) {
			return 0;
		}
	}
	return 1;
}

void selectionSort(List* list) {
	Node* pos = NULL, * next = NULL;
	List tempList = { 0 };
	while ( size(list) ) {
		pos = begin(list);
		next = pos->next;
		while( next ) {
			if (pos->data > next->data) {
				pos = next;
			}
			next = next->next;
		}
		push_back(&tempList, pos->data);
		erase(list, pos);
	}
	swapList(list, &tempList);
	clearList(&tempList);
}

void bubbleSort(List* list) {
	Node* pos = NULL;
	int n = size(list);
	for (int i = 0; i < n; i++) {
		pos = begin(list);
		for (int j = 0; j < n - i - 1; j++) {
			if (pos->data > pos->next->data) {
				int temp = pos->next->data;
				pos->next->data = pos->data;
				pos->data = temp;
			}
			pos = pos->next;
		}
	}
}

// [left, right]
void quickSort(List* list, Node* left, Node* right) {
	if (!left)
		return;

	Node* temp = left->next;
	Node* nextLeft = left;
	Node* nextRight = right;
	Node* stop = right->next;

	while (temp != stop) {
		if (temp->data < left->data) {
			nextLeft = insert(list, nextLeft, temp->data);
		}
		else {
			nextRight = insert(list, nextRight->next, temp->data);
		}
		stop = right->next;
		temp = erase(list, temp);
	}

	if(left != nextLeft)
		quickSort(list, nextLeft, left->prev);
	if(right != nextRight)
		quickSort(list, left->next, nextRight);
}