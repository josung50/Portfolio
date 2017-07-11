/* �˰��� 
	�־��� ���ڸ� �׷�ȭ ��Ų��. �׷�ȭ �� ���ڸ� ����Լ��� �Ἥ ���� �˻��Ѵ�.*/

#include<iostream>
#include<cstring>

using namespace std;

typedef struct splited {
	char s[25]; // �׷�ȭ�� ���ڿ�
	int length; // ���ڿ��� ����
};

class string_class {
public:
	splited splited_string[25]; // �׷�ȭ�� ���ڿ��� ���� ����ü
	int length; // �׷��� ��
	string_class() {
		length = 0;
	}
};

// �������� �׷�(�迭)���� index�� �ش��ϴ� ���ڿ��� ���� ���Ӱ� ����, �ٽ� split�ؼ� �׷�ȭ�� class�� ��ȯ�ϴ� �Լ�
string_class deleteString(string_class sc , int index);

// �־��� ��Ʈ���� �׷�ȭ �ϴ� �Լ�
string_class split(char origin_string[25]);

// �׷�ȭ�� sc�� �� ���ڿ��� �Ǵ��� �����ϴ� �Լ�
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
	return my2; // split�� ���� class ��ȯ
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