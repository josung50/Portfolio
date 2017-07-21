#include<iostream>
using namespace std;

int number[100];
int a, b, c;
int count_jump;

void check_position();
int jump_where();

int main() {
	count_jump = 0;
	cin >> a >> b >> c;

	while (1) {
		int jump_position = jump_where();
		if (jump_position == 0)
			break;
		else if (jump_position == 1)
			c = a + 1;
		else if (jump_position == 2)
			a = c - 1;
		count_jump++;
		check_position();
	}
	cout << count_jump;
}

void check_position() {
	int big, mid, small;
	if (a > b && a > c) {
		big = a;
		small = ((b < c) ? b : c);
		if (small == b)
			mid = c;
		else mid = b;
	}
	else if (b > c) {
		big = b;
		small = ((a < c) ? a : c);
		if (small == c)
			mid = a;
		else mid = c;
	}
	else {
		big = c;
		small = ((a < b) ? a : b);
		if (small == a)
			mid = b;
		else mid = a;
	}
	
	a = small;
	b = mid;
	c = big;
}

int jump_where() {
	int left = abs(a - b);
	int right = abs(b - c);
	if (left == 1 && right == 1) // ¶Û °ø°£ÀÌ ¾øÀ½
		return 0;
	if (left <= right) // b c »çÀÌ·Î a°¡ ¶Ü
		return 2;
	else // a b »çÀÌ·Î c°¡ ¶Ü
		return 1;
}