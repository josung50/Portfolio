#include<iostream>
#include<list>
using namespace std;

/* ���� : �����۽� ������ ������ ����.

1������ N������ N���� ����� ���� �̷�鼭 �ɾ��ְ�, ���� ���� M(�� N)�� �־�����. ���� ������� M��° ����� �����Ѵ�. �� ����� ���ŵǸ� ���� ������ �̷���� ���� ���� �� ������ ����� ������. �� ������ N���� ����� ��� ���ŵ� ������ ��ӵȴ�. ������ ������� ���ŵǴ� ������ (N, M)-�����۽� �����̶�� �Ѵ�. ���� ��� (7, 3)-�����۽� ������ <3, 6, 2, 7, 5, 1, 4>�̴�.

N�� M�� �־����� (N,M)-�����۽� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է� : ù° �ٿ� N�� M�� �� ĭ�� ���̿� �ΰ� ������� �־�����. (1 �� M �� N �� 1,000)
7 3
��� : <3, 6, 2, 7, 5, 1, 4>
*/

list<int> LIST;
list<int>::iterator it; // iterator �ݺ���

int N;	int M;
int count_M = 0;
int cout_n = 0;
int number;

int main() {
	cin >> N >> M;

	number = 1;
	for (int i = 0; i < N; i++) {
		LIST.push_back(number++);
	}

	it = LIST.begin();
	cout << "<";
	while(1) {// end()�� ������ �� ���� �ּҸ� ��ȯ.
		count_M++;
		if (count_M == M) {
			cout << *it;
			cout_n++;
			it = LIST.erase(it); // erase�� �ּҸ� ���� �߱� ������ it���� �ٽ� �ȹ�����
									// it++�� �� �� ����.
			if (it == LIST.end()) // ���� ���ڰ� ���� �� ��� begin���� ȸ��
				it = LIST.begin();
			count_M = 1;

			if (cout_n == N) // ��� �� ���
				break;
			cout << ", ";
		}
		it++;

		if (it == LIST.end()) { // ó������ ȸ��
			it = LIST.begin();
		}
	}
	cout << ">";
}