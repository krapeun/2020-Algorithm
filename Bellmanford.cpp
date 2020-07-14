// 알고리즘설계 HW#3 12171788 박지은
#include <stdio.h>

int weight[1000][1000];

void BellmanFord(int s, int N, int *D) {
	// 시작점 초기화
	weight[s][s] = 0;
	D[s] = 0;
	
	for (int k = 2; k < N - 1; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// 진입 차수가 0보다 큰 모든 정점에 대해
				if (i != j && weight[i][j] != 10000) {
					if (D[j] > D[i] + weight[i][j]) {
						D[j] = D[i] + weight[i][j];
					}
				}
			}
		}
	}
}

int main() {
	int N, M;	// 정점의 개수, 간선의 개수
	int start;	// 시작 정점

	scanf("%d %d %d", &N, &M, &start);

	int *Dist = new int[N];	// 최단 경로 저장

	// 경로 초기화
	for (int i = 0; i < N; i++) {
		Dist[i] = 10000;
		for (int j = 0; j < N; j++)
			weight[i][j] = 10000;
	}

	// 간선 입력
	for (int i = 0; i < M; i++) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		weight[v][u] = w;	// v --> u
	}

	BellmanFord(start, N, Dist);

	// 시작점에서부터 경로 출력
	for (int i = 0; i < N; i++)
		printf("(%d) - (%d) : %d\n", start, i, Dist[i]);

	return 0;
}
