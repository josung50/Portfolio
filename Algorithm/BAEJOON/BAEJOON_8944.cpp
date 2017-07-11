#include<iostream>
#include<cstring>
#include<math.h>

using namespace std;

int data_number[20] = { -99999, };
int data_basic[5000] = { -99999, };
int data_temp[5000] = { -99999, };
int N; int TestCases; int count_n;	int check_flag = 0;

void init_temp(int N);
void init_number();
void permutation(int begin, int end);
void swap(int* a, int* b);
void check(int N);
void make_tree_basic(int N);
void search_left_basic(int target , int index);
void search_right_basic(int target , int index);
void make_tree_temp(int N);
void search_left_temp(int target, int index);
void search_right_temp(int target, int index);

int main() {
	cin >> TestCases;
	
	while (TestCases--) {
		count_n = 0;
		init_number();
		cin >> N;
		for (int i = 1; i <= N; i++)
			cin >> data_number[i];
		make_tree_basic(N);
		permutation(1, N);
		/*
		for (int i = 0; i < 20; i++)
			cout << data_basic[i] << " ";
			*/
		cout << count_n << endl;
	}
}

void permutation(int begin, int end) {
	if (begin >= end) {
		/*
		for (int i = 1; i <= end; i++)
			cout << data_number[i];
		cout << endl;
		*/
		make_tree_temp(end);
		if(check_flag == 0)
			count_n++;
		//check(end);
		init_temp(end);
		return;
	}

	for (int i = begin; i <= end; i++) {
		swap(data_number[i],data_number[begin]);
		permutation(begin + 1, end);
		swap(data_number[begin], data_number[i]);
	}
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void make_tree_basic(int N) {
	for (int i = 1; i <= N; i++) {
		if (i == 1)
			data_basic[1] = data_number[1];
		else {
			if (data_number[i - 1] > data_number[i]) {
				search_left_basic(data_number[i], 1);
			}
			else
				search_right_basic(data_number[i], 1);

		}
	}
	/*
	for (int i = 0; i < 20; i++) {
		cout << data_basic[i] << " ";
	}
	cout << endl;
	*/
}

void search_left_basic(int target, int index) {
	int parent = index;
	if (data_basic[parent] == 0) {
		data_basic[parent] = target;
		return;
	}
	if (data_basic[parent] < target) {
		search_right_basic(target, parent * 2 + 1);
	}
	else if (data_basic[parent] > target) {
		search_left_basic(target, parent * 2);
	}
	return;
}

void search_right_basic(int target, int index) {
	int parent = index;
	if (data_basic[parent] == 0) {
		data_basic[parent] = target;
		return;
	}
	if (data_basic[parent] < target) {
		search_right_basic(target, parent * 2 + 1);
	}
	else if (data_basic[parent] > target) {
		search_left_basic(target, parent * 2);
	}
	return;
}

void make_tree_temp(int N) {
	for (int i = 1; i <= N; i++) {
		if (check_flag == 1)
			return;
		if (i == 1)
			data_temp[1] = data_number[1];
		else {
			if (data_number[i - 1] > data_number[i]) {
				search_left_temp(data_number[i], 1);
			}
			else
				search_right_temp(data_number[i], 1);

		}
	}
	/*
	for (int i = 0; i < 20; i++) {
		cout << data_temp[i] << " ";
	}
	cout << endl;
	*/
}

void search_left_temp(int target, int index) {
	if (check_flag == 1)
		return;
	int parent = index;
	if (data_temp[parent] == 0) {
		data_temp[parent] = target;
		if (data_basic[parent] != target)
			check_flag = 1;
		return;
	}
	if (data_temp[parent] < target) {
		search_right_temp(target, parent * 2 + 1);
	}
	else if (data_temp[parent] > target) {
		search_left_temp(target, parent * 2);
	}
	return;
}

void search_right_temp(int target, int index) {
	if (check_flag == 1)
		return;
	int parent = index;
	if (data_temp[parent] == 0) {
		data_temp[parent] = target;
		if (data_basic[parent] != target)
			check_flag = 1;
		return;
	}
	if (data_temp[parent] < target) {
		search_right_temp(target, parent * 2 + 1);
	}
	else if (data_temp[parent] > target) {
		search_left_temp(target, parent * 2);
	}
	return;
}

void check(int N) {
	int tree_size2 = 0;
	tree_size2 = pow(2, N - 1) - 1;
	for (int i = 1; i <= tree_size2; i++)
		if (data_basic[i] != data_temp[i])
			return;
	count_n++;
	return;
}

void init_temp(int N) {
	check_flag = 0;
	int tree_size = pow(2, N - 1) - 1;
	for (int i = 1; i <= tree_size; i++)
		data_temp[i] = 0;
}

void init_number() {
	for (int i = 1; i <= 20; i++)
		data_number[i] = 0;
	for (int i = 1; i <= 5000; i++)
		data_basic[i] = 0;
}