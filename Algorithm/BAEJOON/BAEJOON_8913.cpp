/* 알고리즘 
	주어진 문자를 그룹화 시킨다. 그룹화 된 문자를 재귀함수를 써서 전부 검사한다.*/

#include<iostream>
#include<cstring>

using namespace std;

typedef struct splited {
	char s[25]; // 그룹화된 문자열
	int length; // 문자열의 길이
};

class string_class {
public:
	splited splited_string[25]; // 그룹화된 문자열을 갖는 구조체
	int length; // 그룹의 수
	string_class() {
		length = 0;
	}
};

// 나누어진 그룹(배열)에서 index에 해당하는 문자열을 빼고 새롭게 조합, 다시 split해서 그룹화된 class를 반환하는 함수
string_class deleteString(string_class sc , int index);

// 주어진 스트링을 그룹화 하는 함수
string_class split(char origin_string[25]);

// 그룹화된 sc가 빈 문자열이 되는지 검출하는 함수
int extraction(string_class sc);

int main() {
	int TestCases;
	cin >> TestCases;

	while (TestCases--) {
		char origin_string[25] = { 0, };
		cin >> origin_string;

		string_class my = string_class();
		my = split(origin_string);

		cout << extraction(my) << endl;

	}
}

string_class split(char origin_string[25]) {
	string_class returnClass = string_class();
	int index = 0; int index_inner = 0;
	
	returnClass.splited_string[index].s[index_inner] = origin_string[0];
	index_inner++;

	for (int i = 1; i <= strlen(origin_string); i++) {
		if (origin_string[i - 1] == origin_string[i]) {
			returnClass.splited_string[index].s[index_inner] = origin_string[i];
			index_inner++;
		}
		else {
			returnClass.splited_string[index].length = index_inner;
			index_inner = 0;
			index++;
			returnClass.splited_string[index].s[index_inner] = origin_string[i];
			index_inner++;
		}
	}

	returnClass.length = index;
	/*
	for (int i = 0; i < index; i++) {
		for (int j = 0; j < splited_string[i].length; j++)
			cout << splited_string[i].s[j];
		cout << endl;
	}
	*/

	return returnClass;
}

string_class deleteString(string_class sc , int index) {
	char temp[25] = { 0, };
	int temp_index = 0;

	for (int i = 0; i < sc.length; i++) {
		if (i != index) {
			for (int j = 0; j < sc.splited_string[i].length; j++) {
				temp[temp_index] = sc.splited_string[i].s[j];
				temp_index++;
			}
		}
	}
	string_class my2 = string_class();
	my2 = split(temp);
	return my2; // split이 끝난 class 반환
}

int extraction(string_class sc) {
	for (int i = 0; i < sc.length; i++) {
		if (sc.splited_string[i].length >= 2) {
			if (extraction(deleteString(sc, i)) == 0)
				continue;
			else
				return 1;
		}
	}

	if (sc.length == 0)
		return 1;
	return 0;
}