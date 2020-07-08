// 4week 12171788 ¹ÚÁöÀº

#include <stdio.h>
#include <stdlib.h>

void heapifyA(int *a, int *b, int here, int size) {
	int left = here * 2 + 1;
	int right = here * 2 + 2;
	int max = here;

	if (left < size && a[left] > a[max]) max = left;
	if (right < size && a[right] > a[max]) max = right;

	if (max != here) {
		int temp = a[here];
		a[here] = a[max];
		a[max] = temp;
		heapifyA(a, b, max, size);
	}
}

void heapifyB(int *a, int *b, int here, int size) {
	int left = here * 2 + 1;
	int right = here * 2 + 2;
	int min = here;

	if (left > size && b[left] < b[min]) min = left;
	if (right > size && b[right] < b[min]) min = right;

	if (min != here) {
		int temp = b[here];
		b[here] = b[min];
		b[min] = temp;
		heapifyB(a, b, min, size);
	}
}

void buildHeap(int *a, int *b, int size) {
	for (int i = size / 2 - 1; i >= 0; i--) {
		heapifyA(a, b, i, size);
		heapifyB(a, b, i, size);
	}
}

void heapSort(int *a, int *b, int size) {
	buildHeap(a, b, size);
	for (int treeSize = size - 1; treeSize >= 0; treeSize--) {
		int temp = a[0];
		a[0] = a[treeSize];
		a[treeSize] = temp;

		temp = b[0];
		b[0] = b[treeSize];
		b[treeSize] = temp;

		heapifyA(a, b, 0, treeSize);
		heapifyB(a, b, 0, treeSize);
	}
}

void printResult(int *a, int *b, int size) {
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum = sum + (a[i] * b[i]);
	}

	printf("%d\n", sum);
}

int main() {
	int length = 0;
	scanf("%d", &length);
	if (length < 1) length = 1;
	else if (length > 100) length = 100;

	int *alpha = new int[length];
	int *beta = new int[length];

	for (int i = 0; i < length; i++) {
		scanf("%d", &alpha[i]);
	}
	for (int i = 0; i < length; i++) {
		scanf("%d", &beta[i]);
	}

	heapSort(alpha, beta, length);
	printResult(alpha, beta, length);

	return 0;
}