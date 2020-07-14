// 12171788 박지은

#include <stdio.h>
#include <string.h>

int next[50];
struct input {
	int next;
	char word[250];
};

// 재시작 위치 알고리즘
void InitNext(char *p)
{
	int i, j = 0;
	int M = strlen(p);
	next[0] = -1;	// 첫번째 인덱스 초기화

	for (i = 0, j = -1; i < M; i++, j++) {
		next[i] = (p[i] == p[j]) ? next[j] : j; //개선된버전
		// if(p[i] == p[j]) next[i] = next[j];
		while ((j >= 0) && (p[i] != p[j]))
			j = next[j];
	}
}

// KMP 함수
int KMP(char *p, char *t)
{
	int i, j;
	int M = strlen(p), N = strlen(t);
	InitNext(p); // next 함수 호출
	for (i = 0, j = 0; j < M && i < N; i++, j++)
		while ((j >= 0) && (t[i] != p[j])) j = next[j];
	if (j == M) return i - M;
	else return i;
}

// 정렬 함수
void sort(input S[], int N) {
	int i, j;
	input temp;

	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N - 1 - i; j++) {
			if (S[j].next > S[j+1].next) {	// SWAP
				temp = S[j];
				S[j] = S[j + 1];
				S[j + 1] = temp;
			}
		}
	}
}

int main()
{
	char keyword[8];
	scanf("%s", &keyword);

	input inputs[100];

	int num = 0;	// 입력받은 문자열 인덱스

	while (1) {
		num++;
		scanf("%s", &inputs[num].word);
		int M, N, pos, previous = 0, i = 0;

		if (inputs[num].word[0] == '0') {
			sort(inputs, num);
			for (int j = 1; j < num; j++) {
				// 출력문 작성
				printf("%s\n", inputs[j].word);
			}
			break;
		}
		else {
			M = strlen(keyword);
			N = strlen(inputs[num].word);

			while (1) { // KMP 사용하여 스트링 탐색
				pos = KMP(keyword, inputs[num].word + i);
				pos += previous;
				i = pos + M;
				if (i <= N)
					inputs[num].next = pos;
				else break;
				previous = i;
			}
		}
	}

	return 0;
}
