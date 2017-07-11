#include<iostream>
#include<fstream>
#include<string>
#include<conio.h.>
#include<Windows.h>
#include<time.h>
#include<math.h>

using namespace std;

#define Map_x 10
#define Map_y 0
#define LEFT 77
#define RIGHT 75
#define UP 80
#define DOWN 72
#define PAUSE 112
#define ESC 27
#define GAMEOVER -1
#define RESET 114
int SPEED = 100;

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR }CURSOR_TYPE;
typedef struct snake_point { int x; int y; }snake_point;

void Draw_Backgroud();
void Draw_Frame();
void Move_Snake();
void Draw_Snake();
void Delete_Before_Snake();
void Gameover_check();
void Load();
void Save();
void Pause();
void Food();
void Eat_Food();
void Init();
void Reset();

void gotoxy(int x, int y); //����ͻ��� x,y ��ǥ�� �̵���Ű�� �Լ�
void setcursortype(CURSOR_TYPE c);

int board_x = Map_x; int board_y = 8; // �� ������ ��ǥ(���� ����� 0,0) , 29(*2�踦 �ؾ��Ѵ�. Ư������ ������.)x12
snake_point snake[1000]; // ���� �����ϴ� ��ǥ , [0]�� �Ӹ��� ���Ѵ�. [length_snake-1]�� ������ ���Ѵ�
int food_x; int food_y; // ������ ��ǥ
int score = 0; int best_score = 0;
int Food_In_Map = 0; // ���� Flag
int length_snake; // ��ǥ�� �ε����� ���
int menu_key;
int Status_Direction_Snake; // ���� �������

void main() {
	Draw_Backgroud();
	menu_key = getch();
	Init();
	while (1) {
		if (kbhit()) do { menu_key = getch(); } while (menu_key == 224); //Ű �Է¹���, ���Ѵ�� ����
		switch (menu_key) {
			case LEFT:
			case RIGHT:
			case DOWN:
			case UP:
				Move_Snake();
				break;
			case ESC:
				return;
				break;
			case PAUSE:
				Pause();
				break;
			case GAMEOVER:
				while (menu_key == RESET) {
					menu_key = getch();
				}
				break;
			case RESET:
				Reset();
		}
		Food();
	}
}

void Draw_Backgroud() {
	setcursortype(NOCURSOR);
	gotoxy(Map_x + 8, Map_y+1);
	cout << "����� ��    ��     ��     ��  �� �����";
	gotoxy(Map_x + 8, Map_y+2);
	cout << "��       ���  ��    ���    �� ��  ��";
	gotoxy(Map_x + 8, Map_y+3);
	cout << "����� �� �� ��   ��  ��   ���   �����";
	gotoxy(Map_x + 8, Map_y+4);
	cout << "      �� ��  ���  �� �� ��  �� ��  ��";
	gotoxy(Map_x + 8, Map_y+5);
	cout << "����� ��    �� ��      �� ��  �� �����";

	gotoxy(Map_x - 2, Map_y + 7);
	cout << "���������������������������������";
	gotoxy(Map_x - 2, Map_y + 8);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 9);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 10);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 11);
	cout << "��                 �� Press any key to start                  ��";
	gotoxy(Map_x - 2, Map_y + 12);
	cout << "��                 �� �� , �� , �� , �� : Move                ��";
	gotoxy(Map_x - 2, Map_y + 13);
	cout << "��                 �� R : Reset                               ��";
	gotoxy(Map_x - 2, Map_y + 14);
	cout << "��                 �� P : Pause                               ��";
	gotoxy(Map_x - 2, Map_y + 15);
	cout << "��                 �� ESC : Quit                              ��";
	gotoxy(Map_x - 2, Map_y + 16);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 17);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 18);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 19);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 20);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 21);
	cout << "���������������������������������";
	gotoxy(Map_x - 2, Map_y + 22);
	cout << "SCORE: " << score << "    BEST SCORE: " << best_score;
	gotoxy(Map_x - 2, Map_y + 23);
}
void Draw_Frame() {
	gotoxy(Map_x + 8, Map_y + 1);
	cout << "����� ��    ��     ��     ��  �� �����";
	gotoxy(Map_x + 8, Map_y + 2);
	cout << "��       ���  ��    ���    �� ��  ��";
	gotoxy(Map_x + 8, Map_y + 3);
	cout << "����� �� �� ��   ��  ��   ���   �����";
	gotoxy(Map_x + 8, Map_y + 4);
	cout << "      �� ��  ���  �� �� ��  �� ��  ��";
	gotoxy(Map_x + 8, Map_y + 5);
	cout << "����� ��    �� ��      �� ��  �� �����";

	gotoxy(Map_x - 2, Map_y + 7);
	cout << "���������������������������������";
	gotoxy(Map_x - 2, Map_y + 8);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 9);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 10);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 11);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 12);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 13);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 14);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 15);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 16);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 17);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 18);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 19);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 20);
	cout << "��                                                            ��";
	gotoxy(Map_x - 2, Map_y + 21);
	cout << "���������������������������������";
	gotoxy(Map_x - 2, Map_y + 22);
	cout << "SCORE: " << score << "    BEST SCORE: " << best_score;
	gotoxy(Map_x - 2, Map_y + 23);
}

void Init() {
	system("cls");
	Draw_Frame();
	Food_In_Map = 0;
	SPEED = 100;
	Status_Direction_Snake = LEFT;
	food_x = 0; food_y = 0; // ������ ��ǥ
	score = 0;
	int Food_In_Map = 0; // ���� Flag

	length_snake = 5;
	for (int i = 0; i < length_snake; i++) {
		snake[i].x = board_x + (15 - i) * 2;
		snake[i].y = board_y + 6;
	}

	for (int i = 0; i < length_snake; i++) {
		if (i == 0) {
			gotoxy(snake[0].x, snake[0].y);
			cout << "��";
		}
		else {
			gotoxy(snake[i].x, snake[i].y);
			cout << "��";
		}
	}
	Food();
	gotoxy(Map_x - 2, Map_y + 23);
}
void Reset() {
	Init();
	menu_key = 0;
}
void Food() {
	if (Food_In_Map == 0) {
		while (1) {
			food_x = (rand() % 29 + 1) * 2 + board_x;
			food_y = (rand() % 12 + 1) + board_y;
			for (int i = 0; i < length_snake; i++) { // ������ �����Ǵ� ��ǥ�� ���� ��ǥ�� ��ġ���� Ȯ��
				if (snake[i].x == food_x && snake[i].y == food_y) {
					break;
				}
				else {
					Food_In_Map = 1;
				}
			}
			if (Food_In_Map == 1)
				break;
		}
		gotoxy(food_x, food_y);
		cout << "��";
	}
}
void Gameover_check() {
	if (snake[0].x == board_x + 30 * 2 || snake[0].x == board_x - 2 || snake[0].y == board_y -1 || snake[0].y == board_y + 13) {
		menu_key = GAMEOVER;
		gotoxy(Map_x + 18, Map_y + 23);
		cout << "GAME OVER. Reset Please.";
		if (best_score < score)
			best_score = score;
		gotoxy(Map_x - 2, Map_y + 24);
	}
	for (int i = 1; i < length_snake; i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			menu_key = GAMEOVER;
			gotoxy(Map_x + 18, Map_y + 23);
			cout << "GAME OVER. Reset Please.";
			if (best_score < score)
				best_score = score;
			gotoxy(Map_x - 2, Map_y + 24);
		}
	}
}
void Move_Snake() {
	Delete_Before_Snake();
	Eat_Food();
	switch (menu_key) {
	case LEFT:
		if (Status_Direction_Snake != RIGHT) {
			// ���� �κ��� �ű�
			for (int i = length_snake - 1; i >= 1; i--) {
				snake[i].x = snake[i - 1].x;
				snake[i].y = snake[i - 1].y;
			}
			snake[0].x += 2; // �Ӹ� ������Ʈ
			Status_Direction_Snake = LEFT;
		}
		if (Status_Direction_Snake == RIGHT) {
			menu_key = RIGHT;
		}
		break;
	case RIGHT:
		if (Status_Direction_Snake != LEFT) {
			// ���� �κ��� �ű�
			for (int i = length_snake - 1; i >= 1; i--) {
				snake[i].x = snake[i - 1].x;
				snake[i].y = snake[i - 1].y;
			}
			snake[0].x -= 2; // �Ӹ� ������Ʈ
			Status_Direction_Snake = RIGHT;
		}
		if (Status_Direction_Snake == LEFT) {
			menu_key = LEFT;
		}
		break;
	case DOWN:
		if (Status_Direction_Snake != UP) {
			// ���� �κ��� �ű�
			for (int i = length_snake - 1; i >= 1; i--) {
				snake[i].x = snake[i - 1].x;
				snake[i].y = snake[i - 1].y;
			}
			snake[0].y -= 1; // �Ӹ� ������Ʈ
			Status_Direction_Snake = DOWN;
		}
		if (Status_Direction_Snake == UP) {
			menu_key = UP;
		}
		break;
	case UP:
		if (Status_Direction_Snake != DOWN) {
			// ���� �κ��� �ű�
			for (int i = length_snake - 1; i >= 1; i--) {
				snake[i].x = snake[i - 1].x;
				snake[i].y = snake[i - 1].y;
			}
			snake[0].y += 1; // �Ӹ� ������Ʈ
			Status_Direction_Snake = UP;
		}
		if (Status_Direction_Snake == DOWN) {
			menu_key = DOWN;
		}
		break;
	}
	Draw_Snake();
	Gameover_check();
}
void Draw_Snake() {
	for (int i = 0; i < length_snake; i++) {
		if (i == 0) {
			gotoxy(snake[i].x, snake[i].y);
			cout << "��";
		}
		else {
			gotoxy(snake[i].x, snake[i].y);
			cout << "��";
		}
	}
	Sleep(SPEED);
}
void Delete_Before_Snake() {
	// ���� �� �����
	for (int i = 0; i < length_snake; i++) {
		gotoxy(snake[i].x, snake[i].y);
		cout << " ";
	}
}
void Eat_Food() {
	if (snake[0].x == food_x && snake[0].y == food_y) {
		gotoxy(food_x, food_y);
		cout << " ";
		snake[length_snake].x = snake[length_snake - 1].x - 2;
		snake[length_snake].y = snake[length_snake - 1].y;
		length_snake++;
		Food_In_Map = 0;
		SPEED -= 3;
		score += 10;

		gotoxy(Map_x - 2, Map_y + 22);
		cout << "SCORE: " << score << "    BEST SCORE: " << best_score;
	}
}
void Pause() {
	int pause = 0;
	while (1) {
		if (kbhit()) do { pause = getch(); } while (menu_key == 224); //Ű �Է¹���, ���Ѵ�� ����
		gotoxy(Map_x + 26, Map_y + 23);
		cout << "P A U S E";
		Sleep(300);
		gotoxy(Map_x + 26, Map_y + 23);
		cout << "         ";
		Sleep(300);
		if (pause == PAUSE) {
			menu_key = Status_Direction_Snake;
			gotoxy(Map_x - 2, Map_y + 23);
			return;
		}
		gotoxy(Map_x - 2, Map_y + 23);
	}
}

void gotoxy(int x, int y) { //����ͻ��� x,y ��ǥ�� �̵���Ű�� �Լ� 
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO Curinfo; // console sursor ����ü
	switch (c)
	{
	case NOCURSOR:
		Curinfo.dwSize = 1; //cursor size
		Curinfo.bVisible = FALSE; // cursor �Ⱥ���
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