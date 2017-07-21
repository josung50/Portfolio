#include<iostream>
#include<cstring>
#include<deque>
using namespace std;

int TestCases;
char command[100000];
int strlen_command;
int n; // 수의 개수
deque<int> dq;
char input_char;
int input_number;

int R_flag;
int error_flag;

void menu(char MENU);
bool error_check(char MENU);
void print();

int main() {
	cin >> TestCases;

	while (TestCases--) {
		R_flag = 0;
		error_flag = 0;
		dq.clear();
		cin >> command >> n;
		strlen_command = strlen(command);
		
		/* 배열 입력 */
		//int total_n = n*2 - 1; // [ ] 뺀 값

		cin >> input_char; // [ 받기
		while (n--) {
			cin >> input_number; // 상수 받기
			dq.push_back(input_number);
			if (n != 0)
				cin >> input_char; // , 받기
		}
		cin >> input_char; // ] 받기
		/* 테스트 출력
		int size = dq.size();
		for (int i = 0; i < size; i++) {
			cout << dq.at(i) << " ";
		}
		*/

		int command_it = 0;
		//cout << strlen_command << "\n";
		while (strlen_command--) {
			if (error_check(command[command_it]) == true ) {
				error_flag = 1;
				cout << "error\n";
				break;
			}
			menu(command[command_it++]);
		}

		print();
	}
}

void menu(char MENU) {
	switch (MENU) {
	case 'R':
		if (R_flag == 0)
			R_flag = 1;
		else if (R_flag == 1)
			R_flag = 0;
		break;

	case 'D':
		if (R_flag == 0) {
			dq.pop_front(); // 상수 pop
		}
		else if (R_flag == 1) {
			dq.pop_back();
		}
		break;
	}
}

bool error_check(char MENU) {
	//cout << dq.size() << "\n";
	if (dq.empty() == 1 && MENU == 'D')
		return true;
	else return false;
}

void print() {
	int size = dq.size();
	if (error_flag == 1)
		return;
	if (R_flag == 0) {
		cout << "[";
		for (int i = 0; i < size; i++) {
			cout << dq.at(i);
			if (i != size - 1)
				cout << ",";
		}
		cout << "]\n";
	}
	else {
		cout << "[";
		for (int i = size - 1; i >= 0; i--) {
			cout << dq.at(i);
			if (i != 0)
				cout << ",";

		}
		cout << "]\n";
	}
}