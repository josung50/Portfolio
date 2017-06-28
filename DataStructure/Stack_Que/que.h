#ifndef Que
#define Que

#define QUE_LEN 100
#define TRUE 1
#define FALSE 0

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

#endif