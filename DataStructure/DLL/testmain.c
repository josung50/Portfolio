#include"DoubleLL.h"

void main()
{
	List list; // ����Ʈ ����
	Create(&list); // �ʱ�ȭ
	int select;
	int data;

	while(1)
	{
		printf("1.AddFirst 2.AddLast 3.Insert 4.Delete 5.Print 6.PrintReverse : ");
		select = getch();

		switch(select)
		{
			case 1: // AddFirst
				printf("Data : %d\n" , &data);
				AddFirst(&list , data);
			case 5: // printf
				Print(&list);
		}
	}
}

