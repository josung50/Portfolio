/************************************************************************************
*																					*
*	국민대학교 컴퓨터 공학부 20123417 조성룡										*
*	프로그램 명: List 결합															*
*	설		 명: 두 개의 리스트를 연결한다.											*
*	알 고 리 즘: 두 개의 리스트에 데이터를 입력받은 후, 한쪽 리스트에 나머지 데이터	*
*				를 몰아서 받는다. 이 때 입력을 받은 데이터는 기존의 데이터와 비교	*
*				하여 대소관계를 파악, 오름차순으로 정렬-저장한다.					*
************************************************************************************/

#include "homework3.h"

void main()
{ 
   ifstream instream_1; // data1.txt 받음
   ifstream instream_2; // data2.txt 받음
   instream_1.open("data1.txt"); 
   instream_2.open("data2.txt");
   if(instream_1.fail() || instream_2.fail()) // 열기 failed
   {
      cerr<<"input file opening fail";
      exit(1);
   }

   List list_1; // data1의 리스트
   List list_2; // data2의 리스트

   for(int i=0; i<8; i++) // list_1의 데이터 입력
   {
		int identy; char name[20]; char major[20]; char grade;
		instream_1 >> name >> identy >> major >> grade;
		list_1.insertNode(name , identy , major , grade);
   }

   for(int i=0; i<3; i++) // list_2의 데이터 입력
   {
	   int identy; char name[20]; char major[20]; char grade;
	   instream_2 >> name >> identy >> major >> grade;
	   list_2.insertNode(name , identy , major , grade);
   }

   // list_1의 저장된 값 출력 //
   cout << "============list_1============" << endl;
   list_1.display();
   cout << "\n\n";

   // list_2의 저장된 값 출력 //
   cout << "============list_2============" << endl;
   list_2.display();
   cout << "\n\n";

	instream_1.close();
	instream_2.close();
	

	instream_2.open("data2.txt"); /* insertNode의 오류를 방지하기 위해 
											data2파일을 다시 open*/
   // 두 list의 결합 //
   for(int i=0; i<3; i++)
   {
	   int identy; char name[20]; char major[20]; char grade;
       instream_2 >> name >> identy >> major >> grade;
       list_1.insertNode(name , identy , major , grade);
   }

   // major == cs 인 데이터만 출력 //
    cout << "============list_1 + list_2============" << endl;
	list_1.display_cs();

  instream_2.close();

}