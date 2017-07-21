/*
	��ȭ��
	n�� ������ ���̶�� �ϸ�
	n = 1 -> dp[1][0~9] = 1
	n >= 2 -> dp[i][j] = dp[i-1][j-1] + dp[i-1][j+1];
	
	���� ���� ���� �ڿ� ������ ����� ���� �ڿ������� �������� ����
	ex )
	n = 3 �� �� ���� ū �ڸ� ���� 2���
	dp[3][2]�� �ǹ��ϰ� 
	2 -> 1 ��, dp[2][1]�� �̷�� ����� ���� ������ �� ���ش�.
	2 -> 1 -> 2
	2 -> 1 -> 0

	2 -> 3 ��, dp[2][0]�� �̷�� ����� ���� ������ �� ���ش�.
	2 -> 3 -> 4
	2 -> 3 -> 2

	dp[3][2] = dp[2][1] + dp[2][3]
*/

#include<iostream>
using namespace std;

const int mod = 1e9;

int n;
long long dp[101][10];

void print();

int main() {
	cin >> n;
	print();
}

void print() {

	dp[1][0] = 1;
	for (int i = 1; i <= 9; i++) {
		dp[1][i] = 1;
	}

	if(n >= 2) {
		for (int i = 2; i <= n; i++) {
			for (int j = 0; j <= 9; j++) {
				if (j == 0)
					dp[i][j] = dp[i - 1][j + 1] % mod;
				else if (j == 9)
					dp[i][j] = dp[i - 1][j - 1] % mod;
				else
					dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1] % mod;
			}
		}
	}

	long long sum = 0;

	for (int i = 1; i <= 9; i++) {
		//cout << dp[n][i] << " ";
		sum += dp[n][i];
	}
	cout << sum%mod;
}
