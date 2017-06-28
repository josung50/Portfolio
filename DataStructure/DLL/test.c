#include"DoubleLL.h"

void main()
{
	List list;
	int select;
	int data;
	int nth;
	Init(&list);
	

	while(1)
	{
		printf("1.AddFirst 2.AddLast 3.Insert 4.Delete 5.PrintReverse : ");
		scanf("%d",&select);

		switch(select)
		{
			case 1: // AddFirst
				printf("AddFirst list : ");
				scanf("%d" , &data);
				AddFirst(&list , data);
				PrintList(&list);
				printf("\n\n");
				break;

			case 2: // AddLast
				printf("AddLast list : ");
				scanf("%d" , &data);
				AddLast(&list , data);
				PrintList(&list);
				printf("\n\n");
				break;

			case 3:
				printf("Insert list\n");
				printf("Add list : ");
				scanf("%d" , &data);
				
				printf("After list : ");
				scanf("%d" , &nth);

				Insert(&list , nth , data);
				PrintList(&list);
				printf("\n\n");
				break;

			case 4:
				printf("Delete list : ");
				scanf("%d" , &data);
				Delete(&list , data);
				PrintList(&list);
				printf("\n\n");
				break;

			case 5:
				printf("Reverse List\n");
				PrintfReverse(&list);
				printf("\n\n");
				break;
		}
	}
}

