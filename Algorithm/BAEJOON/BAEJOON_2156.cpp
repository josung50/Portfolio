#include<iostream>
using namespace std;

/* ��ȭ�� 
������ �� �� -> wine
���� �������� �ִ� �� -> s

n = 0 -> s[0] = 0, wine[0] = 0;
n = 1 -> s[1] = wine[1];
n = 2 -> s[2] = wine[1] + wine[2];
n >= 3 -> s[n] = MAX( s[n-3] + wine[n-1] + wine[n], ���� 3���� ���ô� ��츦 ���ϱ� ����
						s[n-1], �ִ밪 ���� �ȵǴ� ��� ����
						s[n-2] + wine[n]) // ���� 3�� ���ô� ��� ���� �� �ִ밪�� ������ �ȵǴ� ��� ����

						��, s[n]�� �ִ밪�� �ǹ��ϱ�� ������ wine[n] Ȥ�� wine[n-1] wine[n-2]�� ���̴��� �ȸ��̴����� �𸥴�.
						�̸� �� ����ؾ� �Ѵ�.
						���� : http://blog.naver.com/PostView.nhn?blogId=occidere&logNo=220791788953
*/

int max(int a, int b, int c) {
	if (a > b && a > c) {
		return a;
	}
	else if (b > c)
		return b;
	else return c;
}

int n;
int* wine;
int* s;

void init();
int drink(int n);

int main() {
	cin >> n;
	init();
	cout << drink(n);
}

void init() {
	/* base case ���*/

	wine = new int[n+1];	wine[0] = 0;
	s = new int[n+1];	s[0] = 0;
	for (int i = 1; i <= n; i++) {
		cin >> wine[i];
		s[i] = 0;
	}

	s[1] = wine[1];
	s[2] = s[1] + wine[2];
}

int drink(int n) {
	for (int i = 3; i <= n; i++) {
		s[i] = max(s[i - 3] + wine[i - 1] + wine[i],
			s[i - 1],
			s[i - 2] + wine[i]);
	}

	return s[n];
}