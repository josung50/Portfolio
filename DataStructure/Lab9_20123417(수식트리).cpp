#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

class Node 
{
private: 
	int prio;
	char data;
	Node *left;
	Node *right;
public:
	
	Node(char value) {data = value; left=0; right=0;}
	friend class Tree;
};


class Tree
{
public:
	Node *root;
	Tree() {root=0;}
	void Build(char data);
	void Operand(Node *temp);
	void Operator(Node *temp);
	void inorder(Node *ptr);
	void postorder(Node *ptr);
	void preorder(Node *ptr);
	int evaluate(Node *root);

};

void Tree::Build(char data)
{
	char prec[5][2]={'^',3, '*',2, '/',2, '+',1, '-',1}; // ������ �켱������ ����

	Node *temp = new Node(data);
	temp->prio = 4;
	
	// �������� ��� �켱������ ���� //
	for(int i=0; i<=4; i++)
	{
		if(temp->data == prec[i][0])
			temp->prio = prec[i][1];
	}

	// �������� ��� ������ ��� //
	if(temp->prio == 4)
		Operand(temp);
	else Operator(temp);
	
	
}

////////////////////////////////////
/*	������� ����� �����ʿ� ���� */
////////////////////////////////////
void Tree::Operand(Node *temp)
{
	Node *p = root;
	if(root == 0)
		root = temp;
	else
	{
		while(p->right != NULL)
			p=p->right;
		p->right = temp;
	}
}

////////////////////////////////////////////
/*	�����ڶ�� �켱������ ���ؼ� ��带 */
/*	Ʈ���� �籸�� �Ѵ�.					  */
////////////////////////////////////////////
void Tree::Operator(Node *temp)
{
	if(root->prio >= temp->prio)
	{
		temp->left = root;
		root = temp;
	}

	else
	{
		temp->left = root->right;
		root ->right = temp;
	}
}

// ���� ���� //
void Tree::inorder(Node *ptr)
{
	if(ptr)
	{
		inorder(ptr->left);
		cout << ptr->data;
		inorder(ptr->right);
	}
}

// ���� ���� //
void Tree::postorder(Node *ptr)
{
	if(ptr)
	{
		postorder(ptr->left);
		postorder(ptr->right);
		cout << ptr->data;
	}
}

// ���� ���� //
void Tree::preorder(Node *ptr)
{
	if(ptr)
	{
		cout << ptr->data;
		preorder(ptr->left);
		preorder(ptr->right);
	}
}



int Tree::evaluate(Node *root)
{
	if(root == NULL) // ���� ���� ���
		return 0; 
	if(root->left == NULL && root->right == NULL) // root�� �����Ͱ� �ִ� ���
		return root->data-'0' ; 
	else    
	{ 
		int op1=evaluate(root->left);  // ���� ����Ʈ�� ��ȸ
		int op2=evaluate(root->right); // ������ ����Ʈ�� ��ȸ    

		switch(root->data)         
		{
		case'+' :
			return op1+op2; 
		case'-' :
			return op1-op2; 
		case'*' : 
			return op1*op2;
		case'/' : 
			return op1/op2;         
		default:
			return op1;
		}  
		
		
	}   
} 



void main()
{
	char exp[50];
	int length;

	Tree tree;


	cout << "���� �Է� : ";
	cin >> exp;
	length=strlen(exp)+1;

	for(int i=0; i<length; i++)
	{
		tree.Build(exp[i]);
	}
	
	cout << "���� ���� �� : ";
	tree.inorder(tree.root);
	cout << endl;

	cout << "���� ���� �� : ";
	tree.postorder(tree.root);
	cout << endl;

	cout << "���� ���� �� : ";
	tree.preorder(tree.root);
	cout << endl;

	
	cout <<	"��� : " << tree.evaluate(tree.root) << endl;
}
		