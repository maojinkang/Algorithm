//������ʵ������ƥ��
//���ߣ�ë���� �汾��1.0 ѧ�ţ�15436341
#include<stdio.h>
#include<stdlib.h>

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
	S.stacksize =0;
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

Status GetTop(SqStack S, SElemType &e){
	//��ջ��Ϊ�գ���e����ջ��Ԫ�ص�ֵ
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1);
	return OK;
}//GetTop

Status Push(SqStack &S, SElemType e){
	//��ջ
	if (S.top-S.base >= S.stacksize){//ջ�� ���Ӵ洢�ռ�
		S.base = (SElemType *)realloc(S.base, (S.stacksize + LISTINCREMENT)*sizeof(SElemType));
		if (!S.base) exit(OVERFLOW);//�洢�ռ����ʧ��
		S.top = S.base + S.stacksize;
		S.stacksize += LISTINCREMENT;
	}
	* S.top ++ = e;
	return OK;
}//Push

Status Pop(SqStack &S, SElemType &e){
	//��ջ
	//printf("%d ", S.top - S.base);
	if (S.top == S.base) return ERROR;
	e = * --S.top;
	//printf("%d ", e);
	return OK;
} // Pop

Status StackTraverse(const SqStack *S){  
    //��ջ�׵�ջ�����ζ�ÿ��Ԫ�ؽ��з���  
    SElemType *p=S->base;  
    if(S->base==S->top)  
    {  
        printf("ջΪ��.\n");  
        return FALSE;  
    }  
    printf("ջ��Ԫ�أ�");  
    while(p!=S->top)  
    {  
        printf("%d\n",p);  
        *p++;  
    }  
    printf("\n");  
    return OK;  
}//StackTraverse

int A(char s){
//�ж��������ţ�Ϊ�����ŷ���1�������ŷ���2�����򷵻�3
	int i;
	char L[4] = { '{', '[', '(', '<' };
	char R[4] = { '}', ']', ')', '>' };
	for (i = 0; i < 4;i++)
	    if (s == L[i]) return 1;
	for (i = 0; i < 4;i++)
	    if (s == R[i]) return 2;
	return 3;
}

int B(char c, char d){
//�ж��������Ƿ�ƥ��
	int i, j; i = j = 0;
	char L[4] = { '{', '[', '(', '<' };
	char R[4] = { '}', ']', ')', '>' };
	while (i <= 3){                         //      {     [    (    <
		if (L[i] == c) break;               //  }   1     0    0    0
		i++;                                //  ]   0     1    0    0
	}//while                                //  )   0     0    1    0
	while (j <= 3){                         //  >   0     0    0    1
		if (R[j] == d) break;
		j++;
	}//while
	if (i == j) return 1;
	return 0;
}

Status KuoHaoPiPei(SqStack S, char *t){
//��������ƥ�䣬ƥ�䷵��TRUE�����򷵻�FALSE
	char e;
	while (*t!='\0'){
		if (A(*t) == 1) {Push(S, *t); t++;}//Ϊ�����Ž�ջ
		else if(A(*t)==2)//Ϊ������
		{ 
			if (StackEmpty(S)) return FALSE;//ջΪ�գ�û����֮ƥ���������
			else { 
				Pop(S, e); 
				if (!B(e, *t)) return FALSE;//�������Ų�ƥ��
				else t++;
			}//else
		}//else
		else t++;//������������
	}//while
	if (StackEmpty(S)) return TRUE;
	return FALSE;
}

int main()
{
	SqStack S; char s[50];
	InitStack(S);
	while (scanf("%s", &s) != EOF){
		if (KuoHaoPiPei(S, s)) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}