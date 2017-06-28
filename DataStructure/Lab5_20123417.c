#include <stdio.h>
#include <stdlib.h>
#include<conio.h>


#define EMPTY -1
#define MAX 2
#define TRUE 1
#define FALSE 0

#define QUE_LEN 3
typedef int Data;

typedef struct _cQueue
{
	int front;
	int rear;
	Data queArr[QUE_LEN];
} CQueue;

typedef CQueue Queue;

void QueueInit(Queue *pq);
int QIsEmpty(Queue *pq);

void Enqueue(Queue *pq, Data data);
Data Dequeue(Queue *pq);
Data QPeek(Queue *pq);


char stack[MAX];
int top = -1;

void Menu();
void Push(char data);
int Pop();
int Peek();
int isEmpty();
int isFull();

int main(){
    int sel;
    char data;
	Queue q;
	QueueInit(&q);

    while(1){
        Menu();
        scanf("%d", &sel);

        switch(sel){
            case 1 :
                printf("�����͸� �Է��ϼ��� : ");
                data = getch();
				printf("%c \n" , data);
                Push(data);
                break;
            case 2 :
				if(isEmpty()==0)
					printf("Pop�� ����? : %c \n", Pop());
				else if(isEmpty()==1)
					printf("������ ��� �ֽ��ϴ�.\n");
                break;
            case 3 :
				if(isEmpty()==0)
					printf("Peek�� ����? : %c ", Peek());
				else if(isEmpty()==1)
					printf("������ ��� �ֽ��ϴ�.\n");
                break;
			case 4 :
				printf("�����͸� �Է��ϼ��� : ");
				data = getch();
				printf("%c \n" , data);
				Enqueue(&q , data);
				break;
			case 5 :
				if(QIsEmpty(&q)==0)
					printf("Deque�� ����? : %c \n", Dequeue(&q));
				else if(QIsEmpty(&q)==1)
					printf("ť�� ������ϴ�. \n");
				break;

      return ;
            default :
                printf("�߸��Է� �ϼ̽��ϴ�. ");
                continue;
		}
	}
}


void Menu(){
    printf("1. Push ");
    printf("2. Pop ");
    printf("3. Peek ");
	printf("4. Enque ");
	printf("5. Deque ");    
    printf(" ");
    printf("�޴��� �����ϼ��� : ");
}

void Push(char data){
    if(!isFull())
        stack[++top] = data;
    else{
        printf("������ �� á���ϴ�.\n");
    }
}

int Pop(){
    if(!isEmpty())
	{
        return stack[top--];
	}
    printf("������ ��� �ֽ��ϴ�.\n");
}

int Peek(){
    if(!isEmpty())
        return stack[top];
    printf("������ ��� �ֽ��ϴ�.\n");
}

// 1�̸� EMPTY
int isEmpty(){
    if( top == EMPTY )
        return 1;
    return 0;
}

// 1�̸� FULL
int isFull(){
    if( top == MAX - 1 )
        return 1;
    return 0;
}

////////////////////////////////////

void QueueInit(Queue *pq)
{
	pq->front = -1;
	pq ->rear = -1;
}

int QIsEmpty(Queue *pq)
{
	if(pq->front == pq->rear)
		return TRUE;
	else 
		return FALSE;
}

void Enqueue(Queue *pq, Data data)
{
	if(pq->rear == QUE_LEN)
	{
		printf("ť�� �� á���ϴ�. \n");
	}

	pq->rear += 1;
	pq->queArr[pq->rear] = data;
}

Data Dequeue(Queue *pq)
{
	if(QIsEmpty(pq))
	{
		printf("ť�� ������ϴ�. \n");
	}
	pq->front += 1;
	return pq->queArr[pq->front];
	
}