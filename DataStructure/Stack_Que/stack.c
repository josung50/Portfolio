#include<stdio.h>
#include<stdlib.h>
#include"stack.h"


void StackInit(Stack* pstack)
{
	pstack->topIndex = -1;
}

int SIsEmpty(Stack* pstack)
{
	if(pstack->topIndex==-1)
		return TRUE;
	else return FALSE;
}

void SPush(Stack* pstack , Data data)
{
	pstack->topIndex += 1;
	pstack->stack[pstack->topIndex] = data;
}

Data SPop(Stack* pstack)
{
	int rIdx;

	if(SIsEmpty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}

	rIdx = pstack->topIndex;
	return pstack->stack[rIdx];
}

Data SPeek(Stack* pstack)
{
	if(SIsEmpty(pstack))
	{
		printf("Stack Meomory Error!");
		exit(-1);
	}

	return pstack->stack[pstack->topIndex];
}

void QueueInit(Queue *pq)
{
	pq->front = 0;
	pq->rear = 0;
}

int QIsEmpty(Queue* pq)
{
	if(pq->front == pq->rear)
		return TRUE;
	else return FALSE;
}

int NextPosIdx(int pos)
{
	if(pos == QUE_LEN-1) return 0;
	else	return pos+1;
}

void Enqueue(Queue* pq, Data data)
{
	if(NextPosIdx(pq->rear) == pq->front)
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	pq->rear = NextPosIdx(pq->rear);
	pq->queArr[pq->front] = data;
}

Data Dequeue(Queue* pq)
{
	if(QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	pq->front = NextPosIdx(pq->front);
	return pq->queArr[pq->front];
}

Data QPeek(Queue* pq)
{
	if(QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	return pq->queArr[NextPosIdx(pq->front)];
}
