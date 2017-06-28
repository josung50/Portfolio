/********************************************************
*														*
* Name: 조성룡											*
* Student ID : 20123417									*
* Program ID : Lab#2_2									*
* Description: 피보나치 수열값(n)을 입력받고 출력		*
* Algorithm : 피보나치 수열 알고리즘을 짜고 함수에 대입	*
*			  입력받은 수 만큼 for문을 돌려 출력		*
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

	cout << "n의 값 입력: ";	cin >> num;
	
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