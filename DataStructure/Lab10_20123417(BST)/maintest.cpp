#include"BSTree.h"

void main()
{
	int select;
	int key;
	Tree tree;
	while(1)
	{
		cout << "1.Insert  2.Delete  3.Search  4.Print  5.Post  6.Pre  7.In: ";
		cin >> select;

		switch(select)
		{
		case 1:
			cout << "Insert data : ";
			cin >> key;
			tree.insertTree(tree.root , key);
			cout << endl << endl;
			break;
		case 2:
			cout << "Delete data : ";
			cin >> key;
			tree.deleteTree(key);
			cout << endl << endl;
			break;
		case 3:
			cout << "Search data : ";
			cin >> key;
			tree.searchTree(key);
			cout << endl << endl;
			break;
		case 4:
			tree.drawTree();
			cout << endl << endl;
			break;
		case 5:
			tree.postorder(tree.root);
			cout << endl << endl;
			break;
		case 6:
			tree.preorder(tree.root);
			cout << endl << endl;
			break;
		case 7:
			tree.inorder(tree.root);
			cout << endl << endl;
			break;
		case 8:
			exit(1);
		}
	}
}