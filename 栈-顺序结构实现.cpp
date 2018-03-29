//本程序实现括号匹配
//作者：毛靖康 版本：1.0 学号：15436341
#include<stdio.h>
#include<stdlib.h>

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
	S.stacksize =0;
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

Status GetTop(SqStack S, SElemType &e){
	//若栈不为空，用e返回栈顶元素的值
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1);
	return OK;
}//GetTop

Status Push(SqStack &S, SElemType e){
	//堆栈
	if (S.top-S.base >= S.stacksize){//栈满 增加存储空间
		S.base = (SElemType *)realloc(S.base, (S.stacksize + LISTINCREMENT)*sizeof(SElemType));
		if (!S.base) exit(OVERFLOW);//存储空间分配失败
		S.top = S.base + S.stacksize;
		S.stacksize += LISTINCREMENT;
	}
	* S.top ++ = e;
	return OK;
}//Push

Status Pop(SqStack &S, SElemType &e){
	//弹栈
	//printf("%d ", S.top - S.base);
	if (S.top == S.base) return ERROR;
	e = * --S.top;
	//printf("%d ", e);
	return OK;
} // Pop

Status StackTraverse(const SqStack *S){  
    //从栈底到栈顶依次对每个元素进行访问  
    SElemType *p=S->base;  
    if(S->base==S->top)  
    {  
        printf("栈为空.\n");  
        return FALSE;  
    }  
    printf("栈中元素：");  
    while(p!=S->top)  
    {  
        printf("%d\n",p);  
        *p++;  
    }  
    printf("\n");  
    return OK;  
}//StackTraverse

int A(char s){
//判断左右括号，为左括号返回1，右括号返回2，否则返回3
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
//判断两括号是否匹配
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
//进行括号匹配，匹配返回TRUE，否则返回FALSE
	char e;
	while (*t!='\0'){
		if (A(*t) == 1) {Push(S, *t); t++;}//为左括号进栈
		else if(A(*t)==2)//为右括号
		{ 
			if (StackEmpty(S)) return FALSE;//栈为空，没有与之匹配的左括号
			else { 
				Pop(S, e); 
				if (!B(e, *t)) return FALSE;//左右括号不匹配
				else t++;
			}//else
		}//else
		else t++;//不是括号跳过
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