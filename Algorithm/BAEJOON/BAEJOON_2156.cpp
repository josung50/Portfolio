#include<iostream>
using namespace std;

/* 점화식 
포도잔 의 양 -> wine
마신 포도잔의 최대 양 -> s

n = 0 -> s[0] = 0, wine[0] = 0;
n = 1 -> s[1] = wine[1];
n = 2 -> s[2] = wine[1] + wine[2];
n >= 3 -> s[n] = MAX( s[n-3] + wine[n-1] + wine[n], 연속 3잔을 마시는 경우를 피하기 위함
						s[n-1], 최대값 도움에 안되는 경우 방지
						s[n-2] + wine[n]) // 연속 3잔 마시는 경우 방지 및 최대값에 도움이 안되는 경우 배제

						즉, s[n]은 최대값을 의미하기는 하지만 wine[n] 혹은 wine[n-1] wine[n-2]를 마셨는지 안마셨는지는 모른다.
						이를 잘 고려해야 한다.
						참고 : http://blog.naver.com/PostView.nhn?blogId=occidere&logNo=220791788953
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
	/* base case 잡기*/

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