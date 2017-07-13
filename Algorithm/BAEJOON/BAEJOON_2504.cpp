/* �˰��� 
	������ ���� ���ʷ� ��ȯ��Ų��.
	ex) [()()]([])�� ���� ���Դٰ� �����ϸ�,
	1. [
	2. [(
	3. [2
	4. [2(
	5. [22
	6. [22 ���� ���� ]Ȥ�� ) �ε� �տ� ������ �߰� ��� ������
	7. [4
	8. 12
	9. 12 (
	10. 12 ([
	11. 12 (3
	12. 12 (3 ���� ���� ) �̹Ƿ� �߰� ��� ������
	13. 12 6
	14. string���� ���� ���ڰ� ���µ� ����2�� size�� 1���� ũ�� �����θ� �̷���� ���̹Ƿ�
		��� �����ش�.
	15. ����
*/

#include<iostream>
#include<cstring>
#include<stack>
using namespace std;

// (:40 [:91

stack<char> Stack; // �˸��� ���ڿ� Ȯ�ο� ����
stack<int> Stack2; // ���� ����
char String[30];

int check_string(); // -1:�߸��� ���ڿ�, 1:�˸��� ���ڿ�
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
	// (] or [) ��� üũ
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

	// ��ȣ�� �����ִ� ��� üũ
	if (Stack.empty() == 0)
		return -1;
	return 1;
}

int calculation() {
	// (:-1     ):-2     [:-3     ]:-4 �� stack2�� ���� �ִ´�.

	int temp = 0;
	int size = strlen(String);
	int i = 0;
	sum = 0;
	int index = 0;
	while (1) {
		switch (String[i]) { // ������ ��
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
			else if (Stack2.top() != -1) {// top���� ( �ƴϸ�, �� �տ� ����� ������
				while (1) { // ( ���� ������ ��� ����� �����ְ� [������ ���ϱ�3�� ���ش�.
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
			else if (Stack2.top() != -3) {// top���� [ �ƴϸ�, �� �տ� ����� ������
				while (1) { // [ ���� ������ ��� ����� �����ְ� [������ ���ϱ�3�� ���ش�.
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

		// ���ÿ� ����� �ϳ��� �������� ���
		if (i >= strlen(String))
			return Stack2.top();

		i++;
		// ���ڿ��� �� �Է¹޾Ҵµ� ������ ũ�Ⱑ 2�̻��� ��� �����θ� �̷���� �����Ƿ� ��� �����ش�.
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