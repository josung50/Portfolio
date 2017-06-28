/************************************************************************************
*																					*
*	���δ��б� ��ǻ�� ���к� 20123417 ������										*
*	���α׷� ��: List ����															*
*	��		 ��: �� ���� ����Ʈ�� �����Ѵ�.											*
*	�� �� �� ��: �� ���� ����Ʈ�� �����͸� �Է¹��� ��, ���� ����Ʈ�� ������ ������	*
*				�� ���Ƽ� �޴´�. �� �� �Է��� ���� �����ʹ� ������ �����Ϳ� ��	*
*				�Ͽ� ��Ұ��踦 �ľ�, ������������ ����-�����Ѵ�.					*
************************************************************************************/

#include "homework3.h"

void main()
{ 
   ifstream instream_1; // data1.txt ����
   ifstream instream_2; // data2.txt ����
   instream_1.open("data1.txt"); 
   instream_2.open("data2.txt");
   if(instream_1.fail() || instream_2.fail()) // ���� failed
   {
      cerr<<"input file opening fail";
      exit(1);
   }

   List list_1; // data1�� ����Ʈ
   List list_2; // data2�� ����Ʈ

   for(int i=0; i<8; i++) // list_1�� ������ �Է�
   {
		int identy; char name[20]; char major[20]; char grade;
		instream_1 >> name >> identy >> major >> grade;
		list_1.insertNode(name , identy , major , grade);
   }

   for(int i=0; i<3; i++) // list_2�� ������ �Է�
   {
	   int identy; char name[20]; char major[20]; char grade;
	   instream_2 >> name >> identy >> major >> grade;
	   list_2.insertNode(name , identy , major , grade);
   }

   // list_1�� ����� �� ��� //
   cout << "============list_1============" << endl;
   list_1.display();
   cout << "\n\n";

   // list_2�� ����� �� ��� //
   cout << "============list_2============" << endl;
   list_2.display();
   cout << "\n\n";

	instream_1.close();
	instream_2.close();
	

	instream_2.open("data2.txt"); /* insertNode�� ������ �����ϱ� ���� 
											data2������ �ٽ� open*/
   // �� list�� ���� //
   for(int i=0; i<3; i++)
   {
	   int identy; char name[20]; char major[20]; char grade;
       instream_2 >> name >> identy >> major >> grade;
       list_1.insertNode(name , identy , major , grade);
   }

   // major == cs �� �����͸� ��� //
    cout << "============list_1 + list_2============" << endl;
	list_1.display_cs();

  instream_2.close();

}