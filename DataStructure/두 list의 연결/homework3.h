#ifndef __home_work_
#define __home_work_

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Node {
private:
   char name[10];   // 이름
   int id;      // ID
   char major[10];   // 전공
   char grade;      // 학점
   Node *next;

   // 생성자 //
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
   void List::insertNode(char a[],int data,char b[], char c); // 정렬 저장
   bool isEmpty();
   void display(); // 저장된 모든 데이터 출력
   void display_cs(); // 전공이 CS인 데이터만을 출력
};
#endif