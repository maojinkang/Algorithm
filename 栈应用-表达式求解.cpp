//������ʵ�ֱ��ʽ���
//���ߣ�ë���� �汾��1.0 ѧ�ţ�15436341
#include<stdio.h>
#include<stdlib.h>

bool flag = false;
//��������״̬��
#define OK                1
#define ERROR             0
#define OVERFLOW         -2  //�������
#define LIST_INIT_SIZE   100 //�洢�ռ��ʼ������
#define TRUE              1
#define FALSE             0
#define LISTINCREMENT    10 //�洢�ռ�������
typedef int Status;//���庯�����ͷ���ֵ���룬ֵΪ��������״̬��
typedef char SElemType;//Ԫ������
typedef int ElemType;

typedef struct{
	SElemType *base;//ָ��ջ��
	SElemType *top;//ָ��ջ��
	int stacksize;//ջ�Ĵ�С
}SqStack;

Status InitStack(SqStack &S){
	//��ʼ��ջ
	S.base = (SElemType *)malloc(LIST_INIT_SIZE*sizeof(SElemType));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = LIST_INIT_SIZE;
	return OK;
}//InitStack

Status DestroyStack(SqStack &S){
	//����ջ
	free(S.base); S.top = S.base;
	S.stacksize = 0;
	return OK;
}//DestroyStack

Status ClearStack(SqStack &S){
	//���ջ
	S.top = S.base;
	return OK;
}//ClearStack

Status StackEmpty(SqStack S){
	//�ж�ջ�Ƿ�Ϊ�գ��շ���TRUE�����򷵻�FALSE
	if (S.top == S.base) return TRUE;
	return FALSE;
}//StackEmpty

int StackLength(SqStack S){
	//����ջ��Ԫ�ظ���
	return S.top - S.base;
}//StackLength

char GetTop(SqStack S){
	//��ջ��Ϊ�գ���e����ջ��Ԫ�ص�ֵ
	SElemType e;
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1); return e;
}//GetTop

Status Push(SqStack &S, SElemType e){
	//��ջ
	if (S.top - S.base >= S.stacksize){//ջ�� ���Ӵ洢�ռ�
		S.base = (SElemType *)realloc(S.base, (S.stacksize + LISTINCREMENT)*sizeof(SElemType));
		if (!S.base) exit(OVERFLOW);//�洢�ռ����ʧ��
		S.top = S.base + S.stacksize;
		S.stacksize += LISTINCREMENT;
	}
	*S.top++ = e;
	return OK;
}//Push

Status Pop(SqStack &S, SElemType &e){
	//��ջ
	//printf("%d ", S.top - S.base);
	if (S.top == S.base) return ERROR;
	e = *--S.top;
	//printf("%d ", e);
	return OK;
} // Pop

Status StackTraverse(const SqStack *S){
	//��ջ�׵�ջ�����ζ�ÿ��Ԫ�ؽ��з���  
	SElemType *p = S->base;
	if (S->base == S->top)
	{
		printf("ջΪ��.\n");
		return FALSE;
	}
	printf("ջ��Ԫ�أ�");
	while (p != S->top)
	{
		printf("%d\n", p);
		*p++;
	}
	printf("\n");
	return OK;
}//StackTraverse

char A(char s, char ss){
	//�Ƚ����ȼ�
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
	//��������
	int x, y; x = a - '0'; y = b - '0';
	switch (theta){
	case '+':return x + y+'0';
	case '-':return x - y + '0';
	case '*':return x*y + '0';
	case '/':return x / y + '0';
	}
}

Status In(char s){
	//�ж��Ƿ�Ϊ�����
	int i = 0;
	char L[7] = { '+', '-', '*', '/', '(', ')', '#' };
	for (i = 0; i < 7; i++)
	if (s == L[i]) break;
	if (i >= 7) return FALSE;
	return TRUE;
}

int BiaoDaShi(){
	//���ʽ��ֵ
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