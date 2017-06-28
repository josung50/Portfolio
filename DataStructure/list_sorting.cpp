/************************************************************************************
*																					*
*	���δ��б� ��ǻ�� ���к� 20123417 ������										*
*	���α׷� ��: Doubly Linked List Exercise										*
*	��		 ��: Num�� Nmae�� �Է¹޾� ������������ �����Ͽ� LIST�� insert ��		*			 
*				 delete , search , forward , backword �� ����� �����Ѵ�.			*
*																					*
*   �� �� �� ��: insertList - Num�� Name�� �Է¹��� �� List�� ������������ �����Ͽ�	*
*							  �����Ѵ�.												*
*				 deleteList - �Է¹��� Num�� List���� ã�� �����Ѵ�.					*
*				 forwardList - ������������ List�� �׸��� ����Ѵ�.					*
*				 backwardList - ������������ List�� �׸��� ����Ѵ�.					*
*				 searchList - �Է¹��� Num�� List������ �˻��Ѵ�.					*
*				 init - List�� ���� �� �ʱ�ȭ �ϴ� �Լ��̴�. head�� 0���� �����.	*
*																					*
************************************************************************************/

#include<iostream>
#include<cstdlib>
#include<cstring>

using namespace std;

/* Node ���� */
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

/* Doubly List ����, �����Լ��� ���� Documentation ���� */
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


//***************************************�˰���***************************************//
/*	Data�� �Է¹޴´�. �Է¹��� Data�� List->data�� ���Ѵ�.							*/
/*	�� ��, List�� ��������� �߰��� ��尡 head�� �ȴ�.									*/
/*	������� �ʴٸ�, ���� data�� �� ��, �Է¹��� data���� �� ū ���� ���� �� ����		*/
/*	��带 ã�� �̸� q�� p���̶�� �����Ѵ�.											*/
/*	q�� p ���̿� ��带 �����ϰ� next�� prev�� �����ϰ� ��ũ�� �����ش�.				*/
//***************************************�˰���***************************************//
void List::insertList(int Data, char Name[]) // ������ ���(��������)
{
	Node *temp = new Node(Data, Name);
	temp->next=0;
	temp->prev=0;

	Node *p, *q;
	if (head == 0) // ù����϶�
		head = temp;

	else if (temp->data < head->data) 
	{ //head node �տ� ����
		temp->next = head;
		head->prev = temp;
		head = temp;
	}

	else 
	{ // ��� ����
		p = head;
		q = head;
		while ((p != 0) && (p->data < temp->data)) 
		{ //�̵�
			q = p;
			p = p->next;
		}

		if (p != 0)
		{ // �߰��� ����
			temp->next = p;
			temp->prev = q;
			q->next = temp;
			p->prev = temp;
		}

		else
		{ // temp�� ū���
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
	{ // ������ ��尡 head �� ���	
		if(head->next == 0) // ��尡 �Ѱ��ִ� ����� delete
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
	{ // ��� ��尡 ������ ���
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
