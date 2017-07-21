#include<iostream>
using namespace std;

/* µ¿Àû°èÈ¹ -> Çà·Ä°ö¼À½ÄÀ» »ı°¢ÇÏÀÚ. */

int TestCases;
int n;
int number[501];
int** dp;

#define min(a, b) (((a) < (b)) ? (a) : (b))

void init();
void make_dp();
void print();

int main() {
	cin >> TestCases;
	while (TestCases--) {
		cin >> n;
		init();
		make_dp();
		//print();
	}
}

void init() {
	dp = new int*[n + 1];
	for (int i = 0; i <= n; i++)
		dp[i] = new int[n + 1];

	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			dp[i][j] = 0;


	number[0] = 0;
	for (int i = 1; i <= n; i++) {
		cin >> number[i];
	}
	for (int i = 1; i <= n; i++) {
		number[i] += number[i - 1];
	}

	for (int i = 1; i <= n; i++)
		dp[i][i] = 0;
}

void make_dp() {
	for(int i=n-1; i>=1; i--)
		for (int j = i + 1; j <= n; j++) {
			dp[i][j] = 10000000;
			for (int k = i; k < j; k++) {
				if (i + 1 == j) {
					dp[i][j] = number[j] - number[i - 1];
					continue;
				}
				else {
					dp[i][j] = min(dp[i][j], (dp[i][k] + dp[k + 1][j] + number[j] - number[i - 1]) );
				}
			}
		}
	cout << dp[1][n] << "\n";
}

void print() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << dp[i][j] << "   ";
		cout << "\n";
	}
}