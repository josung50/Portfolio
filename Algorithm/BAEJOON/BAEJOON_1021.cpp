#include<iostream>
#include<deque>
using namespace std;

deque<int> dq;
int n;	int m; // �ڿ��� , ���� �������� ��
int count_n; // ���� Ƚ��
int number; // ���� ã�� ��

void init(); // n�� ŭ dq�� ä��
int find_number();
void move_left();
void move_right();

int main() {
	cin >> n >> m;
	init();
	while (m--) {
		cin >> number;
		while (1) {
			int flag = find_number();
			if (flag == 1)
				break;
			else
				continue;
		}
	}
	cout << count_n << "\n";
}

void init() {
	count_n = 0;
	int temp_number = 1;
	for (int i = 0; i < n; i++)
		dq.push_back(temp_number++);

	/*
	�׽�Ʈ ���
	int size = dq.size();
	for (int i = 0; i < size; i++)
		cout << dq.at(i) << " ";
	*/
}

int find_number() {
	int number_it;
	int size = dq.size();

	// �ٷ� front�� ã������ ���
	if (dq.front() == number) {
		dq.pop_front();
		return 1;
	}

	// �̵��� �ؾ� �ϴ� ���
	for (int i = 0; i < size; i++) {
		if (dq[i] == number)
			number_it = i;
	}

	if (number_it <= size / 2) { // �߰����� ����(front��)
		move_left();
		if (dq[0] == number) {
			dq.pop_front();
			return 1;
		}
	}

	else { // �߰����� ������(back��)
		move_right();
		if (dq[0] == number) {
			dq.pop_front();
			return 1;
		}
	}

	return -1;
}

void move_left() {
	count_n++;
	int temp = dq.front();
	dq.pop_front();
	dq.push_back(temp);
}
void move_right() {
	count_n++;
	int temp = dq.back();
	dq.pop_back();
	dq.push_front(temp);
}