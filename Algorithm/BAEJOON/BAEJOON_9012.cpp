#include<iostream>
#include<stack>
#include<cstring>

using namespace std;

int TestCases;

int check_VPS(char String[50] , stack<char> Stack);

int main() {
	
	cin >> TestCases;
	while (TestCases--) {
		stack<char> Stack;
		char String[50];
		cin >> String;
		check_VPS(String , Stack);
	}
}

int check_VPS(char String[50] , stack<char> Stack) {
	for (int i = 0; i < strlen(String); i++) {
		if (String[i] == '(')
			Stack.push('(');
		else {
			if (Stack.empty() != 1)
				Stack.pop();
			else { // (��� pop�� ���ϴ� ���
				cout << "NO\n";
				return 0;
			}
		}
	}

	// (�� �����ִ� ���
	if (Stack.empty() == 0) {
		cout << "NO\n";
		return 0;
	}

	cout << "YES\n";
	return 1;
}