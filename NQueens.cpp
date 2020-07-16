// 알고리즘설계 프로젝트 12171788 박지은

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start;	// 시작 시간
clock_t finish;	// 종료 시간
clock_t times = 0;	// 실행 시간 측정 변수

int sum;	// 해답의 수
int generation;	// 세대 수

bool found = false;	// backtracking 정답 찾았을 때

struct Genome {
	int chess[50];	// 체스판 배열
	int fitness = 0;	// 적합도
};

// 실행 시간 측정 함수
void timer() {
	times = finish - start;	// 실행 시간 측정
	printf("Time : %fsec\n\n", (float)times / CLOCKS_PER_SEC);
}

void Backtracking(int n, int C[], int position) {
	if (found == true) return;	// 성공시 종료
	if (position == n) {	// n개의 퀸을 모두 두었을 때 (성공시)
		found = true;
		for (int i = 0; i < n; i++)
			printf("%d ", C[i]);
		printf("\n");
		return;	// 성공시 종료
	}
	else {
		for (int i = 0; i < n; i++) {	// 열 비교 index
			C[position] = i;	// 퀸을 해당 열에 두기
			
			// 유망성 판단
			bool promising = true;
			for (int j = 0; j < position; j++) {	// 만족하지 않는 모든 경우
				if (C[j] == C[position]) promising = false;	// 상하좌우에 위치
				// 대각선 상에 위치
				if ((C[j] - C[position]) == (position - j)) promising = false;
				if ((C[position] - C[j]) == (position - j)) promising = false;
			}

			if (promising == true) {	// 유망성을 만족하는 경우
				if(position == n - 1){
					for (int i = 0; i < n; i++)
						printf("%d ", C[i]);
					printf("\n");
					found = true;
					return;	// 성공시 종료
				}
				Backtracking(n, C, position + 1);	// 다음 행에서 판단 (재귀적 호출)
			}
		}
	}
}

void encoding(int n, Genome C[]) {
	int *check = new int[n];	// 중복된 난수인지 체크하는 index

	// 염색체 인코딩
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < n; j++) check[j] = 0;	// index 초기화

		for (int j = 0; j < n; j++) {
			int temp = rand() % n;	// 0 ~ n-1의 난수 생성 
			// 중복 체크
			if (check[temp] == 0) {
				C[i].chess[j] = temp;
				check[temp] = 1;
			}
			else j--;	// 중복되는 경우 다시
		}
	}
}

void fitness_count(int n, Genome C[]) {
	int correct = 0;	// 공격 하지 않는 퀸의 수
	for (int i = 1; i < n; i++) correct += i;	// 목표 값
	
	for (int k = 0; k < 100; k++) {
		int sum = correct;	// 목표 값에서 출발

		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {	// 다음 행 비교 index
				// 공격 가능할 때마다 discount
				if ((C[k].chess[i] == C[k].chess[j])) sum--;
				if ((C[k].chess[i] - C[k].chess[j]) == (i - j)) sum--;
				if ((C[k].chess[j] - C[k].chess[i]) == (i - j)) sum--;
			}
		}
		C[k].fitness = 100 * sum / correct;	// 0 ~ 100%
		//C[k].fitness = sum;
	}
}

// Tournament Selection
void selection(int n, Genome C[], Genome B[]) {
	int check[100];	// 중복된 난수인지 체크하는 index
	int tournament[2];	// 토너먼트 배열

	for (int l = 0; l < 100; l++) {	// 100개의 다음 세대 개체 선택
		for (int i = 0; i < 100; i++) check[i] = 0;	// 초기화

		for (int i = 0; i < 2; i++) {	// 4개의 개체를 임의로 선택
			int temp = rand() % 50;
			// 중복 체크
			if (check[temp] == 0) {
				tournament[i] = temp;
				check[temp] = 1;
			}
			else i--;	// 중복되는 경우 다시
		}

		int max = 0;	// 가장 큰 적합도
		int max_index;	// 적합도가 큰 개체 인덱스

		for (int i = 0; i < 2; i++) {	// 적합도가 가장 큰 개체 선택
			if (C[tournament[i]].fitness > max) {
				max = C[tournament[i]].fitness;
				max_index = tournament[i];
			}
		}

		B[l].fitness = max;	// 적합도가 가장 큰 개체로 자식 설정
		for (int i = 0; i < n; i++)	// 자손에게 넘겨주기
			B[l].chess[i] = C[max_index].chess[i];
	}
}

void crossover(int n, Genome B[]) {
	for (int i = 0; i < 100; i += 2) {
		int prob = rand() % 100;
		if (prob < 95) {	// 교차 확률 80%
			int point = rand() % (n / 2) + (n / 4);	// 교차 포인트 설정
			for (int j = point; j < n; j++) {
				// single point crossover
				int temp = B[i].chess[j];
				B[i].chess[j] = B[i + 1].chess[j];
				B[i + 1].chess[j] = temp;
			}
		}
	}
}

// Insertion Mutation
void mutation(int n, Genome C[], Genome B[]) {
	for (int i = 0; i < 100; i++) {
		int prob = rand() % 100;
		if (prob < 1) {	// 돌연변이 확률 1%
			// 임의의 두 지점 선택
			int a = rand() % n;
			int b;
			for (;;) {	// a != b일 때까지
				b = rand() % n;
				if (a != b) break;
			}

			int *insertion = new int[n];	// 복사할 배열
			for (int j = 0; j < n; j++)	// 플래그 초기화
				insertion[j] = -1;

			insertion[b] = B[i].chess[a];

			for (int j = 0, k = 0; j < n, k < n; j++, k++) {
				// insertion index = j, chess index = k
				if (insertion[j] == -1 && k != b)
					insertion[j] = B[i].chess[k];
				else if (insertion[j] == -1 && k == b) j--;
			}

			for (int j = 0; j < n; j++) // 원본 배열로 옮김
				C[i].chess[j] = insertion[j];
		}
		else {	// 돌연변이가 없는 경우
			for (int j = 0; j < n; j++)
				C[i].chess[j] = B[i].chess[j];
		}
	}
}

void GeneticAlgorithm(int n, Genome C[], Genome B[]) {
	encoding(n, C);	// first population
	fitness_count(n, C);	// fitness check

	for (int i = 0; i < 100; i++)
		if (C[i].fitness == 100) {	// 초기 세대에서 정답이 있는 경우
			for (int j = 0; j < n; j++) 
				printf("%d ", C[i].chess[j]);
			printf("\n");
			return;
		}

	for (;;) {	// 정답을 찾을 때까지
		selection(n, C, B);	// selection
		crossover(n, B);	// crossover
		mutation(n, C, B);	// mutation
		fitness_count(n, C);	// fitness

		generation++;

		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < n; j++)
				printf("%d ", C[i].chess[j]);
			printf("\n");
			if (C[i].fitness == 100) {	// 정답이 있는 경우
				for (int j = 0; j < n; j++)
					printf("%d ", C[i].chess[j]);
				printf("\n");
				return;
			}
		}
	}
}

int main() {
	int n;	// 데이터 셋의 크기
	srand((unsigned int)time(NULL));	// 난수 초기화

	for (;;) {
		printf("Enter data size N : ");
		scanf("%d", &n);

		if (n == 0) break;	// 0 입력시 종료
		else {
			// Backtracking
			int *chess_backtrack = new int[n];	// 체스판 배열
			int position = 0;	// 첫 비교 위치
			found = false;

			printf("---Backtracking---\n");
			start = clock();
			Backtracking(n, chess_backtrack, position);
			finish = clock();
			timer();

			// Genetic Algorithm
			generation = 0;	// 세대 초기화
			Genome Genomes[100];	// Population Size = 100
			Genome Baby[100];	// 다음 세대의 개체
			
			printf("---Genetic Algorithm---\n");
			start = clock();
			GeneticAlgorithm(n, Genomes, Baby);
			finish = clock();
			printf("total generation = %d\n", generation);
			timer();
		}
	}

	return 0;
}
