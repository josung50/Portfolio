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
		cout << "항의 갯수 초과" << endl;
	terms[avail].coef = coef;
	terms[avail].expon = expon;
	avail++;
}

void padd (int starta, int finisha, int startb, int finishb, int *startd, int *finishd)
{	 /* A(x) 와 B(x)를 더하여 D(x)를 생성한다 */
	float coefficient;
	*startd = avail;
	while (starta <= finisha && startb <= finishb)
		switch(COMPARE(terms[starta].expon, terms[startb].expon))
		{
		case -1: /* a의 expon이 b의 expon보다 작은 경우 */
			attach(terms[startb].coef, terms[startb].expon);
			startb++; 
			break;

		case 0: /* 지수가 같은 경우 */
			coefficient= terms[starta].coef+terms[startb].coef;
			if(coefficient)
				attach(coefficient, terms[starta].expon);
				starta++;
				startb++; 
				break;

		case 1: /* a의 expon이 b의 expon보다 큰 경우 */
			attach(terms[starta].coef, terms[starta].expon);
			starta++;
		}
	/* A(x)의 나머지 항들을 첨가한다 */
	for(; starta <= finisha; starta++)
		attach(terms[starta].coef, terms[starta].expon);
	/* B(x)의 나머지 항들을 첨가한다 */
	for(; startb <= finishb; startb++)
		attach(terms[startb].coef,terms[startb].expon);
	*finishd = avail-1; 
}