/********************************************************
*														*
* Name: ������											*
* Student ID : 20123417									*
* Program ID : Lab#2_2									*
* Description: �Ǻ���ġ ������(n)�� �Է¹ް� ���		*
* Algorithm : �Ǻ���ġ ���� �˰����� ¥�� �Լ��� ����	*
*			  �Է¹��� �� ��ŭ for���� ���� ���		*
*														*
********************************************************/

#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;
int Fibo(int num);

void main()
{
	int num;

	cout << "n�� �� �Է�: ";	cin >> num;
	
	cout << "Fibonacci("<<num<<")=";
	for(int i =0 ; i<num; i++)
		cout << Fibo(i) <<" ";
}

int Fibo(int num)
{
	if(num==0)	
		return 0;
	else if(num == 1)
		return 1;
	else return (Fibo(num-1)+Fibo(num-2));
}