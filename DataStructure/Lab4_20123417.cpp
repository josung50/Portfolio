#include <iostream>
#include< fstream>
#include <cstring>

using namespace std;

const int stackSize = 100; // ����ũ��
char print[100]; // input�� ���� ����
char stack[stackSize];  //����
int top;  // ������ top(���ذ�=-1)
int printcount=0;
int Gcount=0;
int op1=0 ,op2=0;



/********************���� ADT********************/
void create_stack()  //���ø����
{ 
	top = -1; //ó���� �ƹ��͵�����
}
int isFull()  //�������� 1 �ƴϸ� 0����ȯ
{
	if (top == stackSize - 1) return 1; //top�� ���ÿ� �ǲ���⿡������ ->full!
	else return 0; 
}
int isEmpty() //������� 1 �ƴϸ� 0
{
	if (top == -1) return 1;
	else return 0; 
}
void push(char num) //���ڸ� Ǫ��(�ִ�) �Լ�
{
	++top; //top�� �־��ְ� (��ó�� top�� -1�̴ϱ� ù��°�������� top=0 2��°������ 1...2....3=full
	stack[top] = num; //���� ���ڸ� �ش� top�� ��ġ��Ŵ
}
int pop() //top�ϳ��� �����ϴ� (�������� �Է��� ���� ����)�Լ�
{ 
	return (stack[top--]); 
} 
void displayStack() //���� �׿��� ���� �����ִ� �Լ�
{ 
	int sp; //������ �����ֱ����� ���� sp����
	if (isEmpty() )
		cout << "Stack is empty!" ;

	else
	{
		sp = top;
		while (sp != -1)
		{
			cout << stack[sp];
			--sp; //���������� �ٿ������� 
		}
		cout << endl;
	}
} //���ú����ֱ�
/********************���� ADT********************/

void main()
{
	ifstream instream;
	instream.open("input.txt");
	int countnum;
	instream>>countnum;

	for(int i=0;i<countnum; i++)
	{
		char num[100]; 
		instream>>num;
		create_stack();



		int len = strlen(num); // �Է¹��� ���ڿ��� ����
		int mid=len/2;
		int count=0;

		if(len%2==0)
		{
			for(int m=0 ;m<len;m++)
			{
				if(m<mid)
				{push(num[m]);}
				else
				{
					if(stack[top]==num[m])
						pop();
				}
			}
		}
		else
		{
			for(int i=0 ;i<len;i++)
			{
				if(i<mid)
				{push(num[i]);}

				else if(i==mid)
					continue;

				else
				{
					if(stack[top]==num[i])
						pop();
				}
			}
		}
		
		for(int k=0 ;k<len ;k++)
			cout<<num[k];

		if(isEmpty())
			cout<<"      "<<"PALINDROME";

		else
			cout<<"      "<<"NoT PALINDROME";
		cout<<endl;
	}
}