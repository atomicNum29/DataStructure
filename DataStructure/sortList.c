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

	return 0;
}