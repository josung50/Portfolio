#include"DoubleLL.h"

void Init(List *list)
{
	list->head = 0;
}

void AddFirst(List *list , int key)
{
	// new node�� ���� �� �ʱ�ȭ //
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->data = key;
	temp->next = 0;
	temp->prev = 0;

	if(list->head == NULL) // List�� ��� �ִٸ�
		list->head = temp;
	else
	{
		list->head->prev=temp;
		temp->next=list->head;
		list->head=temp;
	}
}

void AddLast(List *list , int key)
{
	// new node�� ���� �� �ʱ�ȭ //
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->data = key;
	temp->next = 0;
	temp->prev = 0;

	list->p = list->head;

	if(list->head == NULL) // List�� ��� �ִٸ�
		list->head = temp;
	else
	{
		list->p=list->head;
		while(list->p->next!=0) // ������ node�� ã����
			list->p=list->p->next;
		list->p->next=temp;
		temp->prev=list->p;
	}
}

void Insert(List *list, int nth , int key)
{
	int i;
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->data = key;
	temp->next = 0;
	temp->prev = 0;

	if(list->head == 0) // List�� ��������� �Լ� ���� x
	{
		printf("%d is not in the list. " , nth);
		return;
	}

	else
	{
		list->p = list->head;

		while(list->p != 0 && list->p->data != nth) // nth�� ���� ��� ã�� (nth�����͸� ���� ��� �ڿ� ����߰� �ϱ� ���ؼ�)
			list->p = list->p->next;
		
		if(list->p != 0)
		{
			if(list->p->next != 0) //  ������ ��� ��
			{
				temp->next = list->p->next;
				list->p->next->prev = temp;
				temp->prev = list->p;
				list->p->next = temp;

			}
			else // ������ ��� �� ���
			{
				list->p->next = temp;
				temp->prev = list->p;
			}
		}
		else
		{
			printf("%d is not in the list.\n" , nth);
			return;
		}
	}
}

void Delete(List *list , int key)
{
	if(list->head == 0) // List�� empty
	{
		return;
	}

	else
	{
		if(list->head->data == key) // head�� ���� �� ���
		{
			list->head->next->prev = 0;
			list->head = list->head->next;
		}

		else // head ���� ��尡 ���� �� ���
		{
			list->p = list->head;
			list->q = list->p;
			while(list->p != 0 && list->p->data != key) // ������ data�� ���� ��� ã��
			{
				list->q = list->p;
				list->p = list->p->next;
			}

			if(list->p != 0 ) // ã�� ��尡 ������ ��� �� �̶��
			{
				list->q->next = list->p->next;
				if(list->p->next != 0) // ã�� ��尡 ������ �̶��
					list->p->next->prev = list->q;
			}
			else // ��� ��ã��
				printf("%d is not in the list.\n\n" , key);
		}
	}
	free(list->p);
}
void PrintList(List *list)
{
	list->p = list->head;
	if(list->p==0) // List�� ����ִ� (head�� 0)
		printf("List is empty.");

	else
	{
		while(list->p!=0)
		{
			printf("%d ", list->p->data);
			list->p=list->p->next;
		}
	}
}

void PrintfReverse(List *list)
{
	list->p = list->head;
	if(list->head == 0)
		printf("List is empty.");

	else
	{
		while(list->p->next != 0)
			list->p = list->p->next;

		while(list->p!=0)
		{
			printf("%d " , list->p->data);
			list->p = list->p->prev;
		}
	}
}