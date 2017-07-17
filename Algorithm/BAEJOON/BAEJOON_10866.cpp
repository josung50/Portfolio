#include<iostream>
#include<cstring>
using namespace std;

int TestCases;
char command[50];
int deque[20002];
int count_n;
int f;
int b;

void menu();
void push_back(int x);
void push_front(int x);
void front();
void back();
void size();
void pop_front();
void pop_back();
void empty();


int main() {
	cin >> TestCases;
	f = 10000;
	b = 10000;
	count_n = 0;
	while (TestCases--) {
		cin >> command;
		menu();
	}
}

void menu() {
	int x;
	if (strcmp(command, "push_back") == 0) {
		cin >> x;
		push_back(x);
	}
	else if (strcmp(command, "push_front") == 0) {
		cin >> x;
		push_front(x);
	}
	else if (strcmp(command, "front") == 0) {
		front();
	}
	else if (strcmp(command, "back") == 0) {
		back();
	}
	else if (strcmp(command, "empty") == 0) {
		empty();
	}
	else if (strcmp(command, "pop_front") == 0) {
		pop_front();
	}
	else if (strcmp(command, "pop_back") == 0) {
		pop_back();
	}
	else if (strcmp(command, "size") == 0) {
		size();
	}
}

void push_back(int x) {
	if (count_n == 0) {
		deque[b] = x;
		f = b;
		count_n++;
	}
	else {
		deque[--b] = x;
		count_n++;
	}
}
void push_front(int x) {
	if (count_n == 0) {
		deque[f] = x;
		count_n++;
		b = f;
	}
	else {
		deque[++f] = x;
		count_n++;
	}
}
void front() {
	if (count_n >= 1)
		cout << deque[f] << "\n";
	else
		cout << "-1\n";
}
void back() {
	if (count_n >= 1)
		cout << deque[b] << "\n";
	else
		cout << "-1\n";
}
void size() {
	cout << count_n << "\n";
}
void pop_front() {
	if (count_n == 0) {
		cout << "-1\n";
		return;
	}
	if (count_n >= 2) {
		cout << deque[f--] << "\n";
		count_n--;
		return;
	}
	if (count_n == 1) {
		cout << deque[f] << "\n";
		f = 10000;
		b = f;
		count_n--;
		return;
	}
}
void pop_back() {
	if (count_n == 0) {
		cout << "-1\n";
		return;
	}
	if (count_n >= 2) {
		cout << deque[b++] << "\n";
		count_n--;
		return;
	}
	if (count_n == 1) {
		cout << deque[b] << "\n";
		b = 10000;
		f = b;
		count_n--;
		return;
	}

}
void empty() {
	if (count_n == 0)
		cout << "1\n";
	else cout << "0\n";
}