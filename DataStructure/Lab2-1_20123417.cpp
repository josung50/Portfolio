/********************************************************
*														*
* Name: 조성룡											*
* Student ID : 20123417									*
* Program ID : Lab#2_1									*
* Description: 데이터 파일을 입력받고 내가 찾고자 하는	*
			   하는 수를 입력, 어디에 있는지 찾는 것	*
* Algorithm : 이진탐색으로 입력받은 수의 위치를 찾는다	*
*														*
********************************************************/

#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;
int Binarysearch(int list[], int Num , int left , int right);

void main()
{
	int data[]={10,20,30,40,50,60,70,80,90,100};
	int number;
	int Position;

	cout << "찾고자 하는 수 입력 : ";
	cin >> number;  cout << endl;

	Position = (Binarysearch(data , number , 0 , 9))+1;

	if(Position == 0)
			cout << "Not found" << endl;
	else	
		cout << "position : " << Position << endl;


}

int Binarysearch(int list[], int Num , int left , int right)
{
	int middle;
	while(left<=right)
	{
		middle = (left+right)/2;
		if(Num < list[middle])
			right = middle-1;

		else if(Num == list[middle])
			return middle;

		else left = middle +1;
	}
	return -1;
}