#include<iostream>
using namespace std;

#define MAX_COINS 101
#define MAX_CHANGE 10001

int available_coins[MAX_COINS];
int n, k;

int countCoinExchange(int coins[], int numDiffCoins, int change);

int main() {
	cin >> n >> k;
	
	available_coins[0] = 0;
	for (int i = 1; i <= n; i++)
		cin >> available_coins[i];
	cout << countCoinExchange(available_coins, n, k) << "\n";
}

int countCoinExchange(int coins[], int numDiffCoins, int change) {
	int i, j, numComb;
	int** N = new int*[numDiffCoins+1];
	for (int i = 0; i <= numDiffCoins; i++)
		N[i] = new int[change+1];

	/* base cases */
	N[0][0] = 1;
	for (i = 1; i <= numDiffCoins; i++)
		N[i][0] = 1;
	for (i = 1; i <= change; i++)
		N[0][i] = 0;

	for (i = 1; i <= numDiffCoins; i++)
		for (j = 1; j <= change; j++)
		{ // numComb == Cn을 제외한 경우의 수를 의미
			if (j - coins[i] < 0) /* base case */
				numComb = 0;
			else
				numComb = N[i][j - coins[i]];
			N[i][j] = N[i - 1][j] + numComb;
		}

	
	/*
	for (int i = 0; i <= numDiffCoins; i++) {
		for (int j = 0; j <= change; j++)
			cout << N[i][j] << " ";
		cout << "\n";
	}
	*/

	return N[numDiffCoins][change];
}