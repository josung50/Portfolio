/*
	점화식
	n이 숫자의 길이라고 하면
	n = 1 -> dp[1][0~9] = 1
	n >= 2 -> dp[i][j] = dp[i-1][j-1] + dp[i-1][j+1];
	
	앞의 수에 따라 뒤에 나오는 경우의 수는 자연스럽게 정해지기 때문
	ex )
	n = 3 일 때 제일 큰 자리 수가 2라면
	dp[3][2]를 의미하고 
	2 -> 1 즉, dp[2][1]을 이루는 경우의 수를 가져와 더 해준다.
	2 -> 1 -> 2
	2 -> 1 -> 0

	2 -> 3 즉, dp[2][0]을 이루는 경우의 수를 가져와 더 해준다.
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
