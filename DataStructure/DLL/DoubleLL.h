#ifndef _DOUBLELL_H_
#define _DOUBLELL_H_

#include<stdlib.h>
#include<stdio.h>
#include"DoubleLL.h"

typedef struct _node
{
	int data;
	struct _node *next;
	struct _node *prev;
}Node;

typedef struct _Double
{
	Node *head;
	Node *p;
	Node *q;
}List;

void Init(List *list);
void AddFirst(List *list , int key);
void AddLast(List *list , int key);
void Insert(List *list, int nth , int key);
void Delete(List *list , int key);
void PrintList(List *list);
void PrintfReverse(List *list);

#endif