/************************************************************************************
*																					*
*	국민대학교 컴퓨터 공학부 20123417 조성룡										*
*	프로그램 명: 매직스퀘어															*
*	설		 명: 사각형의 크기를 입력 받아 행, 열, 대각선의 합이 같은				*
*				 사각형을 출력 한다.												*
*	알 고 리 즘: 1부터 시작해 n까지 수가 사각형에 들어간다. 기준점을 1로 잡고		*
*				 위로 한칸, 왼쪽으로 한칸 옮겨 그 점을 2라고 잡고 이를 n까지 반복	*
*																					*
*   사 용 함 수: size_check - 원하는 크기의 정사각형을 입력받고 범위가 옳바른지를   *
*							  검사하는 함수											*
*				 Magicsquare - 입력받은 크기만큼 매직스퀘어를 생성, 출력하는 함수	*
*																					*
*																					*
************************************************************************************/

#include<iostream>
#include<cstdlib>

using namespace std;
const int MAX_SIZE = 100;
void Magicsquare(int size);
int size_check(void);



void main()
{
	int Size;
	Size = size_check();
	Magicsquare(Size);
}

// 크기 입력 , 검사 함수 //
int size_check(void)
{
	int n; // 홀수형 정사각형의 크기
	cout << "매직스퀘어의 크기(홀수)를 입력하시오 : ";
	cin >> n;
	while (1)
	{
		// n이 음수 또는 0이거나 , 짝수이거나 , 입력범위를 초과한 경우 if 실행 //
		if ((n > MAX_SIZE) || (n <= 0) || (n%2==0)) 					
		{
			cout << "입력가능한 범위가 아닙니다. 다시 입력하시오" << endl << endl;
			cout << "매직스퀘어의 크기를 입력하시오. : ";
			cin >> n;
		}
		else
		{
			cout << "입력한 사각형의 크기 : " << n << "X" << n << endl;
			break;
		}
	}
	return n;
}








//***************************************알고리즘***************************************//
/*	n이 홀수일 때에는 마방진을 간단한 방법으로 만들 수 있다.							*/
/*	첫 번째 행의 한가운데 열에 1을 넣는다.												*/
/*	이어서 다음과 같은 규칙으로 숫자를 채운다.											*/
/*	즉, 다음 숫자를 대각선 방향으로 오른쪽 위 칸에 넣는다.								*/
/*	이때 해당하는 칸이 마방진의 위쪽으로 벗어난 경우에는 반대로 가장 아래쪽의 칸으로,	*/
/*	마방진의 오른쪽으로 벗어나는 경우는 가장 왼쪽의 칸으로 각각 한번더 이동한다.		*/
/*	오른쪽인 동시에 위쪽으로 벗어나는 경우 및 오른쪽 위에 다른 숫자가 이미 있는 경우에는*/
/*	오른쪽위 대신 원래 칸의 한 칸 아래에 넣는다.										*/	
//***************************************알고리즘***************************************//
void Magicsquare(int size)
{
	int x , y , count=2;
	int arry[MAX_SIZE][MAX_SIZE] = {0,};
	int n = size * size ;

	// Magicsquare의 기준과 초기값 설정
	x = 0 , y = size / 2;	arry[0][y] = 1;

	for(int i=1 ; i<n ; i++)
	{
		x = x-1 , y = y+1; // 오른쪽 위로 이동
		if( ((x<0) && (y>size-1)) || (arry[x][y]!=0) ) // 오른쪽 위로 벗어나는 경우 & 이미 숫자가 존재 하는 경우
		{
			x = x+2 , y = y-1; // 원점의 아래 한칸
			arry[x][y] = count;
		}
		else if(x<0) // 위로 벗어나는 경우
		{
			y = y;	x = size-1;		arry[x][y] = count;
		}
		else if(y>size-1) // 오른쪽으로 벗어나는 경우
		{
			y = 0;
			arry[x][y] = count;
		}
		else arry[x][y] = count;
		count ++;
	}	
				
	for(int i=0 ; i<size ; i++)
	{
		for(int j=0 ; j<size ; j++)
			cout << arry[i][j] << "\t" ;
		cout << endl;
	}
}