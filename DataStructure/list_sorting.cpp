/************************************************************************************
*																					*
*	국민대학교 컴퓨터 공학부 20123417 조성룡										*
*	프로그램 명: Doubly Linked List Exercise										*
*	설		 명: Num와 Nmae을 입력받아 오름차순으로 정렬하여 LIST에 insert 후		*			 
*				 delete , search , forward , backword 의 기능을 수행한다.			*
*																					*
*   사 용 함 수: insertList - Num과 Name을 입력받은 뒤 List에 오름차순으로 정렬하여	*
*							  삽입한다.												*
*				 deleteList - 입력받은 Num을 List에서 찾아 삭제한다.					*
*				 forwardList - 오름차순으로 List의 항목을 출력한다.					*
*				 backwardList - 내림차순으로 List의 항목을 출력한다.					*
*				 searchList - 입력받은 Num을 List내에서 검색한다.					*
*				 init - List를 생성 후 초기화 하는 함수이다. head를 0으로 만든다.	*
*																					*
************************************************************************************/

#include<iostream>
#include<cstdlib>
#include<cstring>

using namespace std;

/* Node 구성 */
class Node
{
private:
	int data;
	char name[10];
	Node *next;
	Node *prev;
	friend class List;
public:
	Node(int Data , char Name[])
	{
		data = Data;
		strcpy_s(name , Name);
	}
};

/* Doubly List 정의, 내장함수는 위의 Documentation 참조 */
class List
{
private:
	Node *head;

public:
	void insertList(int, char[]);
	void deleteList(int);
	void forwardList();
	void backwardList(); void searchList(int);
	int isEmpty(); 	void init();
};

void List::init()
{
	head =0;
}

int List::isEmpty()
{
	if(head == 0)	return 1;
	else return 0;
}


//***************************************알고리즘***************************************//
/*	Data를 입력받는다. 입력받은 Data를 List->data와 비교한다.							*/
/*	이 때, List가 비어있으며 추가된 노드가 head가 된다.									*/
/*	비어있지 않다면, 기존 data와 비교 후, 입력받은 data보다 더 큰 값이 나올 때 까지		*/
/*	노드를 찾고 이를 q와 p사이라고 지정한다.											*/
/*	q와 p 사이에 노드를 삽입하고 next와 prev를 적절하게 링크를 시켜준다.				*/
//***************************************알고리즘***************************************//
void List::insertList(int Data, char Name[]) // 숫자의 경우(오름차순)
{
	Node *temp = new Node(Data, Name);
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
			cout << p->data << " " << p->name << endl;
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
			cout << p->data << " " << p->name << endl;
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

void main()
{
	List list;
	list.init();
	int select;
	char NAME[10];
	int NUMBER;
	while(1)
	{
		cout << "1.insert 2.delete 3.backward 4.forward 5.search : ";
		cin >> select;

		switch(select)
		{
		case 1:
			cout << "insert Number: ";
			cin >> NUMBER;
			cout << "insert Name: ";
			cin >> NAME;
			list.insertList(NUMBER , NAME);
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
		}
	}
}
