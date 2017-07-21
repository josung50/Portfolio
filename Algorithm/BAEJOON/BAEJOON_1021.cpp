#include<iostream>
#include<deque>
using namespace std;

deque<int> dq;
int n;	int m; // 자연수 , 내가 뽑으려는 수
int count_n; // 연산 횟수
int number; // 내가 찾을 수

void init(); // n만 큼 dq를 채움
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
	테스트 출력
	int size = dq.size();
	for (int i = 0; i < size; i++)
		cout << dq.at(i) << " ";
	*/
}

int find_number() {
	int number_it;
	int size = dq.size();

	// 바로 front로 찾아지는 경우
	if (dq.front() == number) {
		dq.pop_front();
		return 1;
	}

	// 이동을 해야 하는 경우
	for (int i = 0; i < size; i++) {
		if (dq[i] == number)
			number_it = i;
	}

	if (number_it <= size / 2) { // 중간보다 왼쪽(front쪽)
		move_left();
		if (dq[0] == number) {
			dq.pop_front();
			return 1;
		}
	}

	else { // 중간보다 오른쪽(back쪽)
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