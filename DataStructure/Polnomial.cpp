#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cmath>

using namespace std;
int COMPARE(int a, int b);
void attach(float coef , int expon);
void padd (int starta, int finisha, int startb, int finishb, int *startd, int *finishd);

int avail = 6;


typedef struct {
	float coef;
	int expon;
} Polynomial;

Polynomial terms[100]= {{2,1000} , {1,0} , {1,4} , {10,3} , {3,2} , {1,0}};;

void main()
{
	int startd , finishd;
	
	padd(0,1,2,5,&startd,&finishd);

	for(int i=0; i<13; i++)
		cout << terms[i].expon << " " << terms[i].coef << endl;
}

int COMPARE(int a, int b)
{
	if (a<b) return -1;
	else if(a == b) return 0;
	else return 1;
}
void attach(float coef , int expon)
{
	if(avail > 100)
		cout << "���� ���� �ʰ�" << endl;
	terms[avail].coef = coef;
	terms[avail].expon = expon;
	avail++;
}

void padd (int starta, int finisha, int startb, int finishb, int *startd, int *finishd)
{	 /* A(x) �� B(x)�� ���Ͽ� D(x)�� �����Ѵ� */
	float coefficient;
	*startd = avail;
	while (starta <= finisha && startb <= finishb)
		switch(COMPARE(terms[starta].expon, terms[startb].expon))
		{
		case -1: /* a�� expon�� b�� expon���� ���� ��� */
			attach(terms[startb].coef, terms[startb].expon);
			startb++; 
			break;

		case 0: /* ������ ���� ��� */
			coefficient= terms[starta].coef+terms[startb].coef;
			if(coefficient)
				attach(coefficient, terms[starta].expon);
				starta++;
				startb++; 
				break;

		case 1: /* a�� expon�� b�� expon���� ū ��� */
			attach(terms[starta].coef, terms[starta].expon);
			starta++;
		}
	/* A(x)�� ������ �׵��� ÷���Ѵ� */
	for(; starta <= finisha; starta++)
		attach(terms[starta].coef, terms[starta].expon);
	/* B(x)�� ������ �׵��� ÷���Ѵ� */
	for(; startb <= finishb; startb++)
		attach(terms[startb].coef,terms[startb].expon);
	*finishd = avail-1; 
}