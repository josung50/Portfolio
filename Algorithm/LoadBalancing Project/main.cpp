#include "FuncVariable.h"

queue<OrderQue> LeftBeverages;
Completed List[MAX];
Barista Barista1;
Barista Barista2;

// �� ���ᰡ �ֹ� ���� �� ��ŭ ä������ �й�Ϸ� ..
int americano, Atemp1, Btemp1;
int caffelatte, Atemp2, Btemp2;
int macchiato, Atemp3, Btemp3;
int index; // List �迭 ������ ���� index
OrderQue temp;

int main(void)
{
	index = 0;
	int n; // ���� ����
	int OrderN; // �ֹ����� ���� ����
	char* Order = new char(sizeof(char) * 30); // �ֹ��ϴ� ���
	ifstream in;
	in.open("input.txt");

	while (!in.eof()) {
		tempInit();
		in >> OrderN;

		// �ֹ��� �޴´�. //
		for (int i = 0; i < OrderN; i++)
		{
			in >> Order >> n;
			ReceiveOrder(Order, n);
			cout << n << endl;
		}
		LeftBeverages.push(temp); // �ֹ� ������ ť�� �� ����
								  // �ٸ���Ÿ���� �й� (�ٸ���Ÿ�� �� ������ ���� �ֹ� ���� ���� ���)
								  // �ð��ʴ� ������ �̿��ؼ�...
								  // A  , B------ , �Ϸ� �� �� ���� ���Ằ ī��Ʈ ����
								  // ��Ʈ�� �츮�� �� �޾� ������ ���̸� ����.
								  // �� ������ ���� �մ� �ֹ� �ޱ�.
		cout << LeftBeverages.front().Num_americano << endl;
	}

	while (!LeftBeverages.empty()) {
		Atemp1 = Atemp2 = Atemp3 = 0; // �ٸ���Ÿ1�� ���� ä���� ����...
		Btemp1 = Btemp2 = Btemp3 = 0; // �ٸ���Ÿ2�� ���� ä���� ����...
		List[index].fin_americano = americano = LeftBeverages.front().Num_americano;
		List[index].fin_caffelatte = caffelatte = LeftBeverages.front().Num_caffelatte;
		List[index].fin_macchiato = macchiato = LeftBeverages.front().Num_macchiato;

		LeftBeverages.pop();
		int complete = 0;
		while (true) {
			if (Barista1.making_time == 0) { // �ٸ���Ÿ1�� ���� ������ �ֹ� �ο�
				if (americano != 0) {
					Barista1.making_time = ame; // �Ƹ޸�ī�� ����� �ð� ����
					strcpy(Barista1.Beverage_name, "americano");
					americano--;
				}
				else if (caffelatte != 0) {
					Barista1.making_time = lat;
					strcpy(Barista1.Beverage_name, "caffelatte");
					caffelatte--;
				}
				else if (macchiato != 0) {
					Barista1.making_time = mac;
					strcpy(Barista1.Beverage_name, "macchiato");
					macchiato--;
				}
			}

			if (Barista2.making_time == 0) { // �ٸ���Ÿ2�� ���� ������ �ֹ� �ο�
				if (americano != 0) {
					Barista2.making_time = ame; // �Ƹ޸�ī�� ����� �ð� ����
					strcpy(Barista2.Beverage_name, "americano");
					americano--;
				}
				else if (caffelatte != 0) { // �� ����� �ð�
					Barista2.making_time = lat;
					strcpy(Barista2.Beverage_name, "caffelatte");
					caffelatte--;
				}
				else if (macchiato != 0) { // ������ ����� �ð�
					Barista2.making_time = mac;
					strcpy(Barista2.Beverage_name, "macchiato");
					macchiato--;
				}

			}

			// ���ϴ� �κ� //
			display(Barista1, Barista2);
			if (Barista1.making_time == 0 && Barista2.making_time == 0) { // ������ * ���ſ�...
				display(Barista1, Barista2);
			}

			// ��Ʈ ���������� ������ �︲//
			if (americano == 0 && caffelatte == 0 
				&& macchiato == 0 && Barista1.making_time == 0 
				&& Barista2.making_time == 0) {
				List[index++].finish = 1;
				break;
			}
		}
		//display(Barista1 , Barista2);
		_sleep(200);
	}

	cout << "�ֹ��Ͻ� " << index << "�� ° �޴� " <<
		"�Ƹ޸�ī�� " << List[index - 1].fin_americano <<
		"�� ī��� " << List[index - 1].fin_caffelatte <<
		"�� �����߶� " << List[index - 1].fin_macchiato <<
		"�� ���Խ��ϴ�.^0^" << endl;
}