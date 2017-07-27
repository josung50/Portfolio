#include<iostream>
using namespace std;

int main() {
	int TestCases = 3;
	int count_zero = 0, count_one = 0;
	int number;
	while (TestCases--) {
		count_zero = 0;
		count_one = 0;
		for (int i = 0; i < 4; i++) {
			cin >> number;
			if (number == 1)
				count_one++;
			else if (number == 0)
				count_zero++;
		}

		if (count_zero == 1 && count_one == 3)
			cout << "A\n";
		else if (count_zero == 2 && count_one == 2)
			cout << "B\n";
		else if (count_zero == 3 && count_one == 1)
			cout << "C\n";
		else if (count_zero == 4 && count_one == 0)
			cout << "D\n";
		else if (count_zero == 0 && count_one == 4)
			cout << "E\n";
	}
}