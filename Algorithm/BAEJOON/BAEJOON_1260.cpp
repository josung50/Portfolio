#include<iostream>
#include<queue>
using namespace std;

int Adjacent_Matrix[1001][1001];
int Visited[1001];
int TheNumberOf_vertax;
int TheNumberOf_edge;
int Start_vertax;
queue<int> Que;

void init();
void init_visited();
void insert_edge();
void dfs(int d, int n);
void bfs(int d, int n);

int main() {
	cin >> TheNumberOf_vertax >> TheNumberOf_edge >> Start_vertax;
	init();
	insert_edge();
	dfs(Start_vertax, TheNumberOf_vertax);
	cout << "\n";
	init_visited();
	bfs(Start_vertax, TheNumberOf_vertax);
}

void init() {
	for (int i = 1; i <= TheNumberOf_vertax; i++) {
		for (int j = 1; j <= TheNumberOf_vertax; j++)
			Adjacent_Matrix[i][j] = 0;
		Visited[i] = 0;
	}
}
void init_visited() {
	for (int i = 1; i <= TheNumberOf_vertax; i++)
		Visited[i] = 0;
}
void insert_edge() {
	int start;	int end;
	for (int i = 1; i <= TheNumberOf_edge; i++) {
		cin >> start >> end;
		Adjacent_Matrix[start][end] = 1;
		Adjacent_Matrix[end][start] = 1;
	}

	/*
	for (int i = 1; i <= TheNumberOf_vertax; i++) {
		for (int j = 1; j <= TheNumberOf_vertax; j++)
			cout << Adjacent_Matrix[i][j] << " ";
		cout << "\n";
	}
	*/
}
void dfs(int d, int n) {
	int j;
	Visited[d] = 1; // 방문
	cout << d << " ";
	for (j = 1; j <= n; j++) {
		if (Adjacent_Matrix[d][j] == 1 && Visited[j] == 0)
			dfs(j, n);
	}
}
void bfs(int d, int n) {
	int temp = 0;
	Visited[d] = 1;
	cout << d << " ";
	for (int i = 1; i <= n; i++) {
		if (Adjacent_Matrix[d][i] == 1 && Visited[i] == 0) {
			Que.push(i);
		}
	}
	
	// 큐에서 뽑았는데 이미 방문했을 경우 다음 큐에서 뽑아야 하기 때문에 while
	while (Que.empty() == 0) {
		temp = Que.front();
		Que.pop();
		if (Visited[temp] == 0) {
			bfs(temp, n);
			break;
		}
	}
}