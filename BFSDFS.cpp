// 알고리즘설계 HW#3 12171788 박지은
#include <stdio.h>

int Graph[100][100];	// 그래프

// Breadth First Search
void BFS(int s, int N) {
	int front = 0, rear = 0;	// push & pop index
	int *queue = new int[N];	// 방문할 정점 저장하는 queue
	int *visited = new int[N];

	// 모든 정점을 방문 안 한 것으로 초기화
	for (int i = 0; i < N; i++) visited[i] = 0;

	queue[rear] = s;	// enqueue
	rear++;
	visited[s] = 1;	// 방문하였음을 표시

	while (front < rear) {	// queue가 비어있는지 확인
		int j = queue[front];	// dequeue
		front++;
		for (int i = 0; i < N; i++) {
			// 간선이 있고 방문하지 않았을 때 (인접 노드)
			if ((Graph[j][i] == 1) && (visited[i] == 0)) {
				printf("- (%d) ", i);	// visited
				queue[rear] = i;	// enqueue
				rear++;
				visited[i] = 1;	// 방문하였음을 표시
			}
		}
	}
}

// Depth First Search
void DFS(int s, int N) {
	int *stack = new int[N];	// 방문할 정점 저장하는 stack
	int *S = new int[N];	// 이미 스택에 있는지 확인하기 위한 배열
	int *visited = new int[N];

	// 모든 정점을 방문 안 한 것으로 초기화
	for (int i = 0; i < N; i++) {
		visited[i] = 0;
		S[i] = 0;
	}

	int stack_count = 1;
	stack[stack_count - 1] = s;

	while (stack_count > 0) {	// stack이 비어있는지 확인
		int j = stack[stack_count - 1];	// pop
		stack_count--;
		if (j != 0) printf("- (%d) ", j);	// visited

		if (visited[j] == 0) {	// 아직 방문하지 않았을 때
			visited[j] = 1;	// 방문하였음을 표시
			for (int i = 0; i < N; i++) {	// 간선이 있고 방문하지 않았을 때 (인접 노드)
				if ((Graph[j][i] == 1) && (visited[i] == 0) && (S[i]==0)) {
					stack[stack_count] = i;	// push
					stack_count++;
					S[i] = 1;	// stack에 넣었음을 확인
				}
			}
		}
	}
}

int main() {
	int N, M;	// 정점의 개수, 간선의 개수
	int start;	// 시작 정점
	scanf("%d %d %d", &N, &M, &start);

	// 간선 입력
	for (int i = 0; i < M; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		// 양방향으로 연결
		Graph[u][v] = 1;
		Graph[u][v] = 1;
	}

	printf("BFS : (%d) ", start);	// 시작 정점 출력
	BFS(start, N);	// BFS 호출
	printf("\n");
	
	printf("DFS : (%d) ", start);	// 시작 정점 출력
	DFS(start, N);	// DFS 호출
	printf("\n");

	return 0;
  }
