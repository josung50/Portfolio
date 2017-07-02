#include<iostream>
#include<conio.h.>
#include<Windows.h>
#include<time.h>
#include<math.h>
#include<fstream>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

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
void moving44(int key);

void draw88();

void InitBoard();
void gotoxy(int x, int y);
int load();
void save();
void back();

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR }CURSOR_TYPE;
void setcursortype(CURSOR_TYPE);

int board44[4][4];
int board44_backup[4][4];
int board88[8][8];
int select_menu_key;
int score;

void main() {
	int key;
	while (1) {
		Menu();
		if (select_menu_key == 27) { // quit
			return;
		}
		if (select_menu_key == 49) { // 4x4
			while (1) {
				draw44();
				key = getch();
				if (key == 114) { // R == 114 , reset
					break;
				}
				else if (key == 27) { // quit
					gotoxy(MAP_ADJ_X + 30, MAP_ADJ_Y + 11);
					return;
				}
				else if (key == 115) { // save
					save();
				}
				else if (key == 8) { // back
					back();
				}
				else {
					key = getch();; // 방향키의 경우 2번 getch를 받아야 한다.
					if (key == LEFT || key == RIGHT || key == DOWN || key == UP) {
						moving44(key);
						newnumber44();
					}
					else continue;
				}

				/* Menu 호출을 하기위해 break을 2번 건다. 첫 번째 break는 r을 계속적으로 입력받기 위한 break.*/
				if (gameover44_check() == 0) { // 0:game_over , 1:not_over
					while (1) {
						key = getch();
						if (key == 114)
							break;
					}
					if (key == 114)
						break;
				}
			}
		}
		else if (select_menu_key == 50) { // 8x8
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
	//gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 2);
	//cout << "2 : Classic - 8 X 8";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 2);
	cout << " ◇ ←,→,↑,↓ : Move";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 4);
	cout << " ◇ ESC : Quit , L : Load";
	gotoxy(MAP_ADJ_X - 2, MAP_ADJ_Y + 6);
	cout << " ◇ Insert 1 please.";
	gotoxy(MAP_ADJ_X + 15, MAP_ADJ_Y + 8);

	while (1) {
		select_menu_key = getch(); // 1 == 49 , 2 == 50; , quit == 27; , load == 108

		if (select_menu_key == 49) {
			draw44_background();
			break;
		}
		else if (select_menu_key == 50) {
			draw88();
			break;
		}
		else if (select_menu_key == 27) {
			return;
		}
		else if (select_menu_key == 108) {
			if (load()) {
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						board44_backup[i][j] = board44[i][j];
				draw44_background();
				select_menu_key = 49;
				return;
			}
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
		gotoxy(MAP_ADJ_X + 30 , MAP_ADJ_Y + 10);
		cout << "SCORE :" << score;
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
	cout << "│                        │";
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

void moving44(int key) {
	int row = 0; int col = 0; int temp_col = -1; int temp_row = -1;

	/* back을 위한 보드 저장 */
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			board44_backup[i][j] = board44[i][j];

	switch (key) {
	/* i = j - 1에 유의*/
	/* 합치기 - 행 또는 열에서 보드가 0이 아닌 경우의 좌표를 저장, 
	그 이후에 나오는 값 중 좌표에 저장한 값과 같으면 더하고 그렇지 않으면
	새로 나온 값의 좌표를 새로 탐색을 시작하는 곳으로 저장*/
	/* 옮기기 - 빈칸의 좌표를 저장, 값이 있는 곳을 저장하고 서로 swap을 한다.
	이 후, 다음 인덱스부터 다시 탐색하여 반복*/
	case LEFT:
		/* 합치기 */
		for (row = 0; row < 4; row++) {
			for (int i = 0; i < 4; i++) {
				if (board44[row][i] == 0)
					continue;
				else {
					for (int j = i + 1; j < 4; j++) {
						if (board44[row][j] == 0)
							continue;
						else if (board44[row][i] != board44[row][j]) {
							i = j - 1;
							break;
						}
						else if (board44[row][i] == board44[row][j]) {
							board44[row][i] = board44[row][i] * 2;
							score += board44[row][i];
							board44[row][j] = 0;
							i = j-1;
							break;
						}
					}
				}
			}
		}

		/* 옮기기 */
		for (row = 0; row < 4; row++) {
			for (int i = 0; i < 4; i++) {
				temp_col = -1;
				for (int j = i; j < 4; j++) {
					if (board44[row][j] == 0 && temp_col < 0) {
						temp_col = j;
						continue;
					}
					if (board44[row][j] != 0 && temp_col >= 0) {
						board44[row][temp_col] = board44[row][j];
						board44[row][j] = 0;
						break;
					}
				}
			}
		}
		break;

	/* i = j + 1에 유의 */
	case RIGHT:
		/* 합치기 */
		for (row = 0; row < 4; row++) {
			for (int i = 3; i >= 0; i--) {
				if (board44[row][i] == 0)
					continue;
				else {
					for (int j = i - 1; j >= 0; j--) {
						if (board44[row][j] == 0)
							continue;
						else if (board44[row][i] != board44[row][j]) {
							i = j + 1;
							break;
						}
						else if (board44[row][i] == board44[row][j]) {
							board44[row][i] = board44[row][i] * 2;
							score += board44[row][i];
							board44[row][j] = 0;
							i = j;
							break;
						}
					}
				}
			}
		}

		/* 옮기기 */
		for (row = 0; row < 4; row++) {
			for (int i = 3; i >= 0; i--) {
				temp_col = -1;
				for (int j = i; j >= 0; j--) {
					if (board44[row][j] == 0 && temp_col < 0) {
						temp_col = j;
						continue;
					}
					if (board44[row][j] != 0 && temp_col >= 0) {
						board44[row][temp_col] = board44[row][j];
						board44[row][j] = 0;
						break;
					}
				}
			}
		}
		break;

	case DOWN:
		/* 합치기 */
		for (col = 0; col < 4; col++) {
			for (int i = 3; i >= 0; i--) {
				if (board44[i][col] == 0)
					continue;
				else {
					for (int j = i - 1; j >= 0; j--) {
						if (board44[j][col] == 0)
							continue;
						else if (board44[i][col] != board44[j][col]) {
							i = j + 1;
							break;
						}
						else if (board44[i][col] == board44[j][col]) {
							board44[i][col] = board44[i][col] * 2;
							score += board44[i][col];
							board44[j][col] = 0;
							i = j;
							break;
						}
					}
				}
			}
		}

		/* 옮기기 */
		for (col = 0; col < 4; col++) {
			for (int i = 3; i >= 0; i--) {
				temp_row = -1;
				for (int j = i; j >= 0; j--) {
					if (board44[j][col] == 0 && temp_row < 0) {
						temp_row = j;
						continue;
					}
					if (board44[j][col] != 0 && temp_row >= 0) {
						board44[temp_row][col] = board44[j][col];
						board44[j][col] = 0;
						break;
					}
				}
			}
		}
		break;

	case UP:
		/* 합치기 */
		for (col = 0; col < 4; col++) {
			for (int i = 0; i < 4; i++) {
				if (board44[i][col] == 0)
					continue;
				else {
					for (int j = i + 1; j < 4; j++) {
						if (board44[j][col] == 0)
							continue;
						else if (board44[i][col] != board44[j][col]) {
							i = j - 1;
							break;
						}
						else if (board44[i][col] == board44[j][col]) {
							board44[i][col] = board44[i][col] * 2;
							score += board44[i][col];
							board44[j][col] = 0;
							i = j - 1;
							break;
						}
					}
				}
			}
		}

		/* 옮기기 */
		for (col = 0; col < 4; col++) {
			for (int i = 0; i < 4; i++) {
				temp_row = -1;
				for (int j = i; j < 4; j++) {
					if (board44[j][col] == 0 && temp_row < 0) {
						temp_row = j;
						continue;
					}
					if (board44[j][col] != 0 && temp_row >= 0) {
						board44[temp_row][col] = board44[j][col];
						board44[j][col] = 0;
						break;
					}
				}
			}
		}
		break;	

	}
}

int load() {
	ifstream ReadFile("data.txt");
	if (ReadFile.is_open() == true) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ReadFile >> board44[i][j];
		ReadFile >> score;
		ReadFile.close();
		return 1;
	}
	else {
		cout << "Open datafile failed.";
		ReadFile.close();
		return 0;
	}
}

void save() {
	ofstream WriteFile;
	WriteFile.open("data.txt", ios_base::out);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			WriteFile << board44[i][j] << " ";
	WriteFile << score;
	gotoxy(MAP_ADJ_X + 30, MAP_ADJ_Y + 11);
	cout << "Save success.";
	WriteFile.close();
}

void back() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			board44[i][j] = board44_backup[i][j];
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

