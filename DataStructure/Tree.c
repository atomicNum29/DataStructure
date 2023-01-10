#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _TNODE TNode;
struct _TNODE {
	int data;
	TNode* parent;
	TNode** child;
};

int main() {

	return 0;
}