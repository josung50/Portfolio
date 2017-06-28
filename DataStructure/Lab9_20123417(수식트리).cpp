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
	char prec[5][2]={'^',3, '*',2, '/',2, '+',1, '-',1}; // 연산자 우선순위를 결정

	Node *temp = new Node(data);
	temp->prio = 4;
	
	// 연산자일 경우 우선운위를 배정 //
	for(int i=0; i<=4; i++)
	{
		if(temp->data == prec[i][0])
			temp->prio = prec[i][1];
	}

	// 연사자일 경우 숫자일 경우 //
	if(temp->prio == 4)
		Operand(temp);
	else Operator(temp);
	
	
}

////////////////////////////////////
/*	정수라면 노드의 오른쪽에 연결 */
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
/*	연산자라면 우선순위를 비교해서 노드를 */
/*	트리를 재구성 한다.					  */
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

// 중위 연산 //
void Tree::inorder(Node *ptr)
{
	if(ptr)
	{
		inorder(ptr->left);
		cout << ptr->data;
		inorder(ptr->right);
	}
}

// 후위 연산 //
void Tree::postorder(Node *ptr)
{
	if(ptr)
	{
		postorder(ptr->left);
		postorder(ptr->right);
		cout << ptr->data;
	}
}

// 전위 연산 //
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
	if(root == NULL) // 값이 없는 경우
		return 0; 
	if(root->left == NULL && root->right == NULL) // root만 데이터가 있는 경우
		return root->data-'0' ; 
	else    
	{ 
		int op1=evaluate(root->left);  // 왼쪽 서브트리 순회
		int op2=evaluate(root->right); // 오른쪽 서브트리 순회    

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


	cout << "수식 입력 : ";
	cin >> exp;
	length=strlen(exp)+1;

	for(int i=0; i<length; i++)
	{
		tree.Build(exp[i]);
	}
	
	cout << "중위 연산 식 : ";
	tree.inorder(tree.root);
	cout << endl;

	cout << "후위 연산 식 : ";
	tree.postorder(tree.root);
	cout << endl;

	cout << "전위 연산 식 : ";
	tree.preorder(tree.root);
	cout << endl;

	
	cout <<	"결과 : " << tree.evaluate(tree.root) << endl;
}
		