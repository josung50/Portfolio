/* 알고리즘 
	스택의 값을 차례로 변환시킨다.
	ex) [()()]([])의 값이 들어왔다고 가정하면,
	1. [
	2. [(
	3. [2
	4. [2(
	5. [22
	6. [22 들어올 값이 ]혹은 ) 인데 앞에 상수라면 중간 계산 끝내기
	7. [4
	8. 12
	9. 12 (
	10. 12 ([
	11. 12 (3
	12. 12 (3 들어올 값이 ) 이므로 중간 계산 끝내기
	13. 12 6
	14. string에서 받을 문자가 없는데 스택2의 size가 1보다 크면 상수들로만 이루어진 것이므로
		모두 더해준다.
	15. 리턴
*/

#include<iostream>
#include<cstring>
#include<stack>
using namespace std;

// (:40 [:91

stack<char> Stack; // 알맞은 문자열 확인용 스택
stack<int> Stack2; // 계산용 스택
char String[30];

int check_string(); // -1:잘못된 문자열, 1:알맞은 문자열
void init_stack();
int calculation();

int sum;

int main() {
	sum = 0;
	cin >> String;
	if (check_string() == -1)
		cout << "0";
	else {
		//init_stack();
		cout << calculation();
	}
}

void init_stack() {
	int size = Stack.size();
	for (int i = 0; i < size; i++) {
		Stack.pop();
	}
}

int check_string() {
	// (] or [) 경우 체크
	for (int i = 0; i < strlen(String); i++) {
		if (String[i] == '(') {
			Stack.push('(');
		}
		else if (String[i] == '[') {
			Stack.push('[');
		}
		else if (String[i] == ')') {
			if (Stack.empty() == 0 && Stack.top() == '(')
				Stack.pop();
			else if (Stack.empty() == 0 && Stack.top() == '[')
				return -1;
			else return -1;
		}
		else if (String[i] == ']') {
			if (Stack.empty() == 0 && Stack.top() == '[')
				Stack.pop();
			else if (Stack.empty() == 0 && Stack.top() == '(')
				return -1;
			else return -1;
		}
	}

	// 괄호가 남아있는 경우 체크
	if (Stack.empty() == 0)
		return -1;
	return 1;
}

int calculation() {
	// (:-1     ):-2     [:-3     ]:-4 로 stack2에 값을 넣는다.

	int temp = 0;
	int size = strlen(String);
	int i = 0;
	sum = 0;
	int index = 0;
	while (1) {
		switch (String[i]) { // 들어오는 값
		case '(':
			Stack2.push(-1);
			break;

		case '[':
			Stack2.push(-3);
			break;

		case ')':
			if (Stack2.top() == -1) {
				Stack2.pop();
				Stack2.push(2);
			}
			else if (Stack2.top() != -1) {// top값이 ( 아니면, 즉 앞에 상수가 있으면
				while (1) { // ( 나올 때까지 모든 상수는 더해주고 [나오면 곱하기3을 해준다.
					if (Stack2.top() == -1) {
						temp *= 2;
						Stack2.pop();
						Stack2.push(temp);
						temp = 0;
						break;
					}
					else {
						temp += Stack2.top();
						Stack2.pop();
					}
				}
			}
			else {
				Stack2.pop();
				Stack2.push(2);
			}
			break;

		case ']':
			if (Stack2.top() == -3) {
				Stack2.pop();
				Stack2.push(3);
			}
			else if (Stack2.top() != -3) {// top값이 [ 아니면, 즉 앞에 상수가 있으면
				while (1) { // [ 나올 때까지 모든 상수는 더해주고 [나오면 곱하기3을 해준다.
					if (Stack2.top() == -3) {
						temp *= 3;
						Stack2.pop();
						Stack2.push(temp);
						temp = 0;
						break;
					}
					else {
						temp += Stack2.top();
						Stack2.pop();
					}
				}

			}
			else {
				Stack2.pop();
				Stack2.push(3);
			}
			break;
		}

		// 스택에 상수가 하나만 남아있을 경우
		if (i >= strlen(String))
			return Stack2.top();

		i++;
		// 문자열은 다 입력받았는데 스택의 크기가 2이상인 경우 상수들로만 이루어져 있으므로 모두 더해준다.
		if (i >= strlen(String)) {
			while (Stack2.empty() == 0) {
				sum += Stack2.top();
				Stack2.pop();
			}
			return sum;
		}
	}
	return sum;
}