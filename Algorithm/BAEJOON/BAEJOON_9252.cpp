#include<iostream>
#include<cstring>
using namespace std;

#define MAX_LENGTH 1000
#define MAX(a,b) ((a) > (b) ? (a) : (b))

int L[MAX_LENGTH][MAX_LENGTH], S[MAX_LENGTH][MAX_LENGTH];

int lengthLCS(char s[], char t[], int m, int n);
void printLCS(char s[], char t[], int m, int n);

int main() {
	char s[1000];
	char t[1000];
	cin >> s >> t;
	int length_s = strlen(s);
	int length_t = strlen(t);
	lengthLCS(s, t, length_s, length_t);
	cout << L[length_s][length_t] << "\n";
	printLCS(s, t, length_s, length_t);

	cout << "\n";
	for (int i = 0; i <= length_s; i++) {
		for (int j = 0; j <= length_s; j++)
			cout << S[i][j] << " ";
		cout << "\n";
	}
}

int lengthLCS(char s[], char t[], int m, int n) {
	int i, j;

	/* base case */
	for (i = 0; i <= m; i++)
		L[i][0] = 0;
	for (i = 0; i <= m; i++)
		L[0][i] = 0;

	for (i = 1; i <= m; i++)
		for (j = 1; j <= n; j++) {
			if (s[i - 1] == t[j - 1]) {
				L[i][j] = L[i - 1][j - 1] + 1;
				S[i][j] = 0; // 대각선 의미
			}
			else {
				L[i][j] = MAX(L[i][j - 1], L[i - 1][j]);
				if (L[i][j] == L[i][j - 1])
					S[i][j] = 1; /// 왼쪽에서 온다.
				else
					S[i][j] = 2; // 위에서 내려온다.
			}
		}
	
	return L[m][n];
}

// 바텀 업 어프로치 방식
void printLCS(char s[], char t[], int m, int n) {
	if (m == 0 || n == 0)
		return;
	if (S[m][n] == 0)
	{
		printLCS(s, t, m - 1, n - 1);
		cout << s[m - 1];
	}
	else if (S[m][n] == 1)
		printLCS(s, t, m, n - 1);
	else if (S[m][n] == 2)
		printLCS(s, t, m - 1, n);
}