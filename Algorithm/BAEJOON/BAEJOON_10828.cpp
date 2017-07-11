#include<iostream>
#include<cstring>

using namespace std;

int index_top;
int stack[10000];
char command[10];
int number;
int test_cases;

void init_stack();
void menu(char command[]);
void push(int X);
void pop();
void size();
void empty();
void top();

int main() {
	init_stack();
	cin >> test_cases;
	while (test_cases--) {
		cin >> command;
		menu(command);
	}
}

void init_stack() {
	index_top = -1;
}
void push(int x) {

	stack[++index_top] = x;
}
void pop() {
	if (index_top < 0) {
		cout << -1 << endl;
		return;
	}
	cout << stack[index_top--] << endl;
}
void empty() {
	if (index_top <= -1) {
		cout << 1 << endl;
		return;
	}
	else {
		cout << 0 << endl;
		return;
	}
}
void size() {
	cout << index_top + 1 << endl;
}
void top() {
	if (index_top < 0)
		cout << -1 << endl;
	else {
		cout << stack[index_top] << endl;
	}
}
void menu(char command[]) {
	if (strcmp(command, "push") == 0) {
		cin >> number;
		push(number);
	}
	else if (strcmp(command, "top") == 0)
		top();
	else if (strcmp(command, "size") == 0)
		size();
	else if (strcmp(command, "empty") == 0)
		empty();
	else if (strcmp(command, "pop") == 0)
		pop();
}