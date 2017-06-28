#include "homework3.h"

bool List::isEmpty()
{
   if (head == 0) return 1;
   else return 0;
}

/****************************************************************/
/*							�˰���							*/
/*	new node �����Ͱ� �� NAME �����͸� head���� �����Ͽ� �����	*/
/*	����Ʈ����� �ƽ�Ű�ڵ尪�� ��, ���� �Ѵ�.				*/
/*	�� ��, ��� ������ �����ڷ� ���� �ʿ��� �����ʹ� ���		*/
/*	�� �ִ� �����̴�.										*/
/****************************************************************/
void List::insertNode(char a[],int data,char b[], char c) //�̸� ���� ���� ���� �� �Է�
{
   Node *temp = new Node(a,data,b,c);
   
   temp->next = 0;   
   Node *p, *q;   //�������� �������� Node* p, *q
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
