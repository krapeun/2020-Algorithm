// 알고리즘설계 HW2 12171788 박지은

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// 재시작 위치 알고리즘
void InitNext(char *p, int *next) {
	int i = 1, j = 0;	// 패턴 비교 인덱스
	int M = strlen(p);	// 패턴의 길이
	next[0] = 0;	// next 배열 첫 인덱스 초기화

	while (i < M) {
		if (p[i] == p[j]) {	// 일치할 때
			j++;
			next[i] = j;
			i++;	// 다음 인덱스로 이동
		}
		else {	// 불일치할 때
			if (j == 0) {
				next[i] = j;
				i++;	// 다음 인덱스로 이동
			}
			else j = next[j - 1];	// 매칭될 때까지
		}
	}
}

// KMP 함수
int KMP(char *p, char *t, int *next){
	int i = 0, j = 0;  // 비교 인덱스
	int M = strlen(p);	// 패턴의 길이
	int N = strlen(t);	// 텍스트의 길이
	InitNext(p, next);	// next 함수 호출

	int sum = 0;	// 일치하는 총 개수

	while (i < N) {
		if (t[i] == p[j]) {	// 일치할 때
			i++;	// 텍스트의 다음 인덱스로 이동
			j++;	// 패턴의 다음 인덱스로 이동
		}
		else if (t[i] != p[j]) {	// 불일치할 때
			if (j == 0) i++;
			else j = next[j - 1];	// 매칭될 때까지
		}
		if (j == M) {	// 패턴의 끝까지 일치할 때
			printf("Pattern found : %d\n", i - j + 1);
			j = next[j - 1];
			sum++;	// 일치 개수 카운트
		}
	}
	return sum;
}

int main() {
	char *pattern = (char*)malloc(sizeof(char));	// 패턴 저장 배열

	int *next = (int*)malloc(sizeof(int));	// 진행 위치 저장 배열

	FILE *fp = fopen("RFC2616_modified.txt", "rt");	// 파일 열기

	char *buf = (char*)malloc(sizeof(char));	// 파일 내용 저장 배열
	int num = 0;	// 파일 입력 변수 개수

	while (!feof(fp)) {	// 파일 내용 저장
		buf = (char*)realloc(buf, sizeof(char)*(num + 1));
		fscanf(fp, "%c", &buf[num]);
		num++;
	}
	printf("%s\n", buf);	// 파일 내용 출력

	while (1) {
		printf("Enter pattern : ");
		scanf("%s", pattern);	// 패턴 입력

		int sum = 0;	// 총 개수 저장

		if (pattern[0] == '0') break;	// 0 입력 시 종료
		else {
			//printf("Enter text : ");
			//scanf("%s", buf);	// 텍스트 입력

			sum = KMP(pattern, buf, next);	// KMP 사용하여 스트링 탐색
			printf("Sum : %d\n", sum);
		}
	}

	fclose(fp);	// 파일 닫기
	return 0;
}
