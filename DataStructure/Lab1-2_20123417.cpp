/********************************************************
*														*
* Name: 조성룡											*
* Student ID : 20123417									*
* Program ID : Lab#1_2									*
* Description: 데이터 파일에서 한 단어씩 읽고			*
*			   단어의 개수를 출력하는 프로그램			*
* Algorithm : 배열을 초기화 한 후(NULL값)으로 데이터를	* 
*			  배열에 저장, 저장된 배열에서 단어의 수를	*
*			  Counting 하고 배열 i행 0열의 값 = NULL	*
*			  이면 Counting종료							*
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


	// lab1.dat 불러오기
	if(inStream.fail())
	{
		cerr << "Infile 'lab1.dat' opening failed" << endl;
		exit(1);
	}

	
	char Word[100][100];
	sizeof (Word);
	Null_arry(Word , inStream);
	Count(Word);

	

	inStream.close(); // lab1.dat 닫기	
}



// Null_arry : 배열을 NULL로 초기화 , 데이터를 배열에 저장시키는 함수
void Null_arry(char arry[100][100] , ifstream &inStream)
{
	for(int i=0; i<100; i++)
		for(int j=0; j<100; j++)
			arry[i][j] = NULL;

	for(int i=0; i<100; i++)
		inStream >> arry[i];
}



// Count : 단어를 출력후 개행 , 단어의 갯수를 파악하는 함수
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
