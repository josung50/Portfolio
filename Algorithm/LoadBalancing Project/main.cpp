#include "FuncVariable.h"

queue<OrderQue> LeftBeverages;
Completed List[MAX];
Barista Barista1;
Barista Barista2;

// 각 음료가 주문 받은 것 만큼 채워지면 분배완료 ..
int americano, Atemp1, Btemp1;
int caffelatte, Atemp2, Btemp2;
int macchiato, Atemp3, Btemp3;
int index; // List 배열 접근을 위한 index
OrderQue temp;

int main(void)
{
	index = 0;
	int n; // 음료 갯수
	int OrderN; // 주문받은 음료 종류
	char* Order = new char(sizeof(char) * 30); // 주문하는 사람
	ifstream in;
	in.open("input.txt");

	while (!in.eof()) {
		tempInit();
		in >> OrderN;

		// 주문을 받는다. //
		for (int i = 0; i < OrderN; i++)
		{
			in >> Order >> n;
			ReceiveOrder(Order, n);
			cout << n << endl;
		}
		LeftBeverages.push(temp); // 주문 내용이 큐에 들어가 있음
								  // 바리스타에게 분배 (바리스타가 일 없으면 다음 주문 받을 음료 배분)
								  // 시간초는 슬립을 이용해서...
								  // A  , B------ , 완료 될 때 마다 음료별 카운트 증가
								  // 세트는 우리가 다 받아 놨으니 모이면 성공.
								  // 다 끝나면 다음 손님 주문 받기.
		cout << LeftBeverages.front().Num_americano << endl;
	}

	while (!LeftBeverages.empty()) {
		Atemp1 = Atemp2 = Atemp3 = 0; // 바리스타1로 부터 채워진 음료...
		Btemp1 = Btemp2 = Btemp3 = 0; // 바리스타2로 부터 채워진 음료...
		List[index].fin_americano = americano = LeftBeverages.front().Num_americano;
		List[index].fin_caffelatte = caffelatte = LeftBeverages.front().Num_caffelatte;
		List[index].fin_macchiato = macchiato = LeftBeverages.front().Num_macchiato;

		LeftBeverages.pop();
		int complete = 0;
		while (true) {
			if (Barista1.making_time == 0) { // 바리스타1이 쉬고 있으면 주문 부여
				if (americano != 0) {
					Barista1.making_time = ame; // 아메리카노 만드는 시간 ㄱㄱ
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

			if (Barista2.making_time == 0) { // 바리스타2이 쉬고 있으면 주문 부여
				if (americano != 0) {
					Barista2.making_time = ame; // 아메리카노 만드는 시간 ㄱㄱ
					strcpy(Barista2.Beverage_name, "americano");
					americano--;
				}
				else if (caffelatte != 0) { // 라떼 만드는 시간
					Barista2.making_time = lat;
					strcpy(Barista2.Beverage_name, "caffelatte");
					caffelatte--;
				}
				else if (macchiato != 0) { // 마꺄또 만드는 시간
					Barista2.making_time = mac;
					strcpy(Barista2.Beverage_name, "macchiato");
					macchiato--;
				}

			}

			// 일하는 부분 //
			display(Barista1, Barista2);
			if (Barista1.making_time == 0 && Barista2.making_time == 0) { // 마지막 * 제거용...
				display(Barista1, Barista2);
			}

			// 세트 맞춰줬으니 진동벨 울림//
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

	cout << "주문하신 " << index << "번 째 메뉴 " <<
		"아메리카노 " << List[index - 1].fin_americano <<
		"잔 카페라떼 " << List[index - 1].fin_caffelatte <<
		"잔 마끼야또 " << List[index - 1].fin_macchiato <<
		"잔 나왔습니다.^0^" << endl;
}