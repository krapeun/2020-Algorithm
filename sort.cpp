// Sorting HW1 12171788 박지은

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SWAP(a,b){int t = a; a = b; b = t;}

clock_t start;	// start time
clock_t finish;	// finish time
clock_t times = 0;

void selection_sort(int n, int S[]);	// Selection Sort
void quick_sort(int S[], int l, int r);	// Median-of-three Quick Sort
void shell_sort(int n, int S[]);	// Shell Sort
void bitonic_sort(int S[], int a, int b, bool ascend);	// Bitonic Sort
void bitonic_merge(int S[], int a, int b, bool ascend);
void oddeven_sort(int S[], int a, int b);	// Odd-Even Merge Sort
void oddeven_merge(int S[], int a, int b, int x);

void timer();
void copy(int n, int S[], int C[]);	// copy array

int main() {
	int n;	// size of data set
	int i;

	printf("Enter data size : ");
	scanf("%d", &n);	// size input
	printf("\n");

	int *list = new int[n];	// data set array
	int *copy_list = new int[n];	// copy array

	srand((unsigned int)time(NULL));	// initialization rand
	for (i = 1; i <= n; i++)
		list[i] = rand()%50 + 1;	// 1~50 random

	// selection_sort
	copy(n, list, copy_list);
	start = clock();
	selection_sort(n, copy_list);
	finish = clock();
	printf("- Selection Sort -\n");
	timer();

	// quick_sort
	copy(n, list, copy_list);
	start = clock();
	quick_sort(copy_list, 1, n);
	finish = clock();
	printf("- Median-of-three Quick Sort -\n");
	timer();

	// shell_sort
	copy(n, list, copy_list);
	start = clock();
	shell_sort(n, copy_list);
	finish = clock();
	printf("- Shell Sort -\n");
	timer();

	// bitonic_sort
	copy(n, list, copy_list);
	start = clock();
	bitonic_sort(copy_list, 1, n, true);
	finish = clock();
	printf("- Bitonic Sort -\n");
	timer();

	// merge_sort
	copy(n, list, copy_list);
	start = clock();
	oddeven_sort(copy_list, 1, n);
	finish = clock();
	printf("- Odd-even Merge Sort -\n");
	timer();

	return 0;
}

void selection_sort(int n, int S[]) {
	int i, j, min;

	for (i = 1; i <= n - 1; i++) {
		min = i;	// first index is current min
		for (j = i + 1; j <= n; j++)	// scan
			if (S[min] > S[j]) min = j;	// if find min
		SWAP(S[i], S[min]);	// finally SWAP
	}
}

void quick_sort(int S[], int a, int b) {
	int left, right, mid;
	int pivot;

	if (b - a >= 2) {	// if data size >= 3
		mid = (a + b) / 2;	// midium

		// left, mid, right first sort
		if (S[a] > S[b]) SWAP(S[a], S[b]);
		if (S[a] > S[mid]) SWAP(S[a], S[mid]);
		if (S[mid] > S[b]) SWAP(S[mid], S[b]);
		SWAP(S[mid], S[b - 1]);

		// left, right
		pivot = S[b - 1];
		left = a;
		right = b - 1;

		for (;;) {	// repeat until left and right cross
			while (S[++left] < pivot);	// stop when bigger than pivot
			while (S[--right] > pivot);	// stop when smaller than pivot
			if (left >= right)	break;	// stop when data is small
			SWAP(S[left], S[right]);	// left와 right에 반대되는 값이 있을 때 교환
		}

		SWAP(S[left], S[b - 1]);	// finding his place

		// recursive call
		quick_sort(S, a, left - 1);	// left half
		quick_sort(S, left + 1, b);	// right half
	}
	else if (S[a] > S[b]) SWAP(S[a], S[b]);	// just comparison
}

void shell_sort(int n, int S[]) {
	int h, i, j;
	int key;

	for (h = 1; h < n; h = 3 * h + 1) {}	// 처음 서브 리스트 크기 계산
	for (; h > 0; h = h / 3) {	// 서브 리스트 크기 줄이면서 계산
		for (i = h + 1; i <= n; i++) {	// scan
			key = S[i];		// select insertion data
			j = i;
			while ((j > h) && (S[j - h] > key)) {	//  비교 후 위치 찾을 때까지
				S[j] = S[j - h];
				j = j - h;
			}
			S[j] = key;		// insert
		}
	}
}

void bitonic_sort(int S[], int a, int b, bool ascend) {
	int mid;

	if (b > 1) {		// data size >= 1
		mid = b / 2;	// mid : n/2
		// recursive call
		bitonic_sort(S, a, mid, true);	// ascending
		bitonic_sort(S, a + mid, b - mid, false);	// descending
		bitonic_merge(S, a, b, ascend);	// merge
	}
}

void bitonic_merge(int S[], int a, int b, bool ascend) {
	int i, mid;

	if (b > 1) {		// data size >= 1
		mid = b / 2;	// mid : n/2
		for (i = a; i < a + b - mid; i++) {	// ascending, descending
			if (ascend == (S[i] > S[i + mid]))
				SWAP(S[i], S[i + mid]);	// ascending swap
		}
		// recursive call
		bitonic_merge(S, a, mid, ascend);	// merge again for the left half
		bitonic_merge(S, a + mid, b - mid, ascend);	// merge again for the right half
	}
}

void oddeven_sort(int S[], int a, int b) {
	int i, mid;

	if (b > 1) {		// 크기가 2가 될 때까지 partition
		mid = b / 2;	// mid : n/2
		// recursive call
		oddeven_sort(S, a, mid);	// left half
		oddeven_sort(S, a + mid, b - mid);	// right half
		oddeven_merge(S, a, b, 1);	// 비교 크기를 1로 시작
	}
}

void oddeven_merge(int S[], int a, int b, int x) {
	int i;

	// increase the comparison size 1 ~ n/2
	if (x * 2 < b) {	// data size >= 1
		// recursive call
		oddeven_merge(S, a, b, x * 2);
		oddeven_merge(S, a + x, b, x * 2);
		for (i = a + x; i < a + b - x; i += x * 2) {
			if (S[i] > S[i + x])	// 배열의 첫번째 데이터 크기 비교
				SWAP(S[i], S[i + x]);	// 크기 비교 후 정렬
		}
	}
	else
		if (S[a] > S[a + x])	// sort after simple comparison
			SWAP(S[a], S[a + x]);
}

void timer() {
	times = finish - start;
	printf("Time : %f\n\n", (float)times / CLOCKS_PER_SEC);
}

void copy(int n, int S[], int C[]) {
	int i;
	for (i = 1; i <= n; i++)
		C[i] = S[i];		// copy origin
}