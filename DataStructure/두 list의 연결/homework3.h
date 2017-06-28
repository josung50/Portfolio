#ifndef __home_work_
#define __home_work_

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Node {
private:
   char name[10];   // �̸�
   int id;      // ID
   char major[10];   // ����
   char grade;      // ����
   Node *next;

   // ������ //
   Node(){}      
   Node(char Name[20],int value, char Major[10],char Grade) : id(value),grade(Grade)
   {                  
      strcpy(name,Name);
      strcpy(major,Major);
   }
   friend class List;
};

class List {
private:
   Node *head;
public:
   List () { head = 0;}
   void List::insertNode(char a[],int data,char b[], char c); // ���� ����
   bool isEmpty();
   void display(); // ����� ��� ������ ���
   void display_cs(); // ������ CS�� �����͸��� ���
};
#endif