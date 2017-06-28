#include<iostream>
#include<cstdlib>
#include<conio.h>

using namespace std;

class node
{
private:
	char data;
	node* next;
	friend class stack;
	friend class queue;
};

class stack
{
private:
	node *head;
public:
	void push(char data);
	char pop();
	int empty(void);
	void init();
};

class queue
{
private:
	node *front;
	node *rear;
public:
	void enqueue(char data);
	char dequeue();
	int empty(void);
	void queue::search(char data);
	void init();
};

int stack::empty(void)
{
	if(head == 0)
	{
		cout << "Is empty"<< endl;
		return 1;
	}
	else return 0;
}
void stack::push(char data)
{
	node* temp = new node;
	temp->data = data;
	temp->next = 0;

	node* p = head;
	
	if(head ==0)
		head = temp;
	else
	{
		temp->next = head;
		head = temp;
	}
}
char stack::pop()
{
	node *p; char data;

	if( head == 0)
	{
		cout << "Is empty" << endl;
		return NULL;
	}
	
	else
	{
		data = head->data;
		p = head;
		head = head->next;
		delete p;
		return data; 
	}
}
void stack::init()
{
	head = 0;
}

void queue::enqueue(char data)
{
	node *temp = new node;
	temp->data =data;
	temp->next =0;
	if (front == 0) 
	{ /* 큐가 empty인경우 */
		front = temp;
		rear = temp;
	}
	else 
	{
		rear->next = temp;
		rear = temp;
	}
}
char queue::dequeue()
{
	node *p; char data;

	if (front == 0)
	{
		cout << "Is empty" << endl;
		front = 0; rear = 0; 
		return NULL;
	}
	else 
	{
		p = front;
		data = front->data;
		front = front->next;
		delete p;
		return data;
		if(front == rear)
		{
			front = 0;
			rear = 0;
		}
		
	}
}
int queue::empty()
{
	if (front == 0) return 1;
	else return 0;
}
void queue::search(char data)
{
	node *p; node *q;
	if( empty() ) 
	{
		cout << "Is empty" << endl << endl;
		return;
	}

	else
	{
		if( front->data == data)
			cout << "Data is in the list" << endl;
		else
		{
			while(p!=0 && p->data != data)
			{
				q=p;
				p=p->next;
			}
			if(p!=0)
				cout << "Data is in the list" << endl << endl;
			else
				cout << "Data is not in the list" << endl << endl;
		}
	}
}
void queue::init()
{
	front = 0;
	rear = 0;
}

void main()
{
	stack sta;
	queue que;
	sta.init();
	que.init();
	int select;
	char data;

	while(1)
	{
		cout << "1.Push 2.Pop 3.Enque 4.Deque 5.SearchQue : "; 
		cin >> select;

		switch(select)
		{
		case 1:
			cout << "Push data: " ;
			cin >> data ;
			sta.push(data);
			cout << endl;
			break;
		case 2:
			cout << "Pop data: " << sta.pop();
			cout << endl << endl;;
			break;
		case 3:
			cout << "Enque data: " ;
			cin >> data;
			que.enqueue(data);
			cout << endl;
			break;
		case 4:
			cout << "Deque data: " << que.dequeue();
			cout << endl << endl;
			break;
		case 5:
			cout << "SearchQue data: ";
			cin >> data;
			que.search(data);
		}

	}

}