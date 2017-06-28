#pragma once

#ifndef __FUNCVARIABLE_H__
#define __FUNCVARIABLE_H__

#include<iostream>
#include<fstream>
#include<queue>
#include<cstdlib>

using namespace std;

#define ame 3
#define lat 4
#define mac 5
#define MAX 30

typedef struct OrderQue {
	int Num_americano;
	int Num_caffelatte;
	int Num_macchiato;// ������ ���� 0:�Ƹ� , 1:��� , 2:������
}OrderQue;

typedef struct Completed {
	int finish = 0;
	int fin_americano = 0;
	int fin_caffelatte = 0;
	int fin_macchiato = 0;
}Completed;
typedef struct Barista {
	int making_time = 0;
	char Beverage_name[30];
}Barista;

extern queue<OrderQue> LeftBeverages;
extern Completed List[MAX];
extern Barista Barista1;
extern Barista Barista2;

// �� ���ᰡ �ֹ� ���� �� ��ŭ ä������ �й�Ϸ� ..
extern int americano, Atemp1, Btemp1;
extern int caffelatte, Atemp2, Btemp2;
extern int macchiato, Atemp3, Btemp3;
extern int index; // List �迭 ������ ���� index
extern OrderQue temp;

void working();
void ReceiveOrder(char* Order, int n);
void tempInit();
void InsertBarista();
void display(Barista Barista1, Barista Barista2);

#endif