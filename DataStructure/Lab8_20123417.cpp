
#include<iostream>
#include<cstdlib>
#include<cstring>

using namespace std;

/* Node 구성 */
class Node
{
private:
	int data;
	Node *next;
	Node *prev;
	friend class List;
public:
	Node(int Data)
	{
		data = Data;
	}
};

/* Doubly List 정의, 내장함수는 위의 Documentation 참조 */
class List
{
private:
	Node *head;

public:
	void insertList(int);
	void deleteList(int);
	void forwardList();
	void backwardList(); void searchList(int);
	int isEmpty(); 	void init();
	void insert_before(int n , int data);
	void insert_after(int n , int data);
	void findn(int n);
};

void List::init()
{
	head =0;
}

void List::findn(int n)
{
	Node *p; Node *q;
	p=head;
	q=p;
	for(int i=1; i<n; i++)
	{
		q=p; p=p->next;
	}
	cout << "Find " << n << "th " << p->data << endl;
}

int List::isEmpty()
{
	if(head == 0)	return 1;
	else return 0;
}



void List::insertList(int Data) // 숫자의 경우(오름차순)
{
	Node *temp = new Node(Data);
	temp->next=0;
	temp->prev=0;

	Node *p, *q;
	if (head == 0) // 첫노드일때
		head = temp;

	else if (temp->data < head->data) 
	{ //head node 앞에 삽입
		temp->next = head;
		head->prev = temp;
		head = temp;
	}

	else 
	{ // 가운데 삽입
		p = head;
		q = head;
		while ((p != 0) && (p->data < temp->data)) 
		{ //이동
			q = p;
			p = p->next;
		}

		if (p != 0)
		{ // 중간에 삽입
			temp->next = p;
			temp->prev = q;
			q->next = temp;
			p->prev = temp;
		}

		else
		{ // temp가 큰경우
			q->next = temp;
			temp->prev = q;
		}
	}
}

void List::deleteList(int key)
{
	Node *p, *q;

	if (head ==0) 
	{
		cout << "Is empty " << endl;
		exit(1);
	}

	if (head->data == key)
	{ // 삭제될 노드가 head 일 경우	
		if(head->next == 0) // 노드가 한개있는 경우의 delete
		{
			head = 0;
			return ;
		}
		p = head;
		head = head->next;
		head->prev = 0;
		delete p;
	}

	else
	{ // 가운데 노드가 삭제될 경우
		q = head;
		p = head;
		while (p != 0 && (p->data != key) ) 
		{
			q = p;
			p = p->next;
		}

		if (p != 0) 
		{
			q->next = p->next;
			if (p->next != 0)
				p->next->prev = q;
			delete p;
		}

		else	cout << key << " is not in the list" << endl;
	}
	
}

void List::forwardList()
{
	if (!isEmpty()) 
	{
		Node *p = head;
		cout << "----- Forward List -----\n";
		while (p!= 0)
		{
			cout << p->data << endl;
			p = p->next;
		}
		cout << endl;
	}

	else
		cout << "List is empty!\n\n";
}

void List::backwardList()
{
	if (!isEmpty()) 
	{
		Node *p = head;
		while (p->next != 0)
			p = p->next;

		cout << "----- Backward List -----\n";
		while (p!= 0) 
		{
			cout << p->data << endl;
			p = p->prev;
		}
		cout << endl; 
	}
	else
		cout << "List is empty!\n\n";
}

void List::searchList(int key)
{
	if (!isEmpty()) 
	{
		Node *p = head;
		while (p != 0 && p->data != key) 
			p = p->next;
		if (p != 0)
			cout << p->data << " is in the list\n";
		else
			cout << key << " is not int the list\n";
	}
	else
	cout << "List is empty!\n";
}

void List::insert_before(int n , int data)
{
	Node* p; Node* q;
	Node *temp = new Node(data);
	p=head;
	q=p;

	temp->data = data;
	temp->prev = 0; temp->next = 0;

	if( head == 0 )
		head = temp;
	else
	{
		for(int i=1; i<n; i++)
		{
			q=p; p=p->next;
		}
		q->next = temp;
		temp->next = p;
		p->prev = temp;
		temp->prev = q;
	}
}

void List::insert_after(int n , int data)
{
	Node* p; Node* q;
	Node* temp = new Node(data);
	temp->data = data;
	temp->prev = 0; temp->next = 0;
	p=head;
	q=p;

	if(head == 0)
		head = temp;
	else
	{

		for(int i=1; i<n; i++)
		{
			q=p; p=p->next;
		}
		temp->next = p->next;
		p->next->prev = temp;
		p->next = temp;
		temp->prev = p;
	}
	
}


void main()
{
	List list;
	list.init();
	int select;
	char NAME[10];
	int NUMBER;
	int nth;
	while(1)
	{
		cout << "1.insert 2.delete 3.back 4.for 5.search 6.insertafter 7.insertbefore ";
		cout << "8.find n node : " ;
		cin >> select;

		switch(select)
		{
		case 1:
			cout << "insert Number: ";
			cin >> NUMBER;
			list.insertList(NUMBER);
			cout << endl ;
			break;
		case 2:
			cout << "delete Number: ";
			cin >> NUMBER;
			list.deleteList(NUMBER);
			cout << endl;
			break;
		case 3:
			list.backwardList();
			break;
		case 4:
			list.forwardList();
			break;
		case 5:
			cout << "search Number : ";
			cin >> NUMBER;
			list.searchList(NUMBER);
			cout << endl;
			break;
		case 6:
			cout << "insert_after Number : ";
			cin >> NUMBER;
			cout << "select Node : ";
			cin >> nth;
			list.insert_after(nth , NUMBER);
			cout << endl;
			break;
		case 7:
			cout << "insert_before Number : ";
			cin >> NUMBER;
			cout << "select Node : ";
			cin >> nth;
			list.insert_before(nth , NUMBER);
			cout << endl;
			break;
		case 8:
			cout << "select n node : ";
			cin >> nth;
			list.findn(nth);
			cout << endl;
			break;
		}
	}
}