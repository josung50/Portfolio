#include<iostream>
using namespace std;

int A, B, C;
int result;
int number[10];

int main() {
	for (int i = 0; i < 10; i++) {
		number[i] = 0;
	}
	cin >> A >> B >> C;
	result = A*B*C;

	int left;  // ³ª¸ÓÁö , ¸ò
	while (result != 0) {
		left = result % 10;
		result = result / 10;

		number[left] += 1;
	}

	for (int i = 0; i < 10; i++) {
		cout << number[i] << "\n";
	}
}
