#include<iostream>
#include<queue>
using namespace std;

/* ���� : �����۽� ������ ������ ����.

1������ N������ N���� ����� ���� �̷�鼭 �ɾ��ְ�, ���� ���� M(�� N)�� �־�����. ���� ������� M��° ����� �����Ѵ�. �� ����� ���ŵǸ� ���� ������ �̷���� ���� ���� �� ������ ����� ������. �� ������ N���� ����� ��� ���ŵ� ������ ��ӵȴ�. ������ ������� ���ŵǴ� ������ (N, M)-�����۽� �����̶�� �Ѵ�. ���� ��� (7, 3)-�����۽� ������ <3, 6, 2, 7, 5, 1, 4>�̴�.

N�� M�� �־����� (N,M)-�����۽� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է� : ù° �ٿ� N�� M�� �� ĭ�� ���̿� �ΰ� ������� �־�����. (1 �� M �� N �� 1,000)
7 3
��� : <3, 6, 2, 7, 5, 1, 4>
*/

queue<int> que;

int N;	int M;
int count_M = 0;
int cout_n = 0;
int number;

int main() {
	int temp;
	cin >> N >> M;

	number = 1;
	for (int i = 0; i < N; i++) {
		que.push(number++);
	}
	
	cout << "<";
	while (que.empty() == 0) {
		count_M++;
		if (count_M == M) {
			cout << que.front();
			que.pop();
			count_M = 0;
			cout_n++;
			if (cout_n == N)
				break;
			cout << ", ";
		}
		
		else {
			temp = que.front();
			que.pop();
			que.push(temp);
		}
	}
	cout << ">";
}