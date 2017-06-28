#include<iostream>
#include<cstdlib>
#include<fstream>
using namespace std;
const int MaxVertices = 100;

class node
{
private:
	node *next;
	int vertex;

public:
	node(int num){	vertex=num; next=0;}
	node(){ vertex=0; next=0;}
	friend class Graph;
};

class Graph
{
private:
	int n; // 정점의 개수
	node *graph[MaxVertices];
	bool visited[MaxVertices];
	int front; int rear;
	int que[MaxVertices];
	int arry[MaxVertices][MaxVertices];

public:
	Graph(int num) :n(num) {front = -1; rear = -1;}
	Graph() {n=0;	front = -1;	rear = -1;}
	void initGraph(int num); // num은 정점의 개수
	void insertGraph(int num1, int num2);
	void displayGraph();
	void enqueue(int v);
	int dequeue();
	void queueinit();
	void bfs(int v);
	void dfs(int v);
	void initvisited();
};

void Graph::initvisited()
{
	for(int i=0; i<n; i++)
		visited[i] = false;
}

void Graph::initGraph(int num)
{
	n=num;
	for (int i = 0; i < MaxVertices; i++)
	{
		graph[i] = new node();
		//	graph[i] = NULL;
		visited[i] = false; 
	}
}

void Graph::insertGraph(int u, int v) // u는 정점 v는 연결점
{
	node *anode = new node(v);
	node *p = graph[u];
	node *q = graph[v];

	// 끝의 노드를 찾아 추가 //
	while(p->next !=0)
		p=p->next;
	p->next = anode;

	node *vnode = new node(u);
	while(q->next !=0 )
		q=q->next;
	q->next = vnode;

	
}

void Graph::displayGraph()
{
	node *p;
	for(int i=0; i<n; i++)
	{
		p = graph[i];
		cout << "v" << i << ": ";
		p = p->next; // NULL 출력방지

		while( p != NULL )
		{
			cout << p->vertex;
			p=p->next;
			cout << " ";
		}
		cout << endl;
	}
}

void Graph::enqueue(int v)
{	que[++rear]=v;	}

int Graph::dequeue()
{
	if(front == rear)
	{
		cout << "Deque할 data없음";
		exit(1);
	}

	int num;
	num=que[++front];
	return num;
}

void Graph::queueinit()
{	front=-1; rear=-1;	}

void Graph::bfs(int v)
{
	int temp_f=front;
	int temp_r=rear;

	node *p;
	visited[v]=true;
	enqueue(v);
	cout << "v" << v << " ";

	while(front!=rear)
	{
		v=dequeue();
		for(p=graph[v]->next; p; p=p->next) // 초기값에서 NULL 출력방지 p=graph[v]하면 p는 NULL값
		{
			if(!visited[p->vertex])
			{
				enqueue(p->vertex);
				visited[p->vertex]=true;
				cout << "v" << p->vertex << " ";
			}
		}
	}

	// 큐 , 방문원래 상태로 //
	for (int i = 0; i < MaxVertices; i++)
	{	visited[i] = false;	 }
	front = temp_f;	rear = temp_r;
}

void Graph::dfs(int v)
{
	node *p;
	visited[v] = true;
	cout << "v" << v << " ";
	for(p=graph[v]->next; p!=NULL; p=p->next)
		if(!visited[p->vertex])
			dfs(p->vertex);
}

void main()
{
	// Adjacent Matrix //
	int arry[MaxVertices][MaxVertices] ={ {0,1,1,0,0,0,0,0} , {1,0,0,1,1,0,0,0} , {1,0,0,0,0,1,1,0} , {0,1,0,0,0,0,0,1} ,
	{0,1,0,0,0,0,0,1} , {0,0,1,0,0,0,0,1} , {0,0,1,0,0,0,0,1} , {0,0,0,1,1,1,1,0} };
	
	Graph Gp;
	int select;	int u;	int v;	int n;
	while(1)
	{
		cout << "1.InsertGraph 2.Matrix 3.InsertEdge 4.Display 5.BFS 6.DFS 7.exit : ";
		cin >> select;


		switch(select)
		{
		case 1:
			cout << "정점의 개수: ";
			cin >> n;
			Gp.initGraph(n);
			cout << endl;	break;

		case 2:
			cout << "*****  Adjacent Matrix\n";
			cout << "	 v0	v1	v2	v3	v4	v5	v6	v7\n";
			for(int i=0; i<n; i++)
			{
				cout << "v" << i<< "	 ";
				for(int j=0; j<n; j++)
					cout << arry[i][j] << "\t";
				cout << endl;
			}
			
			for(int i=0; i<n; i++)
			{
				for(int j=i; j<n; j++)
				{
					if(arry[i][j] == 1)
						Gp.insertGraph(i,j);
				}
			}
			cout << endl;	break;
			
		case 3:
			cout << "정  점 선택: ";
			cin >> u;
			cout << "연결점 선택: ";
			cin >> v;
			Gp.insertGraph(u,v);
			cout << endl;	break;

		case 4:
			cout << "D I S P L A Y\n";
			Gp.displayGraph();
			cout << endl;	break;

		case 5:
			cout << "Breadth First search\n";
			cout << "Start vertex: ";
			cin >> n;
			Gp.bfs(n);
			cout << endl;	
			Gp.queueinit();
			cout << endl;	break;

		case 6:
			cout << "Depth First Search\n";
			cout << "Start vertex: ";
			cin >> n;
			Gp.dfs(n);
			cout << endl;
			Gp.initvisited();
			cout << endl;	break;

		case 7:
			exit(1);
		}
	}
}
