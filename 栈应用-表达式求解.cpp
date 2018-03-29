//本程序实现表达式求解
//作者：毛靖康 版本：1.0 学号：15436341
#include<stdio.h>
#include<stdlib.h>

bool flag = false;
//函数返回状态码
#define OK                1
#define ERROR             0
#define OVERFLOW         -2  //数据溢出
#define LIST_INIT_SIZE   100 //存储空间初始分配量
#define TRUE              1
#define FALSE             0
#define LISTINCREMENT    10 //存储空间增加量
typedef int Status;//定义函数类型返回值代码，值为函数返回状态码
typedef char SElemType;//元素类型
typedef int ElemType;

typedef struct{
	SElemType *base;//指向栈底
	SElemType *top;//指向栈顶
	int stacksize;//栈的大小
}SqStack;

Status InitStack(SqStack &S){
	//初始化栈
	S.base = (SElemType *)malloc(LIST_INIT_SIZE*sizeof(SElemType));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = LIST_INIT_SIZE;
	return OK;
}//InitStack

Status DestroyStack(SqStack &S){
	//销毁栈
	free(S.base); S.top = S.base;
	S.stacksize = 0;
	return OK;
}//DestroyStack

Status ClearStack(SqStack &S){
	//清空栈
	S.top = S.base;
	return OK;
}//ClearStack

Status StackEmpty(SqStack S){
	//判断栈是否为空，空返回TRUE，否则返回FALSE
	if (S.top == S.base) return TRUE;
	return FALSE;
}//StackEmpty

int StackLength(SqStack S){
	//返回栈中元素个数
	return S.top - S.base;
}//StackLength

char GetTop(SqStack S){
	//若栈不为空，用e返回栈顶元素的值
	SElemType e;
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1); return e;
}//GetTop

Status Push(SqStack &S, SElemType e){
	//堆栈
	if (S.top - S.base >= S.stacksize){//栈满 增加存储空间
		S.base = (SElemType *)realloc(S.base, (S.stacksize + LISTINCREMENT)*sizeof(SElemType));
		if (!S.base) exit(OVERFLOW);//存储空间分配失败
		S.top = S.base + S.stacksize;
		S.stacksize += LISTINCREMENT;
	}
	*S.top++ = e;
	return OK;
}//Push

Status Pop(SqStack &S, SElemType &e){
	//弹栈
	//printf("%d ", S.top - S.base);
	if (S.top == S.base) return ERROR;
	e = *--S.top;
	//printf("%d ", e);
	return OK;
} // Pop

Status StackTraverse(const SqStack *S){
	//从栈底到栈顶依次对每个元素进行访问  
	SElemType *p = S->base;
	if (S->base == S->top)
	{
		printf("栈为空.\n");
		return FALSE;
	}
	printf("栈中元素：");
	while (p != S->top)
	{
		printf("%d\n", p);
		*p++;
	}
	printf("\n");
	return OK;
}//StackTraverse

char A(char s, char ss){
	//比较优先级
	int i, j;
	char L[7] = { '+', '-', '*', '/', '(', ')', '#' };
	char x[7][7] = {
		{ '>', '>', '<', '<', '<', '>', '>' },
		{ '>', '>', '<', '<', '<', '>', '>' },
		{ '>', '>', '>', '>', '<', '>', '>' },
		{ '>', '>', '>', '>', '<', '>', '>' },
		{ '<', '<', '<', '<', '<', '=', ' ' },
		{ '>', '>', '>', '>', ' ', '>', '>' },
		{ '<', '<', '<', '<', '<', ' ', '=' }
	};
	for (i = 0; i <= 6; i++)
	if (s == L[i]) break;
	for (j = 0; j <= 6; j++)
	if (ss == L[j]) break;
	return x[i][j];
}

char B(char a, char theta, char b){
	//进行运算
	int x, y; x = a - '0'; y = b - '0';
	switch (theta){
	case '+':return x + y+'0';
	case '-':return x - y + '0';
	case '*':return x*y + '0';
	case '/':return x / y + '0';
	}
}

Status In(char s){
	//判断是否为运算符
	int i = 0;
	char L[7] = { '+', '-', '*', '/', '(', ')', '#' };
	for (i = 0; i < 7; i++)
	if (s == L[i]) break;
	if (i >= 7) return FALSE;
	return TRUE;
}

int BiaoDaShi(){
	//表达式求值
	SqStack S, Zhi; char c, x, a, b, theta;
	InitStack(Zhi); InitStack(S);
	Push(S, '#'); c = getchar();
	while (c != '#' || GetTop(S) != '#'){
		if (!In(c)){ Push(Zhi, c); c = getchar(); flag = true; }
		else{
			switch (A(GetTop(S), c)){
			case '<':
				if (c == '(') flag = true;
				if (!flag) {printf("ERROR\n"); return 0;}
				flag = false;
				Push(S, c); c = getchar(); break;
			case '=':Pop(S, x); c = getchar(); break;
			case '>':Pop(Zhi, b); Pop(Zhi, a); Pop(S, theta); Push(Zhi, B(a, theta, b)); break;
			case ' ':Push(S, c); break;
			}//switch
		}//else
	}
	return GetTop(Zhi) - '0';
}

int main()
{
	printf("%d\n",BiaoDaShi());
	return 0;
}