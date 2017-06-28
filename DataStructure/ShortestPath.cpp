/************************************************************************************
*																					*
*	국민대학교 컴퓨터 공학부 20123417 조성룡										*
*	프로그램 명: Shortest Path														*
*	설		 명: Cost Matrix에 기초하여 원하는 정점에서의 최단거리를 구한다.		*
*   사 용 함 수: init - graph를 초기화한다. 											*
*				 Shortestpath - cost에 기초하여 최단거리를 비교, 출력한다.			*
*				 choose	- 방문하지않은 정점에 대하여 최단거리를 구하고 반환한다.		*
*				 getcost - 주어진 Cost Matrix를 graph에 입력한다.					*
*																					*
************************************************************************************/

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
};

void main()
{
	graph SP; // SP의 생성

	// Cost Matrix //
	int matrix[Max][Max] = { {100,2,4,5,100,100,100} , {2,100,100,2,7,100,100} ,
	{100,100,100,1,100,4,100} , {100,2,1,100,4,3,100} , {100,7,100,4,100,1,5} ,
	{100,100,4,3,1,100,7} , {100,100,100,100,7,5,100} };

	int select;
	int n; // 정점의 개수
	int start; // Shortest Path의 시작 점을 결정
	while(1)
	{
		cout << "1.Insert_Vertices 2.Matirx 3.ShortestPath 4.exit :";
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
			exit(1);
		}
	}


}


/************************************************************
*	choose() Algorithm										*
*	입력된 vertex의 cost를 distance에 입력받으면(조건)		*
*	choose함수 호출 시 distance의 원소를 비교하여			*
*	최소값을 갖는 원소의 번호를 반환한다.					*
*	여기서 원소의 번호는 vertex를 의미한다.					*
************************************************************/
int graph::choose() // 강의노트 참조
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for(i=0; i< n; i++)
		if(distance[i] < min && !found[i]) 
		{
			min = distance[i];
			minpos = i;
		}

	return minpos;
}

/****************************************************************
*	Shortestpath(int v) Algorithm								*
*	v는 정점을 의미하며 v에서의 각 정점에 이르는 최소 cost를	*
*	구하는 것이 목적이다. 함수가 호출되면 Cost Matrix에서 v의	* 
*	행의 cost를 distance에 입력한 후에 choose 함수를 호출하여	*
*	방문자가 false이면 distance에 입력된 cost비교를 한다.		*
*	더해진 cost가 적은 것이 그 정점에서의 새로운 cost가 된다.	*
****************************************************************/
void graph::Shortestpath(int v) // 강의노트 참조
{
	int u,w;

	for(int i=0; i<n; i++) 
	{
		found[i] = false;
		distance[i] = cost[v][i];
	}

	found[v] = true; // start vertex mark
	distance[v] = 0; // start vertex 0

	for(int i=0; i<n-1; i++) 
	{
		u = choose(); // find min value node
		found[u] = true; // mark that node
		for(w=0; w<n; w++) // and replace if revised value
			if (!found[w]) // if not marked
				if (distance[u] + cost[u][w] < distance[w]) //is smaller than org
		distance[w] = distance[u] + cost[u][w]; // value

		for(int i=0; i<n; i++) // 중간 과정 출력
			cout << distance[i] << " ";
		cout << endl;
	}
}

// 초기화 //
void graph::init(int vertices)
{
	n = vertices;
	for(int i=0; i<vertices; i++)
		found[i] = false;
}

// 접근자 //
void graph::getcost(int matrix[][Max])
{
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			cost[i][j] = matrix[i][j];
}

