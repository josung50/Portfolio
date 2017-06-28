/************************************************************************************
*																					*
*	���δ��б� ��ǻ�� ���к� 20123417 ������										*
*	���α׷� ��: MAX HEAP implementation											*
*	��		 ��: �����͸� �Է¹޾� HEAP�� ������ ����Ѵ�.							*
*																					*
*   �� �� �� ��: insert_maxheap - Data�� �Է¹޾� �������� ���Ļ����Ѵ�.				*
*									root�Ʒ��� Ʈ���� ���������.					*
*				 delete_maxheap - ���� ū Data ���� ( root ���� )					*
*				 print_maxheap - MAXHEAP�� root���� ����Ѵ�.						*
*				 HEAP_FULL - HEAP�� Ǯ������ �˻��Ѵ�.								*
*				 HEAP_EMPTY - HEAP�� ��������� �˻��Ѵ�.							*
*				 creat_maxheap - �Էµ����� 8 6 4 2 5 3�� ���α׷����� �����Ѵ�.		*
*																					*
************************************************************************************/

#include <iostream>
#include <cstdlib>
#include "MAXHEAP.h"

using namespace std;

void main()
{
	element item;
	heaptype heaptype;
	heaptype.n = 0;

	while(1)
	{
		int input;

		cout<<"1.Insert  2.Delete  3.Empty  4.Full  5.Quit  6.Creat: ";
		cin>>input;

		switch(input)
		{
			case 1:
				if(!heaptype.HEAP_FULL(&heaptype))
				{
				cout<<"Input Insert Number : ";
				cin>>item.key;
				heaptype.insert_maxheap(&item, &heaptype);
				heaptype.print_maxheap(&heaptype);
				cout << endl << endl;
				}
				else
					cout<<"Heap is Full!!"<<endl;
				break;
			case 2:
				if(!heaptype.HEAP_EMPTY(&heaptype))
				{
				heaptype.delete_maxheap(&heaptype);
				cout<<"Delete"<<endl;
				heaptype.print_maxheap(&heaptype);
				cout <<endl<<endl;
				}
				else
					cout<<"Heap is Empty!!"<<endl<<endl;
				break;
			case 3:
				if(heaptype.HEAP_EMPTY(&heaptype))
				{
					cout<<"Heap is Empty!!"<<endl<<endl;
				}
				else
					cout<<"Heap is not Empty!!"<<endl<<endl;
				break;
			case 4:
				if(heaptype.HEAP_FULL(&heaptype))
				{
					cout<<"Heap is Full!!"<<endl<<endl;
				}
				else
					cout<<"Heap is not Full!!"<<endl<<endl;
				break;
			case 5:
				exit(1);
				break;
			case 6:
				cout<<"Creat 8 6 4 2 5 3\n";
				heaptype.creat_maxheap(&heaptype);
				heaptype.print_maxheap(&heaptype);
				cout <<endl<<endl;
		}
	}
}