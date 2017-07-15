#include<iostream>
#include<deque>
#include<algorithm>
using namespace std;

struct document {
	int importance;
	int sequence;
};

int TestCases;	int M;	int N;
deque<document> dq;
document temp_document;
document most_importance_document;
int order[100];
int order_index;

void check();
void find_most_importance();

bool comparefunction(document a, document b) {
	return a.importance > b.importance;
}

int main() {
	cin >> TestCases;
	int sequence;
	while (TestCases--) {
		dq.clear();
		sequence = 0;
		most_importance_document.importance = 0;
		most_importance_document.sequence = -1;
		for (int i = 0; i < N; i++)
			order[i] = 0;
		order_index = 0;

		cin >> N >> M;
		for (int i = 0; i < N; i++) {
			cin >> temp_document.importance;
			temp_document.sequence = sequence++;
			dq.push_front(temp_document);
		}
		
		for (int i = 0; i < N; i++) {
			check();
		}

		for (int i = 0; i < N; i++) {
			if (order[i] == M + 1) {
				cout << i+1 << "\n";
				break;
			}
		}
	}
}

void check() {
	int size = dq.size();
	document temp;

	find_most_importance();
	for (int i = 0; i < size; i++) {
		if (dq.back().importance >= most_importance_document.importance) {
			//cout << dq.back().sequence << " ";
			order[order_index++] = dq.back().sequence+1;
			dq.pop_back();
			most_importance_document.importance = 0;
			most_importance_document.sequence = -1;
			return;
		}
		else {
			temp = dq.back();
			dq.pop_back();
			dq.push_front(temp);
		}
	}
}

void find_most_importance() {
	int size = dq.size();
	document temp;
	for (int i = 0; i < size; i++) {
		if (dq.back().importance >= most_importance_document.importance)
			most_importance_document = dq.back();
		temp = dq.back();
		dq.pop_back();
		dq.push_front(temp);
	}
	//cout << "most importance : " << most_importance_document.importance << "\n";
}