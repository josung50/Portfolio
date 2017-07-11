#include<iostream>
#include<cstring>
using namespace std;

int n;
int* number; // 뽑아 낼 수열
int x; // 스택에 차례로 들어갈 수
int* stack;
int stack_index;
int number_index; // 뽑아낸 수열의 index
int no_flag;
char* result;
int result_index;

void init();
void push();
int pop();
int test_cases;
void check(int number);
int empty();

int main() {
	init();
	cin >> n;
	number = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> number[i];
	}
	result = new char[2 * n + 1];

	while (number_index < n) {
		check(number[number_index]);
		if (no_flag == 1) {
			return 0;
		}
	}
	for (int i = 0; i <= result_index; i++)
		cout << result[i] << "\n";

	delete[] stack;
	delete[] number;
}

void init() {
	result_index = -1;
	no_flag = 0;
	x = 1;
	number_index = 0;
	stack_index = -1;
	stack = new int[100000];
}
void push() {
	//cout << "+\n";
	result[++result_index] = '+';
	stack[++stack_index] = x;
	x++;
}
int pop() {
	//cout << "-\n";
	result[++result_index] = '-';
	return stack[stack_index--];
}
int empty() {
	if (stack_index < 0)
		return 1;
	else return 0;
}
void check(int number) {
	if (empty() == 0) {
		if (number == stack[stack_index]) {
			pop();
			number_index++;
		}
		else if (number > stack[stack_index]) {
			push();
		}
		else if (number < stack[stack_index]) { // 잘못된 경우
			cout << "NO" << endl;
			no_flag = 1;
			return;
		}
	}
	else if (empty() == 1) {
		push();
	}
}