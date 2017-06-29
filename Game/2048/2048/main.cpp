#include<iostream>
#include<conio.h.>
#include<Windows.h>
#include<time.h>
#include<math.h>

#define TRUE 1
#define FALSE 0

#define MAP_ADJ_X 10
#define MAP_ADJ_Y 5

using namespace std;

void Menu();

/* 4x4 보드 */
void draw44();
void draw44_background();
void newnumber44();
int gameover44_check();

void draw88();
void InitBoard();
void gotoxy(int x, int y);

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR }CURSOR_TYPE;
void setcursortype(CURSOR_TYPE);

int board44[4][4];
int board88[8][8];
int select_menu_key;
int score;

void main() {
	int key;
	while (1) {
		Menu();
		if (select_menu_key == 49) {
			while (1) {
				draw44();
				key = getch();
				if (key == 114) { // R == 114 , reset
					break;
				}

				if (gameover44_check() == 0) { // 0:game_over , 1:not_over
					while (1) {
						key = getch();
						if (key == 114)
							break;
					}
					if (key == 114)
						break;
				}

				newnumber44();
			}
		}
	}
}

void Menu() {
	system("cls");
	setcursortype(NOCURSOR);

	InitBoard();

	//배경을 그림     
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y - 4);
	cout << "  ─┐┌┐││┌┐";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y - 3);
	cout << "  ┌┘││└┤├┤";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y - 2);
	cout << "  └─└┘  │└┘";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y);
	cout << "1 : Classic - 4 X 4";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 2);
	cout << "2 : Classic - 8 X 8";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 4);
	cout << " ◇ ←,→,↑,↓ : Move";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 6);
	cout << " ◇ ESC : Quit";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 8);
	cout << " ◇ Insert 1 or 2 please. : ";

	while (1) {
		select_menu_key = getch(); // 1 == 49 , 2 == 50;

		if (select_menu_key == 49) {
			draw44_background();
			break;
		}
		else if (select_menu_key == 50) {
			draw88();
			break;
		}
		else
			continue;
	}
}

void InitBoard() {
	score = 0;

	// 4*4 보드 초기화
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++)
			board44[row][col] = 0;
	}
	board44[2][3] = 8;
	board44[1][2] = 4;
	board44[1][3] = 16;
	board44[1][1] = 2;
	//board44[1][0] = 1024;

	// 8*8 보드 초기화
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++)
			board88[row][col] = 0;
	}
}

// 행은 6간격 , 열은 3간격으로 보드를 만듬
void draw44() {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (board44[row][col] == 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				gotoxy(MAP_ADJ_X + (col * 6), MAP_ADJ_Y + (row * 3));
				cout << "      ";
				gotoxy(MAP_ADJ_X + (col * 6), MAP_ADJ_Y + (row * 3) + 1);
				cout << "  ┿  ";
				gotoxy(MAP_ADJ_X + (col * 6), MAP_ADJ_Y + (row * 3) + 2);
				cout << "      ";
			}

			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), board44[row][col]%10);
				gotoxy(MAP_ADJ_X + (col * 6), MAP_ADJ_Y + (row * 3));
				cout << "┌─┐" ;
				gotoxy(MAP_ADJ_X + (col * 6), MAP_ADJ_Y + (row * 3) + 1);
				cout << " " << board44[row][col] << " ";
				gotoxy(MAP_ADJ_X + (col * 6), MAP_ADJ_Y + (row * 3) + 2);
				cout << "└─┘" ;
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	}
}

void draw44_background() {
	//배경을 그림  
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y - 4);
	cout << "  ─┐┌┐││┌┐";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y - 3);
	cout << "  ┌┘││└┤├┤";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y - 2);
	cout << "  └─└┘  │└┘";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y - 1);
	cout << "┌────────────┐";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y);
	cout << "│                        │";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 1);
	cout << "│                        │";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 2);
	cout << "│                        │";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 3);
	cout << "│                        │";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 4);
	cout << "│                        │";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 5);
	cout << "│                        │";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 6);
	cout << "│                        │";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 7);
	cout << "│                        │";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 8);
	cout << "│                        │";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 9);
	cout << "│                        │";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 10);
	cout << "│                        │    SCORE :" << score;
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 11);
	cout << "│                        │";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 12);
	cout << "└────────────┘";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 14);
	cout << " ◇ SPACEBAR : Back , R : Reset , S : Save";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 16);
	cout << " ◇ ←,→,↑,↓ : Move";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 18);
	cout << " ◇ ESC : Quit";
}

void newnumber44() {
	int number; int rand_row; int rand_col;
	if (rand() % 100 > 70)
		number = 4;
	else number = 2;

	while (1) {
		rand_row = rand() % 4; // 0~3의 값을 갖는다.
		rand_col = rand() % 4; 
		if (board44[rand_row][rand_col] == 0) {
			board44[rand_row][rand_col] = number;
			break;
		}
		else continue;
		
	}
	draw44();
}

int gameover44_check() {
	int count_block = 1;
	for(int row = 0; row < 4; row++)
		for (int col = 0; col < 4; col++) {
			if (board44[row][col] != 0)
				count_block++;
		}
	
	if (count_block >= 17) {
		gotoxy(MAP_ADJ_X + 30 , MAP_ADJ_Y + 11);
		cout << "game over";
		gotoxy(MAP_ADJ_X + 30, MAP_ADJ_Y + 12);
		cout << "Try again!! Press the R key.";
		return 0;
	}
	return 1;
}

void draw88() {

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


/* 참고 문헌 , 블로그*/
/* 커서 없애기 : http://sotooto.blogspot.kr/2010/05/setcursortype%EC%BB%A4%EC%84%9Conoff.html */
/* 난수 : http://dgblog.tistory.com/68 */

