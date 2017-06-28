/************************************************************************************
*																					*
*	국민대학교 컴퓨터 공학부 20123417 조성룡										*
*	프로그램 명: MAX HEAP implementation											*
*	설		 명: 데이터를 입력받아 HEAP의 내용을 출력한다.							*
*																					*
*   사 용 함 수: insert_maxheap - Data를 입력받아 내림차순 정렬삽입한다.				*
*									root아래로 트리가 만들어진다.					*
*				 delete_maxheap - 가장 큰 Data 삭제 ( root 삭제 )					*
*				 print_maxheap - MAXHEAP을 root부터 출력한다.						*
*				 HEAP_FULL - HEAP이 풀인지를 검사한다.								*
*				 HEAP_EMPTY - HEAP이 비었는지를 검사한다.							*
*				 creat_maxheap - 입력데이터 8 6 4 2 5 3을 프로그램내에 생성한다.		*
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