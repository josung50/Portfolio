/************************************************************************************
*																					*
*	국민대학교 컴퓨터 공학부 20123417 조성룡										*
*	프로그램 명: InfixtoPostfix														*
*	설		 명: 수식을 입력 받고 수식을 Postfix로 변환하여 변환된 식을 출력, 연산	*
*	알 고 리 즘: 스택을 이용해 Postfix로 변환한다. 입력값 중 '$' 입력되면 입력중단,	*
*				 반복문을 빠져나온다.												*
*   사 용 함 수: postfix - infix form을 Postifix로 변환하는 함수						*
*				 precedence get_token - 입력받은 토큰을 읽고 반환하는 함수			*
*				 calc - 주어진 수식을 연산하는 함수									*
*																					*
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_EXRP_SIZE 100

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, positive, negative, eos, operand
} precedence;

enum {
	single, couple
} preop;

int isp[] = { 0, 0, 1, 1, 2, 2, 2, 3, 3, 0, 0};
int icp[] = { 9, 0, 1, 1, 2, 2, 2, 4, 4, 0, 0};
char operato[] = {' ', ' ', '+', '-', '*', '/', '%', '\0', ' '};

char expr_1[MAX_EXRP_SIZE];
char expr_2[MAX_EXRP_SIZE];
double calc_stack[MAX_STACK_SIZE];

void postfix(void);
double calc(void);
precedence get_token(char *, int *);

int main()
{
	char str[20]={0,}; 
	int i;

	while(str[0]!='E' && str[1] !='N' && str[2]!='D'
	&& str[3]!='-' && str[4]!='O' && str[5]!='F' 
	&& str[6]!='-' && str[7]!='I' && str[8]!='N' 
	&& str[9]!='P' && str[10]!='U' && str[11]!='T')
	{
	system("cls");
	printf("Enter Data : ");
	i=-1;
	
	while( (expr_1[++i]=getchar()) != '$' ); // $ = 수식의 마침/
	expr_1[i]='\0';
	postfix();
	printf("Echo data (infix form) : %s"  , expr_1);
	printf("\nConversion(postifx form) : %s\n", expr_2);
	printf("Result : %lf\n\n", calc());
	scanf("\n%s", &str); // 화면 출력유지를 위한 scanf
	}
}

// infix to postfix //
void postfix(void)
{
precedence stack[MAX_STACK_SIZE];
char symbol; 
int n=0,j=0; 
int top=0;
precedence token;
stack[0]=eos;

preop=single;

	for(token=get_token(&symbol,&n);token!=eos;token=get_token(&symbol,&n))
	{
		if(token==operand)
		expr_2[j++]=symbol;
		else if(token==rparen)
		{
			while(stack[top]!=lparen) 
			{
			expr_2[j++]=' ';
			expr_2[j++]=operato[stack[top--]];
			}
		top--;
		}
		else
		{
			while( isp[stack[top]] >= icp[token] )
			{
			expr_2[j++]=' ';
			expr_2[j++]=operato[stack[top--]];
			}
			stack[++top]=token;
			expr_2[j++]=' ';
		}
	}
	while( (token=stack[top--]) != eos ) 
	{
		expr_2[j++]=' ';
		expr_2[j++]=operato[token];
	}
	expr_2[j++]=operato[token];
}

precedence get_token(char *symbol, int *n)
{
	*symbol=expr_1[(*n)++];
	switch(*symbol)
	{
		case '(' : return lparen;
		case ')' : preop=couple; return rparen;
		case '+' : if(preop==single)
			return positive;
		else
		{
			preop=single;
			return plus;
		}
		case '-' : 
			if(preop==single)
				return negative;
			else 
			{
			preop=single;
			return minus;
			}
		case '*' : preop=single;
			return times;
		case '/' : preop=single;
			return divide;
		case '%' : preop=single;
			return mod;

		case ' ' : preop=single;
			return operand;
		case '\t': preop=single;
			return operand;
		case '\0': preop=single;
			return eos;
		default : preop=couple;
			return operand;
	}
}


// 가장 뒤의 주소값의 성분 2개를 연산자에 따라 계산, 
// 그 결과와 바로 전 주소값에 해당하는 수를 계산하고 이를
// 반복한다.
double calc()
{
	char *p=expr_2;
	int top=-1;

	while(*p != '\0')
	{
		if( (*p>='0' && *p<='9') || (*p=='.') ) 
		{
		calc_stack[++top]= atof(p);
		while(*(p++) != ' ');
		}
		else
		switch (*p)
		{
			case '+' : 
				if(top < 0) 
				{
				printf("stack empty\n");
				exit(1);
				}
				else
				{
				calc_stack[top]=calc_stack[--top] + calc_stack[top+1];
				p++;
				break;
				}
			case '-' : 
				if(top < 0)
				{
				printf("stack empty\n");
				exit(1);
				}
				else 
				{
				calc_stack[top]=calc_stack[--top] - calc_stack[top+1];
				p++;
				break;
				}
			case '*' : 
				if(top < 0)
				{
				printf("stack empty\n");
				exit(1);
				}
				else
				{
				calc_stack[top]=calc_stack[--top] * calc_stack[top+1];
				p++;
				break;
				}
			case '/' : 
				if(top < 0) 
				{
				printf("stack empty\n");
				exit(1);
				}
				else if(calc_stack[top]==0) 
				{
				printf("WRONG INPUT!!\n");
				exit(1);
				}
				calc_stack[top]=calc_stack[--top] / calc_stack[top+1];
				p++;
				break;
			case '%' : 
				if(top < 0) 
				{
				printf("stack empty\n");
				exit(1);
				}
				else
				{
				calc_stack[top]=(int)calc_stack[--top] % (int)calc_stack[top+1];
				p++;
				break;
				}
			default : p++;
		}
		}
	return calc_stack[top];
}


