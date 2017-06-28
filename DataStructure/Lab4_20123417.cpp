#include <iostream>
#include< fstream>
#include <cstring>

using namespace std;

const int stackSize = 100; // 스택크기
char print[100]; // input의 문자 저장
char stack[stackSize];  //스택
int top;  // 스택의 top(기준값=-1)
int printcount=0;
int Gcount=0;
int op1=0 ,op2=0;



/********************스택 ADT********************/
void create_stack()  //스택만들기
{ 
	top = -1; //처음엔 아무것도없다
}
int isFull()  //꽉찻으면 1 아니면 0을반환
{
	if (top == stackSize - 1) return 1; //top이 스택에 맨꼭대기에있을때 ->full!
	else return 0; 
}
int isEmpty() //비었으면 1 아니면 0
{
	if (top == -1) return 1;
	else return 0; 
}
void push(char num) //숫자를 푸쉬(넣는) 함수
{
	++top; //top을 넣어주고 (맨처음 top은 -1이니까 첫번째수가들어가면 top=0 2번째수들어가면 1...2....3=full
	stack[top] = num; //넣은 숫자를 해당 top에 위치시킴
}
int pop() //top하나를 제거하는 (마지막에 입력한 수를 빼는)함수
{ 
	return (stack[top--]); 
} 
void displayStack() //현재 쌓여진 수를 보여주는 함수
{ 
	int sp; //스택을 보여주기위해 비교할 sp선언
	if (isEmpty() )
		cout << "Stack is empty!" ;

	else
	{
		sp = top;
		while (sp != -1)
		{
			cout << stack[sp];
			--sp; //위에서부터 줄여나간다 
		}
		cout << endl;
	}
} //스택보여주기
/********************스택 ADT********************/

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



		int len = strlen(num); // 입력받은 문자열의 길이
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