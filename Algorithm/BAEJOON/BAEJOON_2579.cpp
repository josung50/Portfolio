#include<iostream>
using namespace std;

int stairs[301];
int dp[301][301];

int n;

int compare_max(int i, int j);
void print();

int main() {
	cin >> n;
	stairs[0] = 0;
	for (int i = 1; i <= n; i++)
		cin >> stairs[i];

	/* dp 초기값 */
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++)
		dp[i][i] = stairs[i];


	/* dp 채우기 */		
	for (int i = n; i >= 1; i--) {
		for (int j = i; j <= n; j++) {
			if ( (j - i) == 1)
				dp[i][j] = stairs[i] + stairs[j];
			else if ((j - i) >= 2)
				dp[i][j] = compare_max(i, j) + stairs[j];
		}
	}


	cout << dp[1][n];
	//print();
}

int compare_max(int i, int j) {
	if (dp[i][j - 2] >= stairs[j - 1] + dp[i][j - 3])
		return dp[i][j - 2];
	else return (stairs[j - 1] + dp[i][j - 3]);
}

void print() {
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << dp[i][j] << " ";
		cout << "\n";
	}
}