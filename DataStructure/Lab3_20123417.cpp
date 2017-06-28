#include<iostream>
#include<cstdlib>

using namespace std;
const int MAX = 100;
typedef struct{
	float coef;
	int expon;
}poly;

poly terms[MAX] = {{2,1000} , {1,0} , {1,4} , {10,3} , {3,2} , {1,0}};
poly terms_2[MAX] = {{1,4} , {10,3} , {3,2} , {1,0} , {2,4} , {5,3} , {3,2} , {1,0}};

void padd_puls (int starta, int finisha, int startb, int finishb, int *startc, int *finishc);
void padd_sub (int starta, int finisha, int startb, int finishb, int *startd, int *finishd);
int COMPARE(int a, int b);
void attach(float coefficient, int exponent);
int avail;

void main()
{
	int startc;
	int finishc;
	padd_puls (0,1,2,5,&startc,&finishc); // terms_1 의 다항식의 덧셈

	cout << "Addition" << endl;
	cout << "Enter A(X): " ;
	for(int i=0 ; i<2 ; i++)
		cout << terms[i].coef << " " << terms[i].expon << " " ;
	cout << endl ;

	cout << "Enter B(X): ";
	for(int i=2 ; i<6 ; i++)
		cout << terms[i].coef << " " << terms[i].expon << " " ;
	cout << endl;

	cout << "A(X)+B(X)=C(X): " ;
	for(int i=6 ; i<avail ; i++)
		cout << terms[i].coef << " " << terms[i].expon << " ";
	
	cout << endl << endl << endl;

	padd_sub (0,3,4,7,&startc,&finishc);
	
	cout << "Subtraction" << endl;
	cout << "Enter A(X): " ;
	for(int i=0 ; i<4 ; i++)
		cout << terms_2[i].coef << " " << terms_2[i].expon << " " ;
	cout << endl;

	cout << "Enter B(X): ";
	for(int i=4 ; i<8 ; i++)
		cout << terms_2[i].coef << " " << terms_2[i].expon << " " ;
	cout << endl;

	cout << "A(X)-B(X)=C(X): " ;
	for(int i=8 ; i<avail ; i++)
		cout << terms[i].coef << " " << terms[i].expon << " ";
	cout << endl;

}

void padd_puls (int starta, int finisha, int startb, int finishb, int *startd, int *finishd)
{
	/* A(x) 와 B(x)를 더하여 D(x)를 생성한다 */
	float coefficient;
	avail = finishb + 1;
	*startd = avail;
	while (starta <= finisha && startb <= finishb)
		switch(COMPARE(terms[starta].expon, terms[startb].expon))
		{
		case -1: /* a의 expon이 b의 expon보다 작은 경우 */
			attach(terms[startb].coef, terms[startb].expon);
			startb++; break;
		case 0: /* 지수가 같은 경우 */
			coefficient= terms[starta].coef+terms[startb].coef;
			if(coefficient)
				attach(coefficient, terms[starta].expon);
			starta++; startb++; break;
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

int COMPARE(int a, int b)
{
	if(a>b) return 1;
	else if(a==b) return 0;
	else return -1;
}

void attach(float coefficient, int exponent)
{	
	if (avail >= MAX) 
	{
		fprintf(stderr, "다항식에 항이 너무 많다.");
		exit(1);
	}

	terms[avail].coef = coefficient;
	terms[avail].expon = exponent;
	avail++;
}



void padd_sub (int starta, int finisha, int startb, int finishb, int *startd, int *finishd)
{
	/* A(x) 와 B(x)를 더하여 D(x)를 생성한다 */
	float coefficient;
	avail = finishb + 1;
	*startd = avail;
	while (starta <= finisha && startb <= finishb)
		switch(COMPARE(terms_2[starta].expon, terms_2[startb].expon))
		{
		case -1: /* a의 expon이 b의 expon보다 작은 경우 */
			terms_2[startb].coef = (terms_2[startb].coef)*(-1);
			attach(terms_2[startb].coef, terms_2[startb].expon);
			startb++; break;
		case 0: /* 지수가 같은 경우 */
			coefficient= terms_2[starta].coef - terms_2[startb].coef;
			if(coefficient)
				attach(coefficient, terms_2[starta].expon);
			starta++; startb++; break;
		case 1: /* a의 expon이 b의 expon보다 큰 경우 */
			attach(terms_2[starta].coef, terms_2[starta].expon);
		starta++;
		}

	/* A(x)의 나머지 항들을 첨가한다 */
	for(; starta <= finisha; starta++)
		attach(terms_2[starta].coef, terms_2[starta].expon);

	/* B(x)의 나머지 항들을 첨가한다 */
	for(; startb <= finishb; startb++)
	attach(terms_2[startb].coef,terms_2[startb].expon);
		*finishd = avail-1;
}

