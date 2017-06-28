/************************************************************************************
*																					*
*	���δ��б� ��ǻ�� ���к� 20123417 ������										*
*	���α׷� ��: Shortest Path														*
*	��		 ��: Cost Matrix�� �����Ͽ� ���ϴ� ���������� �ִܰŸ��� ���Ѵ�.		*
*   �� �� �� ��: init - graph�� �ʱ�ȭ�Ѵ�. 											*
*				 Shortestpath - cost�� �����Ͽ� �ִܰŸ��� ��, ����Ѵ�.			*
*				 choose	- �湮�������� ������ ���Ͽ� �ִܰŸ��� ���ϰ� ��ȯ�Ѵ�.		*
*				 getcost - �־��� Cost Matrix�� graph�� �Է��Ѵ�.					*
*																					*
************************************************************************************/

#include<iostream>
#include<cstdlib>
using namespace std;

const int Max = 100;

class graph
{
private:
	int n; // ������ ���� ( ��Ʈ���� ũ�� )
	int cost[Max][Max]; // Cost Matrix
	int distance[Max]; // �������� �Ÿ�
	bool found[Max]; // �湮 ����

public:
	void init(int vertices); // graph�� �ʱ�ȭ, ���ڴ� ������ ����
	void Shortestpath(int v); // ���ڴ� ����
	void getcost(int matrix[][Max]); // �־��� cost matrix�� �Է¹޴´�
	int choose();
};

void main()
{
	graph SP; // SP�� ����

	// Cost Matrix //
	int matrix[Max][Max] = { {100,2,4,5,100,100,100} , {2,100,100,2,7,100,100} ,
	{100,100,100,1,100,4,100} , {100,2,1,100,4,3,100} , {100,7,100,4,100,1,5} ,
	{100,100,4,3,1,100,7} , {100,100,100,100,7,5,100} };

	int select;
	int n; // ������ ����
	int start; // Shortest Path�� ���� ���� ����
	while(1)
	{
		cout << "1.Insert_Vertices 2.Matirx 3.ShortestPath 4.exit :";
		cin >> select;

		switch (select)
		{
		case 1:
			cout << "������ ����: ";
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
			SP.getcost(matrix); // Cost Matrix�� �Է� //
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
*	�Էµ� vertex�� cost�� distance�� �Է¹�����(����)		*
*	choose�Լ� ȣ�� �� distance�� ���Ҹ� ���Ͽ�			*
*	�ּҰ��� ���� ������ ��ȣ�� ��ȯ�Ѵ�.					*
*	���⼭ ������ ��ȣ�� vertex�� �ǹ��Ѵ�.					*
************************************************************/
int graph::choose() // ���ǳ�Ʈ ����
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
*	v�� ������ �ǹ��ϸ� v������ �� ������ �̸��� �ּ� cost��	*
*	���ϴ� ���� �����̴�. �Լ��� ȣ��Ǹ� Cost Matrix���� v��	* 
*	���� cost�� distance�� �Է��� �Ŀ� choose �Լ��� ȣ���Ͽ�	*
*	�湮�ڰ� false�̸� distance�� �Էµ� cost�񱳸� �Ѵ�.		*
*	������ cost�� ���� ���� �� ���������� ���ο� cost�� �ȴ�.	*
****************************************************************/
void graph::Shortestpath(int v) // ���ǳ�Ʈ ����
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

		for(int i=0; i<n; i++) // �߰� ���� ���
			cout << distance[i] << " ";
		cout << endl;
	}
}

// �ʱ�ȭ //
void graph::init(int vertices)
{
	n = vertices;
	for(int i=0; i<vertices; i++)
		found[i] = false;
}

// ������ //
void graph::getcost(int matrix[][Max])
{
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			cost[i][j] = matrix[i][j];
}

