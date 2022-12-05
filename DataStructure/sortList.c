#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "LinkedList.h"

void selectionSort(List* list);

int main() {
	List list = { 0 };
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int temp;
		scanf("%d", &temp);
		push_back(&list, temp);
	}

	printList(&list);

	selectionSort(&list);
	printList(&list);

	clearList(&list);

	return 0;
}

void selectionSort(List* list) {
	Node* pos, * next;
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