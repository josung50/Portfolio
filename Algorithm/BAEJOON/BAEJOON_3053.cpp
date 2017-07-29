#include<iostream>
using namespace std;

double PI = 3.14159265358979;
double R;

int main() {
	cin >> R;
	double s_u = R*R*PI;
	double s_t = 2*R*R;
	cout << fixed; // 소수점을 고정시켜 표현하겠다.
					// 해제하려면 cout.unsetf(ios::fixed);
	cout.precision(6); // 자리수를 표현한다.
	cout << s_u << "\n";
	cout << s_t;
	
}

// 참고 http://pmoncode.tistory.com/20