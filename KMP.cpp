// �˰��򼳰� HW2 12171788 ������

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// ����� ��ġ �˰���
void InitNext(char *p, int *next) {
	int i = 1, j = 0;	// ���� �� �ε���
	int M = strlen(p);	// ������ ����
	next[0] = 0;	// next �迭 ù �ε��� �ʱ�ȭ

	while (i < M) {
		if (p[i] == p[j]) {	// ��ġ�� ��
			j++;
			next[i] = j;
			i++;	// ���� �ε����� �̵�
		}
		else {	// ����ġ�� ��
			if (j == 0) {
				next[i] = j;
				i++;	// ���� �ε����� �̵�
			}
			else j = next[j - 1];	// ��Ī�� ������
		}
	}
}

// KMP �Լ�
int KMP(char *p, char *t, int *next){
	int i = 0, j = 0;  // �� �ε���
	int M = strlen(p);	// ������ ����
	int N = strlen(t);	// �ؽ�Ʈ�� ����
	InitNext(p, next);	// next �Լ� ȣ��

	int sum = 0;	// ��ġ�ϴ� �� ����

	while (i < N) {
		if (t[i] == p[j]) {	// ��ġ�� ��
			i++;	// �ؽ�Ʈ�� ���� �ε����� �̵�
			j++;	// ������ ���� �ε����� �̵�
		}
		else if (t[i] != p[j]) {	// ����ġ�� ��
			if (j == 0) i++;
			else j = next[j - 1];	// ��Ī�� ������
		}
		if (j == M) {	// ������ ������ ��ġ�� ��
			printf("Pattern found : %d\n", i - j + 1);
			j = next[j - 1];
			sum++;	// ��ġ ���� ī��Ʈ
		}
	}
	return sum;
}

int main() {
	char *pattern = (char*)malloc(sizeof(char));	// ���� ���� �迭

	int *next = (int*)malloc(sizeof(int));	// ���� ��ġ ���� �迭

	FILE *fp = fopen("RFC2616_modified.txt", "rt");	// ���� ����

	char *buf = (char*)malloc(sizeof(char));	// ���� ���� ���� �迭
	int num = 0;	// ���� �Է� ���� ����

	while (!feof(fp)) {	// ���� ���� ����
		buf = (char*)realloc(buf, sizeof(char)*(num + 1));
		fscanf(fp, "%c", &buf[num]);
		num++;
	}
	printf("%s\n", buf);	// ���� ���� ���

	while (1) {
		printf("Enter pattern : ");
		scanf("%s", pattern);	// ���� �Է�

		int sum = 0;	// �� ���� ����

		if (pattern[0] == '0') break;	// 0 �Է� �� ����
		else {
			//printf("Enter text : ");
			//scanf("%s", buf);	// �ؽ�Ʈ �Է�

			sum = KMP(pattern, buf, next);	// KMP ����Ͽ� ��Ʈ�� Ž��
			printf("Sum : %d\n", sum);
		}
	}

	fclose(fp);	// ���� �ݱ�
	return 0;
}