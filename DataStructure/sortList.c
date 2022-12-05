#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "LinkedList.h"

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

	Node* pos, * next;
	List tempList = { 0 };
	for (int i = 0; i < n; i++) {
		pos = list.head;
		next = pos->next;
		for (int j = i + 1; j < n; j++) {
			if (pos->data > next->data) {
				pos = next;
			}
			next = next->next;
		}
		push_back(&tempList, pos->data);
		erase(&list, pos);
	}
	swapList(&list, &tempList);
	printList(&list);

	clearList(&list);
	clearList(&tempList);

	return 0;
}