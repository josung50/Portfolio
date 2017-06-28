#include"BSTree.h"

void Tree::drawTree() { drawBSTree(root, 1); }

void Tree::drawBSTree(Node *p, int level)
{
	if (p != 0 && level <= 7) 
	{
		drawBSTree(p->right, level+1);
		for (int i = 1; i <= (level-1); i++)
			cout << " ";
		cout << setw(2) << p->data;
		if (p->left != 0 && p->right != 0) cout << " <" << endl;
		else if (p->right != 0) cout << " /" << endl;
		else if (p->left != 0) cout << " \\" << endl;
		else cout << endl;
		drawBSTree(p->left, level+1);
	}
}

Node* Tree::insertTree(Node* ptr, int key)
{
	if(root == 0)
	{
		Node *temp = new Node(key);
		root = temp;
	}

	if (ptr == NULL) 
	{
		ptr = new Node(key);
		ptr->data = key;
		ptr->left = NULL;
		ptr->right = NULL;
	}
	else if (key < ptr->data)
		ptr->left = insertTree(ptr->left, key);
	else if (key > ptr->data)
		ptr->right = insertTree(ptr->right, key);
	return ptr;
}

void Tree::deleteTree(int key)	{ deleteBSTree(root , key); }
Node* Tree::deleteBSTree(Node* ptr , int key)
{
	
	Node* p;
	if (ptr != NULL) 
	{
		if (key < ptr->data)
			ptr->left = deleteBSTree(ptr->left , key); /* move to the node */
		else if (key > ptr->data)
			ptr->right = deleteBSTree (ptr->right , key); /* arrived at the node*/
		else if ((ptr->left == NULL) && (ptr->right==NULL))
			ptr=NULL; /*leaf*/
		else if (ptr->left == NULL) 
		{
			if(ptr == root)
				root=root->right;
			p = ptr; ptr=ptr->right; delete(p); /*rightchild only*/ }
		else if (ptr->right == NULL) 
		{
			if(ptr == root)
				root=root->left;
			p = ptr; ptr=ptr->left; delete(p); /*left child only */ }
		else ptr->data = find_min(ptr->right); /*both child exists */
	}
	else printf("Not found.");
	return ptr;
}

int Tree::find_min(Node* ptr) /*right subtree에서 가장 작은것 선택 */
{
	Node* temp = new Node;
	if (ptr->left ==NULL)
	{
		temp->data = ptr->data;
		ptr = ptr->right;
	}
	else temp->data = find_min (ptr->left);
	return temp->data;
}

void Tree::searchTree(int key)
{
	if(searchBSTree(root , key) == NULL)
		cout << key <<" is not in the Tree.";
	else
		cout << key << " is in the Tree.";
}
Node* Tree::searchBSTree(Node *ptr, int key)
{
	if (ptr == NULL) 
		return NULL; //search unsuccessful
	else
	{
		if (key == ptr->data) return ptr;
		else if (key <ptr->data)
			ptr = searchBSTree(ptr->left, key); //search leftsubtree
		else if (key > ptr->data)
			ptr= searchBSTree(ptr->right, key); //search rightsubtree
	}

	return ptr;
}

void Tree::postorder(Node *ptr)
{
	if(ptr)
	{
		postorder(ptr->left);
		postorder(ptr->right);
		cout << ptr->data << " "; 
	}
}

void Tree::preorder(Node *ptr)
{
	if(ptr)
	{
		cout << ptr->data << " ";
		preorder(ptr->left);
		preorder(ptr->right);
	}
}

void Tree::inorder(Node *ptr)
{
	if(ptr)
	{
		inorder(ptr->left);
		cout << ptr->data << " ";
		inorder(ptr->right);
	}
}