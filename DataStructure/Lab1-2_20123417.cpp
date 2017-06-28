/********************************************************
*														*
* Name: ������											*
* Student ID : 20123417									*
* Program ID : Lab#1_2									*
* Description: ������ ���Ͽ��� �� �ܾ �а�			*
*			   �ܾ��� ������ ����ϴ� ���α׷�			*
* Algorithm : �迭�� �ʱ�ȭ �� ��(NULL��)���� �����͸�	* 
*			  �迭�� ����, ����� �迭���� �ܾ��� ����	*
*			  Counting �ϰ� �迭 i�� 0���� �� = NULL	*
*			  �̸� Counting����							*
*														*
********************************************************/

#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;
void Count(char arry[100][100]);
void Null_arry(char arry[100][100] , ifstream &inStream);


void main()
{
	ifstream inStream;
	inStream.open("lab1.dat");


	// lab1.dat �ҷ�����
	if(inStream.fail())
	{
		cerr << "Infile 'lab1.dat' opening failed" << endl;
		exit(1);
	}

	
	char Word[100][100];
	sizeof (Word);
	Null_arry(Word , inStream);
	Count(Word);

	

	inStream.close(); // lab1.dat �ݱ�	
}



// Null_arry : �迭�� NULL�� �ʱ�ȭ , �����͸� �迭�� �����Ű�� �Լ�
void Null_arry(char arry[100][100] , ifstream &inStream)
{
	for(int i=0; i<100; i++)
		for(int j=0; j<100; j++)
			arry[i][j] = NULL;

	for(int i=0; i<100; i++)
		inStream >> arry[i];
}



// Count : �ܾ ����� ���� , �ܾ��� ������ �ľ��ϴ� �Լ�
void Count(char arry[100][100])
{
	int count = 0;

	for(int i=0; i<100; i++)
	{
		if(arry[i][0] != NULL)
		{
			count++;
			cout << arry[i]<< endl;
		}
	}
			

	cout << "The number of words = " << count << endl; 
}
