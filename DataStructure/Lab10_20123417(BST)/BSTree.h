#ifndef _BSTREE_H_
#define _BSTREE_H_

#include<iostream>
#include<cstdlib>
#include<iomanip>
using namespace std;

class Node
{
private:
	int data;
	Node* right;
	Node* left;
	friend class Tree;
public:
	Node()
	{	right = 0 ; left = 0;	}
	Node(int key) : data(key)
	{	right = 0; left = 0;	}
};

class Tree 
{
public:
	Node *root;
	Tree()	{root = 0;}
	Node* insertTree(Node* ptr, int key);
	void deleteTree(int);
	Node* deleteBSTree(Node* ptr , int key);
	void searchTree(int);
	Node *searchBSTree(Node *, int key);
	//void traverseTree();
	//void inorderTraverse(Node *);
	void drawTree();
	void drawBSTree(Node *, int);
	int find_min(Node *ptr);
	//int tree_empty();
	//void freeBSTree(Node *);
	void postorder(Node *ptr);
	void preorder(Node *ptr);
	void inorder(Node* ptr);
};

#endif