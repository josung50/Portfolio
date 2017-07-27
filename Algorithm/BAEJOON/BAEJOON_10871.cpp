#include<iostream>
using namespace std;

int N, X;

int main() {
	cin >> N >> X;
	int number;
	while (N--) {
		cin >> number;
		if (number < X)
			cout << number << " ";
	}
}

