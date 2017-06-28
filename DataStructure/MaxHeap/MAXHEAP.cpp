#include <iostream>
#include <cstdlib>
#include "MAXHEAP.h"

using namespace std;

bool heaptype::HEAP_FULL(heaptype *h)
{
	if(h->n == MAX_ELEMENTS-1) 
		return true;
	else
		return false;
}

bool heaptype::HEAP_EMPTY(heaptype *h)
{
	if(h->n <= 0)
		return true;
	else
		return false;
}

// 8,6,4,2,5,3을 가지는 heap을 만든다 //
void heaptype::creat_maxheap(heaptype *h)
{
	element temp_item[6] = {8,6,4,2,5,3};
	for(int i=0; i<6; i++)
	{
		insert_maxheap(&temp_item[i] , h);
	}
}

void heaptype::insert_maxheap(element *item, heaptype *h)
{
	int i;

	i = ++h->n;
	
	while ((i!=1) && (item->key > h->heap[i/2].key)) 
	{ 
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = *item;
}

element heaptype::delete_maxheap(heaptype *h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[h->n--];
	parent = 1;
	child = 2;

	while (child <= h->n)
	{
		if (child < h->n && h->heap[child].key < h->heap[child+1].key)
			child++; 
		if (temp.key >= h->heap[child].key) 
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item; 
}

void heaptype::print_maxheap(heaptype *h)
{
	for(int i=1; i<=h->n; i++)
	{
		cout<<h->heap[i].key<<" ";
	}
}