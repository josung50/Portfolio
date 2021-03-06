#include<iostream>
#include<string>
#include<conio.h.>
#include<Windows.h>
#include<time.h>
#include<math.h>
#include<vector>
using namespace std;

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR }CURSOR_TYPE;
typedef struct point { int x; int y; };
#define MAP_X 13
#define MAP_Y 0
#define LEFT 75
#define RIGHT 77
#define QUIT 113
#define RESET 114

int life;
int holding_time;
int game_over_flag;
int invincibility_status; // 별에 닿을 시 2초간 무적 상태

/* 1~12로 while문을 돌 때마다 1씩 증가,
drop()에서
100로 나눈 나머지가 0일 때는 producing1
200로 나눈 나머지가 0일 때는 producing2
500로 나눈 나머지가 0일 때는 producing3
1000로 나눈 나머지가 0일 때는 producing4 를 호출한다.*/
int drop_level;

void main_screen();
void frame(); // 내부의 x 좌표는 10 ~ 68
int limit_area(int direct); // 벽 넘기방지
void time_ac(); // 시간 계산

void production_star(); // 별 생성 , 10 ~ 68 사이의 좌표에서 별을 생성하면 된다.
void print_star(); // map에 별들을 그린다. 성능상의 문제로 drop()과 통합
int production_star_time; // 0.1초마다 별 생성
void drop(); // 별들을 떨구는 함수.

void gotoxy(int x, int y);
void setcursortype(CURSOR_TYPE c);

class human {
public:
	point head;
	point left_hand;
	point body;
	point right_hand;
	point left_leg;
	point right_leg;

	human() { // MAP_X의 중앙 : +15, MAP_Y의 맨 아래 : 20
		head.x = MAP_X + 20;		head.y = MAP_Y + 18;
		left_hand.x = MAP_X + 18;	left_hand.y = MAP_Y + 19;
		body.x = MAP_X + 20;	body.y = MAP_Y + 19;
		right_hand.x = MAP_X + 22;	right_hand.y = MAP_Y + 19;
		left_leg.x = MAP_X + 19;	left_leg.y = MAP_Y + 20;
		right_leg.x = MAP_X + 21;	right_leg.y = MAP_Y + 20;
	}

	void move(int direct) {
		switch (direct) {
		case LEFT:
			head.x--;
			left_hand.x--;
			body.x--;
			right_hand.x--;
			left_leg.x--;
			right_leg.x--;
			break;
		case RIGHT:
			head.x++;
			left_hand.x++;
			body.x++;
			right_hand.x++;
			left_leg.x++;
			right_leg.x++;
			break;
		}

	}
	void human_print() {
		gotoxy(head.x, head.y);
		cout << "○";
		gotoxy(left_hand.x, left_hand.y);
		cout << "＼";
		gotoxy(body.x, body.y);
		cout << "§";
		gotoxy(right_hand.x, right_hand.y);
		cout << "／";
		gotoxy(left_leg.x, left_leg.y);
		cout << "／";
		gotoxy(right_leg.x, right_leg.y);
		cout << "＼";
	}

	void human_cls() {
		gotoxy(head.x, head.y);
		cout << " ";
		gotoxy(left_hand.x, left_hand.y);
		cout << " ";
		gotoxy(body.x, body.y);
		cout << " ";
		gotoxy(right_hand.x, right_hand.y);
		cout << " ";
		gotoxy(left_leg.x, left_leg.y);
		cout << " ";
		gotoxy(right_leg.x, right_leg.y);
		cout << " ";
	}
};
human H;

class star {
public:
	int drop_speed;
	point Point;
	star() {
		Point.x = rand() % 58 + 10; // 10 ~ 68 좌표
		Point.y = MAP_Y + 1; // 천장
		drop_speed = rand() % 4 + 1; // 1~4의 값을 갖는다.
	}
};
vector<star> drop_star; // 최대 map에 생성되는 star의 수는 100개
vector<star>::iterator it;

int life_cut(vector<star>::iterator i);
int game_over();

/* 각 star_producing마다 떨어지는 속도의 차이가 있다.*/
void star_producing1(vector<star>::iterator i); // 1 , 제일 빠르게 떨어진다.
void star_producing2(vector<star>::iterator i); // 2
void star_producing3(vector<star>::iterator i); // 3
void star_producing4(vector<star>::iterator i); // 4 , 제일 느리게 떨어진다.

int main() {
	main_screen();
	frame();
	int key = 0;
	while (1) {
		if (game_over_flag == 1) {
			while (1) {
				key = getch();
				if (key == RESET) {
					drop_star.clear();
					game_over_flag = 0;
					system("cls");
					main_screen();
					frame();
					break;
				}
			}
			holding_time = 0;
		}
		if (kbhit()) {
			key = getch();
			switch (key) {
			case LEFT:
				if (limit_area(LEFT) == 0) {
					H.move(LEFT);
					H.human_print();
					gotoxy(MAP_X + 10, MAP_Y + 24);
					//cout << H.left_hand.x << " " << H.right_hand.x;
				}
				break;
			case RIGHT:
				if (limit_area(RIGHT) == 0) {
					H.move(RIGHT);
					H.human_print();
					gotoxy(MAP_X + 10, MAP_Y + 24);
					//cout << H.left_hand.x << " " << H.right_hand.x;
				}
				break;
			case QUIT:
				gotoxy(MAP_X + 10, MAP_Y + 23);
				return 0;
				break;
			}
		}
		drop_level += 1;
		production_star();
		//print_star();
		time_ac();
		drop();
		if (drop_level == 9000)
			drop_level = 1;
	}
}

void main_screen() {
	invincibility_status = 0;
	game_over_flag = 0;
	it = drop_star.begin();
	drop_level = 1;
	life = 5;
	holding_time = 0;
	production_star_time = 0;

	setcursortype(NOCURSOR);
	gotoxy(MAP_X, MAP_Y);
	cout << "     ■  ■        ■  ■■■■  ■■■■ ■■■■  ";
	gotoxy(MAP_X, MAP_Y + 1);
	cout << "    ■■  ■      ■  ■      ■    ■    ■     ■ ";
	gotoxy(MAP_X, MAP_Y + 2);
	cout << "   ■  ■  ■    ■   ■      ■    ■    ■      ■";
	gotoxy(MAP_X, MAP_Y + 3);
	cout << "  ■■■■  ■  ■    ■      ■    ■    ■      ■";
	gotoxy(MAP_X, MAP_Y + 4);
	cout << " ■      ■  ■■     ■      ■    ■    ■     ■ ";
	gotoxy(MAP_X, MAP_Y + 5);
	cout << "■        ■  ■       ■■■■  ■■■■ ■■■■  ";
	gotoxy(MAP_X + 6, MAP_Y + 7);
	cout << "■■■■ ■■■■■    ■      ■■■■   ";
	gotoxy(MAP_X + 6, MAP_Y + 8);
	cout << "■           ■       ■■     ■     ■";
	gotoxy(MAP_X + 6, MAP_Y + 9);
	cout << "■■■■     ■      ■  ■    ■     ■";
	gotoxy(MAP_X + 6, MAP_Y + 10);
	cout << "      ■     ■     ■■■■   ■■■■";
	gotoxy(MAP_X + 6, MAP_Y + 11);
	cout << "      ■     ■    ■      ■  ■     ■ ";
	gotoxy(MAP_X + 6, MAP_Y + 12);
	cout << "■■■■     ■   ■        ■ ■      ■";
	gotoxy(MAP_X + 9, MAP_Y + 15);
	cout << "※ Move : → , ←";
	gotoxy(MAP_X + 9, MAP_Y + 16);
	cout << "※ Quit : q";
	gotoxy(MAP_X + 9, MAP_Y + 17);
	cout << "※ Reset: r";
	gotoxy(MAP_X + 9, MAP_Y + 19);

	int key = 224;
	while (1) {
		if (kbhit()) do { key = getch(); } while (key == 224);
		gotoxy(MAP_X + 9, MAP_Y + 19);
		cout << "Press any key to start";
		Sleep(500);
		gotoxy(MAP_X + 9, MAP_Y + 19);
		cout << "                      ";
		Sleep(500);

		if (key != 224) {
			system("cls");
			break;
		}
	}
}
void frame() {
	setcursortype(NOCURSOR);
	gotoxy(MAP_X - 5, MAP_Y);
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
	for (int i = 1; i <= 20; i++) {
		gotoxy(MAP_X - 5, MAP_Y + i);
		cout << "■                                                            ■";
	}
	gotoxy(MAP_X - 5, MAP_Y + 21);
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
	gotoxy(MAP_X + 10, MAP_Y + 22);
	cout << "TIME : " << holding_time;
	gotoxy(MAP_X + 24, MAP_Y + 22);
	cout << "LIFE : " << life;

	H.human_print();
}

void time_ac() {
	clock_t time1 = clock();
	if ((time1 - holding_time) >= 1) {
		holding_time = time1;
		gotoxy(MAP_X + 17, MAP_Y + 22);
		cout << holding_time / CLOCKS_PER_SEC;
	}
}

int limit_area(int direct) { // 벽 넘기방지
	switch (direct) {
	case LEFT:
		if (H.left_hand.x <= MAP_X - 3) {
			return 1;
		}
		break;
	case RIGHT:
		if (H.right_hand.x >= MAP_X + 55) {
			return 1;
		}
		break;
	}
	return 0;
}

void production_star() { // 0.25초마다 생성
	clock_t temp_clock = clock();
	if ( (temp_clock - production_star_time) >= 250) {
		production_star_time = temp_clock;
		star temp_star;
		drop_star.push_back(temp_star);
	}
}
void print_star() {
	if (drop_star.empty() == 1)
		return;
	int size = drop_star.size();
	for (it = drop_star.begin(); it != drop_star.end(); it++) {
		gotoxy(it->Point.x, it->Point.y);
		cout << "★";
	}
	gotoxy(MAP_X + 10, MAP_Y + 25);
	cout << "star size : " << drop_star.size();
}
void drop() {
	int size = drop_star.size();
	for (it = drop_star.begin(); it != drop_star.end(); it++) {
		if (it->Point.y >= MAP_Y + 20) {
			gotoxy(it->Point.x, it->Point.y);
			cout << " ";
			it = drop_star.erase(it);
			break;
		}
		switch (it->drop_speed) {
		case 1:
			star_producing1(it);
			break;
		case 2:
			star_producing2(it);
			break;
		case 3:
			star_producing3(it);
			break;
		case 4:
			star_producing4(it);
			break;
		}
		if(invincibility_status == 0)
			life_cut(it);
		else if(drop_level % 9000 == 0) { // 무적상태 제거
			invincibility_status = 0;
			for (int i = 0; i < 50; i++) { // 사람이 깜빡이는 효과 , 잠시 게임 멈춤
				H.human_cls();
				Sleep(2);
				H.human_print();
			}
		}

		if (game_over() == 1) {
			gotoxy(MAP_X + 23, MAP_Y + 11);
			cout << "GAME OVER";
			game_over_flag = 1;
			break;
		}

	}
}
void star_producing1(vector<star>::iterator i) {
	if (drop_level % 1000 == 0) {
		gotoxy(it->Point.x , it->Point.y);
		cout << " ";
		it->Point.y += 1;
		gotoxy(it->Point.x, it->Point.y);
		cout << "★";
	}
}
void star_producing2(vector<star>::iterator i) {
	if (drop_level % 1200 == 0) {
		gotoxy(it->Point.x, it->Point.y);
		cout << " ";
		it->Point.y += 1;
		gotoxy(it->Point.x, it->Point.y);
		cout << "★";
	}
}
void star_producing3(vector<star>::iterator i) {
	if (drop_level % 2400 == 0) {
		gotoxy(it->Point.x, it->Point.y);
		cout << " ";
		it->Point.y += 1;
		gotoxy(it->Point.x, it->Point.y);
		cout << "★";
	}
}
void star_producing4(vector<star>::iterator i) {
	if (drop_level % 3000 == 0) {
		gotoxy(it->Point.x, it->Point.y);
		cout << " ";
		it->Point.y += 1;
		gotoxy(it->Point.x, it->Point.y);
		cout << "★";
	}
}
int life_cut(vector<star>::iterator i) {
	int x = i->Point.x;	int y = i->Point.y;
	if (H.head.x == x && H.head.y == y) {
		life--;
		gotoxy(MAP_X + 24, MAP_Y + 22);
		cout << "LIFE : " << life;
		invincibility_status = 1;
		return 1;
	}
	if (H.left_hand.x == x && H.left_hand.y == y) {
		life--;
		gotoxy(MAP_X + 24, MAP_Y + 22);
		cout << "LIFE : " << life;
		invincibility_status = 1;
		return 1;
	}
	if (H.right_hand.x == x && H.right_hand.y == y) {
		life--;
		gotoxy(MAP_X + 24, MAP_Y + 22);
		cout << "LIFE : " << life;
		invincibility_status = 1;
		return 1;
	}
	if (H.left_leg.x == x && H.left_leg.y == y) {
		life--;
		gotoxy(MAP_X + 24, MAP_Y + 22);
		cout << "LIFE : " << life;
		invincibility_status = 1;
		return 1;
	}
	if (H.right_leg.x == x && H.right_leg.y == y) {
		life--;
		gotoxy(MAP_X + 24, MAP_Y + 22);
		cout << "LIFE : " << life;
		invincibility_status = 1;
		return 1;
	}
	return 0;
}
int game_over() {
	if (life == 0) {
		game_over_flag = 1;
		return 1;
	}
}

void gotoxy(int x, int y) { //모니터상의 x,y 좌표로 이동시키는 함수 
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO Curinfo; // console sursor 구조체
	switch (c)
	{
	case NOCURSOR:
		Curinfo.dwSize = 1; //cursor size
		Curinfo.bVisible = FALSE; // cursor 안보임
		break;
	case SOLIDCURSOR:
		Curinfo.dwSize = 100;
		Curinfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		Curinfo.dwSize = 20;
		Curinfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Curinfo);
}