#include<iostream>
#include<list>
using namespace std;

/* 문제 : 조세퍼스 문제는 다음과 같다.

1번부터 N번까지 N명의 사람이 원을 이루면서 앉아있고, 양의 정수 M(≤ N)이 주어진다. 이제 순서대로 M번째 사람을 제거한다. 한 사람이 제거되면 남은 사람들로 이루어진 원을 따라 이 과정을 계속해 나간다. 이 과정은 N명의 사람이 모두 제거될 때까지 계속된다. 원에서 사람들이 제거되는 순서를 (N, M)-조세퍼스 순열이라고 한다. 예를 들어 (7, 3)-조세퍼스 순열은 <3, 6, 2, 7, 5, 1, 4>이다.

N과 M이 주어지면 (N,M)-조세퍼스 순열을 구하는 프로그램을 작성하시오.

입력 : 첫째 줄에 N과 M이 빈 칸을 사이에 두고 순서대로 주어진다. (1 ≤ M ≤ N ≤ 1,000)
7 3
출력 : <3, 6, 2, 7, 5, 1, 4>
*/

list<int> LIST;
list<int>::iterator it; // iterator 반복자

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
	while(1) {// end()는 마지막 값 다음 주소를 반환.
		count_M++;
		if (count_M == M) {
			cout << *it;
			cout_n++;
			it = LIST.erase(it); // erase로 주소를 제거 했기 때문에 it으로 다시 안받으면
									// it++를 할 수 없다.
			if (it == LIST.end()) // 끝의 숫자가 제거 될 경우 begin으로 회기
				it = LIST.begin();
			count_M = 1;

			if (cout_n == N) // 모든 수 출력
				break;
			cout << ", ";
		}
		it++;

		if (it == LIST.end()) { // 처음으로 회기
			it = LIST.begin();
		}
	}
	cout << ">";
}