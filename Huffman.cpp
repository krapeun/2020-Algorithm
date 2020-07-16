// 실기시험 1 12171788 박지은

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 
#define MAX_ELEMENT 1000

int bit_size = 0;	// 전체 비트 수 출력

struct nodetype {
	int symbol; // key -> ascii
	int freq = 0; // value
};

struct pq {
	nodetype weight;
	pq *left;
	pq *right;
};

struct Element {
	pq *pTree;
	int key;
};

struct HeapType {
	Element heap[MAX_ELEMENT];
	int heap_size;
};

void Insert(HeapType *h, Element item) {
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;
}

Element Delete(HeapType *h) {
	int parent = 1, child = 2;
	Element data, temp;

	data = h->heap[parent];
	temp = h->heap[(h->heap_size)--];

	while (child <= h->heap_size){
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;

		if (temp.key <= h->heap[child].key) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;
	return data;
}

pq* MakeNode(pq *l, pq *r) {
	pq *node = (pq*)malloc(sizeof(pq));

	if (node != NULL)
	{
		node->left = l;
		node->right = r;
	}

	return node;
}

void Array(pq *p, int n, char *code) {
	if (p != NULL) {
		n++;
		code[n] = '1';
		Array(p->left, n, code);
		code[n] = '0';
		Array(p->right, n, code);
		code[n] = '\0';

		if (p->left == NULL && p->right == NULL)
			bit_size += p->weight.freq * strlen(code);	// 비트 길이 계산
	}
}

void Huffman(nodetype *pArr, int n) {
	pq *node, *temp;
	Element e, e1, e2;
	HeapType heap;
	char binaryCode[100];

	heap.heap_size = 0;

	for (int i = 0; i<n; i++) {
		node = MakeNode(NULL, NULL);
		node->weight.symbol = pArr[i].symbol;
		e.key = node->weight.freq = pArr[i].freq;
		e.pTree = node;
		Insert(&heap, e);
	}

	for (int i = 0; i <= n - 2; i++) {
		e1 = Delete(&heap);
		e2 = Delete(&heap);

		temp = MakeNode(e1.pTree, e2.pTree);

		e.key = temp->weight.freq = e1.key + e2.key; 
		e.pTree = temp;

		Insert(&heap, e); 
	}
	e = Delete(&heap);

	Array(e.pTree, -1, binaryCode);
}

int main() {
	nodetype data[100];
	nodetype *copy;

	char input[100];
	scanf("%s", input);

	int a = 0;
	int index;
	int count = 0;

	for(int i = 'a'; i <= 'z'; i++) {
		index = 0;
		for (int j = 0; j < strlen(input); j++) {
			if (input[j] == i) {	// 존재할 때
				data[i - 97].freq++;
				index = 1;
			}
		}
		if (index == 1)
			count++;
	}

	copy = (nodetype*)malloc(sizeof(nodetype)*count);

	for (int i = 0; i < 100; i++) {
		if (data[i].freq != NULL) {	// 존재할 때
			copy[a].symbol = i + 97;
			copy[a].freq = data[i].freq;
			a++;
		}
	}

	Huffman(copy, count);

	printf("%d\n", bit_size);

	return 0;
}
