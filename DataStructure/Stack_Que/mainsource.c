#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

void main()
{
	
	Stack sta;
	StackInit(&sta);
	
	Queue que;
	QueueInit(&que);

	int menu;
	int select;
	int word;

	while(1)
	{
		printf("Stack 1¹ø , Queue 2¹ø: ");
		scanf("%d" , &menu);
		printf("\n");
		switch(menu)
		{
		case 1:
				 printf("Push 1 , Pop 2 : ");
				 scanf("%d" , &select);
				 printf("\n");
				 if(select == 1)
				 {
					 printf("Push : ");
					 scanf("%d", &word);	 
					 printf("\n");
					 SPush(&sta , word);
				 }
				 else
				 {
					SPop(&sta);
				 }

				 break;
		case 2:
			printf("Enque 1, Deque 2 : ");
			scanf("%d" , &select);
			printf("\n");
			 if(select == 1)
				{
				 printf("Enque : ");
				 scanf("%d", &word);
				 printf("\n");
				 Enqueue(&que , word);
				}
				else
				{
				 Dequeue(&que);
				}
		}
		
	}
}