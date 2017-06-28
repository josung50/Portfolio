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
	int Num_macchiato;// 음료의 갯수 0:아메 , 1:라뗴 , 2:마꺄또
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

// 각 음료가 주문 받은 것 만큼 채워지면 분배완료 ..
extern int americano, Atemp1, Btemp1;
extern int caffelatte, Atemp2, Btemp2;
extern int macchiato, Atemp3, Btemp3;
extern int index; // List 배열 접근을 위한 index
extern OrderQue temp;

void working();
void ReceiveOrder(char* Order, int n);
void tempInit();
void InsertBarista();
void display(Barista Barista1, Barista Barista2);

#endif