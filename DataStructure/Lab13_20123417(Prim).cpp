#include<iostream>
#include<cstdlib>
using namespace std;

const int Max = 100;

class graph
{
private:
	int n; // 정점의 갯수 ( 매트릭스 크기 )
	int cost[Max][Max]; // Cost Matrix
	int distance[Max]; // 정점들의 거리
	bool found[Max]; // 방문 정보

public:
	void init(int vertices); // graph의 초기화, 인자는 정점의 개수
	void Shortestpath(int v); // 인자는 정점
	void getcost(int matrix[][Max]); // 주어진 cost matrix를 입력받는다
	int choose();
	void Prim(int v);
};

void main()
{
	graph SP; // SP의 생성

	// Cost Matrix //
	int matrix[Max][Max] = { {100,6,1,5,100,100} , {6,100,4,100,3,100} ,
	{1,4,100,5,6,5} , {5,100,5,100,100,2} , {100,3,6,100,100,6} ,
	{100,100,5,2,6,100} };

	int select;
	int n; // 정점의 개수
	int start; // Shortest Path의 시작 점을 결정
	while(1)
	{
		cout << "1.Insert_Vertices 2.Matirx 3.ShortestPath 4.Prim 5.exit :";
		cin >> select;

		switch (select)
		{
		case 1:
			cout << "정점의 개수: ";
			cin >> n;
			SP.init(n);
			cout << endl;	break;

		case 2:
			cout << "**** COST MATRIX\n";
			cout << "\t";
			for(int i=0; i<n; i++)
				cout << i << "\t" ;
			cout << endl;
			for(int i=0; i<n; i++)
			{
				cout << i << " \t";
				for(int j=0; j<n; j++)
					cout << matrix[i][j] << "\t";
				cout << endl;
			}
			SP.getcost(matrix); // Cost Matrix를 입력 //
			cout << endl;	break;
			
		case 3:
			cout << "Shortest Path\n";
			cout << "Start vertex: ";
			cin >> start;
			SP.Shortestpath(start);
			cout << endl;	break;

		case 4:
			cout << "Prim's Algorithm\n";
			cout << "Start vertex: ";
			cin >> start;
			SP.Prim(start);
			cout << endl << endl; break;

		case 5:
			exit(1);
		}
	}


}


//*************** Public 멤버 함수 ***************//
int graph::choose() // 강의노트 참조
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for(i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) 
		{
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void graph::Shortestpath(int v) // 강의노트 참조
{
	int I,u,w;

	// 초기 distance 설정 (입력받은 v를 토대로) //
	for (I=0; I<n; I++) 
	{
		found[I] = false;
		distance[I] = cost[v][I];
	}

	found[v]=true; // start vertex mark
	distance[v]=0; // start vertex 0

	for(I=0; I<n-1; I++) 
	{
		u = choose(); // find min value node
		found[u] = true; // mark that node
		for(w=0; w<n; w++) // and replace if revised value
			if (!found[w]) // if not marked
				if (distance[u]+cost[u][w] < distance[w]) //is smaller than org
		distance[w] = distance[u] + cost[u][w]; // value

		for(int i=0; i<n; i++) // 중간 과정 출력
			cout << distance[i] << " ";
		cout << endl;
	}

	// 방문자 초기화 //
	for(int i=0; i<n; i++)
		found[i] = false;
}

void graph::Prim(int v)
{
	int u;

	// 초기 distance 설정 (입력받은 v를 토대로) //
	for(int i=0; i<n; i++)
	{
		distance[i] = cost[v][i];
	}

	cout << v;
	found[v]=true;
	distance[v]=0;


	u = choose();
	if(!found[u])
	{
		cout << " -> ";
		Prim(u);
	}

	/* 방문자 초기화 */
	for(int i=0; i<n; i++)
		found[i] = false;
}

void graph::init(int vertices)
{
	n = vertices;
	for(int i=0; i<vertices; i++)
		found[i] = false;
}

void graph::getcost(int matrix[][Max])
{
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			cost[i][j] = matrix[i][j];
}

