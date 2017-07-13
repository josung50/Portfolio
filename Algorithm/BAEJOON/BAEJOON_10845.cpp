#include<iostream>
#include<cstring>
using namespace std;


int TestCases;

class Queue {
public:
	int start;	int end;
	int que[10001];
	int count_n;
	Queue() {
		count_n = 0;
		start = -1;
		end = -1;
	}
	void init() {
		start = -1;
		end = -1;
	}
	void push(int x) {
		que[++end] = x;
		count_n++;
		if (count_n == 1) {
			start = end;
		}
	}
	void pop() {
		if(count_n == 1) {
			cout << que[start] << "\n";
			count_n--;
			return;
		}
		if (start >= end) {
			cout << "-1\n";
		}
		else {
			cout << que[start++] << "\n";
			count_n--;
		}
	}
	void size() {
		cout << count_n << "\n";
	}
	void empty() {
		if (count_n == 0)
			cout << "1\n";
		else cout << "0\n";
	}
	void front() {
		if (count_n == 0) {
			cout << "-1\n";
		}
		else if (count_n == 1) {
			cout << que[end] << "\n";
		}
		else {
			cout << que[start] << "\n";
		}
	}
	void back() {
		if (count_n == 0)
			cout << "-1\n";
		else {
			cout << que[end] << "\n";
		}
	}
};

int main() {
	Queue queue;
	queue.init();
	cin >> TestCases;
	char command[40];
	int x;
	while (TestCases--) {
		cin >> command;
		if (strcmp(command, "push") == 0) {
			cin >> x;
			queue.push(x);
		}
		else if (strcmp(command, "pop") == 0) {
			queue.pop();
		}
		else if (strcmp(command, "front") == 0) {
			queue.front();
		}
		else if (strcmp(command, "back") == 0) {
			queue.back();
		}
		else if (strcmp(command, "empty") == 0) {
			queue.empty();
		}
		else if (strcmp(command, "size") == 0) {
			queue.size();
		}
		//cout << "start:" << queue.start << "   end:" << queue.end << "    count_n:" << queue.count_n << "\n\n";
	}
}