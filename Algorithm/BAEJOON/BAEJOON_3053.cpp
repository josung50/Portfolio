#include<iostream>
using namespace std;

double PI = 3.14159265358979;
double R;

int main() {
	cin >> R;
	double s_u = R*R*PI;
	double s_t = 2*R*R;
	cout << fixed; // �Ҽ����� �������� ǥ���ϰڴ�.
					// �����Ϸ��� cout.unsetf(ios::fixed);
	cout.precision(6); // �ڸ����� ǥ���Ѵ�.
	cout << s_u << "\n";
	cout << s_t;
	
}

// ���� http://pmoncode.tistory.com/20