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

vector<int> VEC;
vector<int>::iterator it;

int N;	int M;
int count_M = 0;
int cout_n = 0;
int number;

int main() {
	cin >> N >> M;

	number = 1;
	for (int i = 0; i < N; i++) {
		VEC.push_back(number++);
	}

	it = VEC.begin();
	cout << "<";
	while (VEC.empty() == 0) {
		count_M++;
		if (count_M == M) {
			count_M = 1;
			cout << *it;

			cout_n++;
			it = VEC.erase(it);
			if (it == VEC.end()) // ó������ ȸ��
				it = VEC.begin();

			if (cout_n == N)
				break;
			cout << ", ";
		}

		it++;
		if (it == VEC.end()) // ó������ ȸ��
			it = VEC.begin();
	}
	cout << ">";
}