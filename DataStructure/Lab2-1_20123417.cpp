/********************************************************
*														*
* Name: ������											*
* Student ID : 20123417									*
* Program ID : Lab#2_1									*
* Description: ������ ������ �Է¹ް� ���� ã���� �ϴ�	*
			   �ϴ� ���� �Է�, ��� �ִ��� ã�� ��	*
* Algorithm : ����Ž������ �Է¹��� ���� ��ġ�� ã�´�	*
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

	cout << "ã���� �ϴ� �� �Է� : ";
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