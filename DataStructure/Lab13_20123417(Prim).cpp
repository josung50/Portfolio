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
	void Prim(int v);
};

void main()
{
	graph SP; // SP�� ����

	// Cost Matrix //
	int matrix[Max][Max] = { {100,6,1,5,100,100} , {6,100,4,100,3,100} ,
	{1,4,100,5,6,5} , {5,100,5,100,100,2} , {100,3,6,100,100,6} ,
	{100,100,5,2,6,100} };

	int select;
	int n; // ������ ����
	int start; // Shortest Path�� ���� ���� ����
	while(1)
	{
		cout << "1.Insert_Vertices 2.Matirx 3.ShortestPath 4.Prim 5.exit :";
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


//*************** Public ��� �Լ� ***************//
int graph::choose() // ���ǳ�Ʈ ����
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

void graph::Shortestpath(int v) // ���ǳ�Ʈ ����
{
	int I,u,w;

	// �ʱ� distance ���� (�Է¹��� v�� ����) //
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

		for(int i=0; i<n; i++) // �߰� ���� ���
			cout << distance[i] << " ";
		cout << endl;
	}

	// �湮�� �ʱ�ȭ //
	for(int i=0; i<n; i++)
		found[i] = false;
}

void graph::Prim(int v)
{
	int u;

	// �ʱ� distance ���� (�Է¹��� v�� ����) //
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

	/* �湮�� �ʱ�ȭ */
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

