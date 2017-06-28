#ifndef STACK
#define STACK

#define TRUE 1
#define FALSE 0
#define STACK_LEN 100
#define QUE_LEN 100

typedef int Data;

typedef struct
{
	int front;
	int rear;
	Data queArr[QUE_LEN];
} CQue;

typedef CQue Queue;

void QueueInit(Queue* pq);
int QIsEmpty(Queue* pq);

void Enqueue(Queue* pq, Data data);
Data Dequeue(Queue* pq);
Data QPeek(Queue* pq);


typedef int Data;

typedef struct
{
	Data stack[STACK_LEN];
	int topIndex;
}ArrayStack;

typedef ArrayStack Stack;

void StackInit(Stack* pstack); // ������ �ʱ�ȭ
int SIsEmpty(Stack* pstack); // ������ ����ִ��� Ȯ��

void SPush(Stack* pstack, Data data);
Data SPop(Stack* pstack);
Data SPeek(Stack* pstack);

#endif