#ifndef __MAXHEAP_H__
#define __MAXHEAP_H__

#define MAX_ELEMENTS 9 

class element
{
public:
	int key; 
};

class heaptype
{
public:
	element heap[MAX_ELEMENTS]; 
	int n; // 현재 힙의 크기
	void creat_maxheap(heaptype *h);
	void insert_maxheap(element *item, heaptype *h); 
	element delete_maxheap(heaptype *h); 
	void print_maxheap(heaptype *h);
	bool HEAP_FULL(heaptype *h);
	bool HEAP_EMPTY(heaptype *h); 
};


#endif