#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<string.h>

using namespace std;

struct Node {
	int data;
	char NAME[10];
	Node *next;
};
class List 
{
private:
	Node *head;
public:
	List () { head = 0;}
	void insert(int , char []);
	void append(int , char []);
	bool isEmpty();
	void display();
	void search(int num);
	void deleteNode(int num);
};

void menu(void);

void List::insert(int data , char name[]) // ���� ����
{ 
	Node *temp = new Node;

	temp->data = data;
	strcpy(temp->NAME , name);
	temp->next=0;

	Node *p, *q;

	p=head;
	q=p;

	if (head == 0) head = temp; // Empty �� ���
	else if (temp->data < head->data) 
	{
		temp->next = head;
		head = temp;
	}
	else
	{
		p = head;
		while ((p != 0) && (p->data < temp->data)) 
		{
			q = p;
			p = p->next;
		}
	
		if (p != 0) 
		{
			temp->next = p; q->next = temp;
		}
	
		else
			q->next = temp;
	}
}

void List::append(int data , char name[]) // ������ ����
{
	Node *temp = new Node;
	temp->data = data;
	strcpy(temp->NAME , name);
	temp->next = 0;
	if (head == 0)
		head = temp;
	else 
	{
		Node *ptr = head;
		while (ptr->next != 0)
			ptr = ptr->next;
		ptr->next = temp;
	}
}

bool List::isEmpty()
{
	if (head == 0) return true;
	else return false;
}

void List::display() // ��� ��� ��� //
{
	Node *ptr;
	ptr = head;
	cout << endl;
	cout << "L I S T " << endl;
	while (ptr) 
	{
		cout << ptr->data << " " << ptr->NAME << endl;
		ptr = ptr->next;
	}
}

void List::search(int num)
{
	Node *p;

	if (head != 0) 
	{
		p = head;
		while ( (p != 0) && (p->data != num) ) // data�ӿ��� num�� ��ġ�� ã�� ����
			p = p->next;
		if (p) // data�� ����Ʈ ������ ���� ���� �Ѵٸ�
			cout << "List : "<< p->data << " " << p->NAME << endl;
		else // ����Ʈ�� ���� �� ���� num�� �� ã�� ���
			cout << num << " is not in the list." << endl;
	}

	else	cout << "List is empty\n";
}

void List::deleteNode(int num)
{
	Node *p, *q;
	if (head->data == num)
	{
		p = head;
		head = head->next;
		delete p;
	}

	else 
	{
		p = head;
		while (p != 0 && p->data != num) 
		{
			q = p;
			p = p->next;
		}

		if (p!=0) 
		{
			q->next = p->next;
			delete p;
		}

		else	cout << num << " is not in the list " << endl;;
	
	}
}


void main()
{ 
	List list;
	int select;
	int data;
	char name[10];

	

	while(1)
	{
		menu();
		cin >> select ;

		switch(select)
		{
		case 1:
			cout << "Insert �� Data�� �Է��ϼ��� : " ;
			cin >> data;
			cout << "Insert �� NAME�� �Է��ϼ��� : ";
			cin >> name;
			list.insert(data , name);
			break;
	
		case 2:
			cout << "Append �� Data�� �Է��ϼ��� : ";
			cin >> data;
			cout << "Insert �� NAME�� �Է��ϼ��� : ";
			cin >> name;
			list.append(data , name);
			break;
		case 3:
			cout << "Search �� Data�� �Է��ϼ��� : ";
			cin >> data;
			list.search(data);
			break;
		case 4:
			cout << "Delete �� Data�� �Է��ϼ��� : ";
			cin >> data;
			list.deleteNode(data);
			break;
		case 5:
			list.display();
		}
		cout << endl << endl;
	}
}

void menu(void)
{
	cout << "Menu: 1.Insert		2.Append		3.Search"<<endl;
	cout <<	"Menu: 4.Delete		5.Display	:";
}

