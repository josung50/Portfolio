#include"FuncVariable.h"

// 주문 받는 내역을 큐에 넣어주는 함수 //
void ReceiveOrder(char* Order, int n) {
	if (strcmp(Order, "ame") == 0)
		temp.Num_americano = n;
	if (strcmp(Order, "lat") == 0)
		temp.Num_caffelatte = n;
	if (strcmp(Order, "mac") == 0)
		temp.Num_macchiato = n;
}

void display(Barista Barista1, Barista Barista2) {
	system("cls");
	cout << "바리스타1 " << Barista1.Beverage_name << " 진행도 :";
	for (int i = 0; i < Barista1.making_time; i++)
		cout << "*";

	cout << endl;

	cout << "바리스타2 " << Barista2.Beverage_name << " 진행도 :";
	for (int i = 0; i < Barista2.making_time; i++)
		cout << "*";
	cout << endl;

	cout << "아메리카노 " << Atemp1 + Btemp1 << "잔" << endl <<
		"카페라떼 " << Atemp2 + Btemp2 << "잔" << endl <<
		"마끼야또 " << Atemp3 + Btemp3 << "잔" << endl;

	for (int i = 0; i < index; i++) {
		if (List[i].finish == 1)
			cout << "주문하신 " << i + 1 << "번 째 메뉴 " <<
			"아메리카노 " << List[i].fin_americano <<
			"잔 카페라떼 " << List[i].fin_caffelatte <<
			"잔 마끼야또 " << List[i].fin_macchiato <<
			"잔 나왔습니다.^0^" << endl;
	}
	working(); // 1초씩 감소
}

void tempInit() {
	temp.Num_americano = 0;
	temp.Num_caffelatte = 0;
	temp.Num_macchiato = 0;
}

void working() {

	if (Barista1.making_time != 0)
		Barista1.making_time--;
	if (Barista2.making_time != 0)
		Barista2.making_time--;

	if (Barista1.making_time == 0) {
		if (strcmp(Barista1.Beverage_name, "americano") == 0) {
			if (Atemp1 == List[index].fin_americano - Btemp1) {}
			else Atemp1++;
		}
		else if (strcmp(Barista1.Beverage_name, "caffelatte") == 0) {
			if (Atemp2 == List[index].fin_caffelatte - Btemp2) {}
			else Atemp2++;
		}
		else if (strcmp(Barista1.Beverage_name, "macchiato") == 0) {
			if (Atemp3 == List[index].fin_macchiato - Btemp3) {}
			else Atemp3++;
		}
	}
	if (Barista2.making_time == 0) {
		if (strcmp(Barista2.Beverage_name, "americano") == 0) {
			if (Btemp1 == List[index].fin_americano - Atemp1) {}
			else Btemp1++;
		}
		else if (strcmp(Barista2.Beverage_name, "caffelatte") == 0) {
			if (Btemp2 == List[index].fin_caffelatte - Atemp2) {}
			else Btemp2++;
		}
		else if (strcmp(Barista2.Beverage_name, "macchiato") == 0) {
			if (Btemp3 == List[index].fin_macchiato - Atemp3) {}
			else Btemp3++;
		}
	}
	_sleep(500);
}