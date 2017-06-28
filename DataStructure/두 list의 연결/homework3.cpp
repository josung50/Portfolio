#include "homework3.h"

bool List::isEmpty()
{
   if (head == 0) return 1;
   else return 0;
}

/****************************************************************/
/*							알고리즘							*/
/*	new node 데이터값 중 NAME 데이터를 head부터 시작하여 연결된	*/
/*	리스트들과의 아스키코드값을 비교, 정렬 한다.				*/
/*	이 때, 노드 생성시 생성자로 인해 필요한 데이터는 모두		*/
/*	들어가 있는 상태이다.										*/
/****************************************************************/
void List::insertNode(char a[],int data,char b[], char c) //이름 점수 전공 학점 순 입력
{
   Node *temp = new Node(a,data,b,c);
   
   temp->next = 0;   
   Node *p, *q;   //오름차순 정렬위한 Node* p, *q
   if (head == 0) head = temp;
   else if (temp->name[0] < head->name[0]) {
      temp->next = head;
      head = temp;
   }
   else {
      p = head;
      while ((p != 0) && (p->name[0] < temp->name[0])) {
         q = p;
         p = p->next;
      }
      if (p != 0) {
         temp->next = p; q->next = temp;
      }
      else
         q->next = temp;
   }
}

void List::display()
{ 
   Node *ptr;
   ptr = head;

   while(ptr) 
   {
      cout<<ptr->name<<" "<< ptr->id<<" "<<ptr->major<<" "<<ptr->grade << endl;
      ptr = ptr->next;
   }
   cout << endl;
}

void List::display_cs()
{
	Node *ptr;
	ptr = head;
	while(ptr)
	{
		if(strcmp(ptr->major,"CS"))
			cout << ptr->name << " " << ptr->id <<" " << ptr->major << " " << ptr->grade << endl;;
		ptr = ptr->next;
	}
}
