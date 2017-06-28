#include"DoubleLL.h"

void Init(List *list)
{
	list->head = 0;
}

void AddFirst(List *list , int key)
{
	// new node의 생성 및 초기화 //
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->data = key;
	temp->next = 0;
	temp->prev = 0;

	if(list->head == NULL) // List가 비어 있다면
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
	// new node의 생성 및 초기화 //
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->data = key;
	temp->next = 0;
	temp->prev = 0;

	list->p = list->head;

	if(list->head == NULL) // List가 비어 있다면
		list->head = temp;
	else
	{
		list->p=list->head;
		while(list->p->next!=0) // 마지막 node를 찾으면
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

	if(list->head == 0) // List가 비어있으면 함수 실행 x
	{
		printf("%d is not in the list. " , nth);
		return;
	}

	else
	{
		list->p = list->head;

		while(list->p != 0 && list->p->data != nth) // nth를 갖는 노드 찾기 (nth데이터를 갖는 노드 뒤에 노드추가 하기 위해서)
			list->p = list->p->next;
		
		if(list->p != 0)
		{
			if(list->p->next != 0) //  마지막 노드 외
			{
				temp->next = list->p->next;
				list->p->next->prev = temp;
				temp->prev = list->p;
				list->p->next = temp;

			}
			else // 마지막 노드 일 경우
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
	if(list->head == 0) // List가 empty
	{
		return;
	}

	else
	{
		if(list->head->data == key) // head가 삭제 될 경우
		{
			list->head->next->prev = 0;
			list->head = list->head->next;
		}

		else // head 외의 노드가 삭제 될 경우
		{
			list->p = list->head;
			list->q = list->p;
			while(list->p != 0 && list->p->data != key) // 삭제할 data를 지닌 노드 찾기
			{
				list->q = list->p;
				list->p = list->p->next;
			}

			if(list->p != 0 ) // 찾은 노드가 마지막 노드 전 이라면
			{
				list->q->next = list->p->next;
				if(list->p->next != 0) // 찾은 노드가 마지막 이라면
					list->p->next->prev = list->q;
			}
			else // 노드 못찾음
				printf("%d is not in the list.\n\n" , key);
		}
	}
	free(list->p);
}
void PrintList(List *list)
{
	list->p = list->head;
	if(list->p==0) // List가 비어있다 (head가 0)
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