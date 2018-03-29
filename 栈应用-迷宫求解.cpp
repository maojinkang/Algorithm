#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//��������״̬��
#define OK                1
#define ERROR             0
#define OVERFLOW         -2  //�������
#define LIST_INIT_SIZE   100 //�洢�ռ��ʼ������
#define TRUE              1
#define FALSE             0
#define LISTINCREMENT    10 //�洢�ռ�������

typedef int Status;//���庯�����ͷ���ֵ���룬ֵΪ��������״̬��
//typedef char SElemType;//Ԫ������

typedef struct{
	char s[50][50];//�Թ�����//sָ���ά����
	int a[50][50];//�㼣//aָ���ά����
	int row;//����
	int column;//����
}MazeType;

typedef struct{
	int x;//������
	int y;//������
}PosType;//��������

typedef struct{
	int ord;//ͨ������·���ϵġ���š�
	PosType seat;//����
	int di;//����
}SElemType;//ջ��Ԫ������

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

Status GetTop(SqStack S, SElemType &e){
	//��ջ��Ϊ�գ���e����ջ��Ԫ�ص�ֵ
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1);
	return OK;
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
	if (S.top == S.base) return ERROR;
	e = *--S.top;
	return OK;
} // Pop

Status StackTraverse(SqStack S){
	//��ջ�׵�ջ�����ζ�ÿ��Ԫ�ؽ��з���  
	SElemType *p; p = S.base;
	if (S.base == S.top) return FALSE;//ջΪ��
	while (p != S.top)
	{
		printf("(%d,%d)\n", p->seat.x, p->seat.y);
		p++;
	}
	printf("\n");
	return OK;
}//StackTraverse

Status InitMaze(MazeType &M){
	//��ʼ���Թ�
	int i, j;
	char mz[50][50];
	printf("�������Թ���������������");
	scanf("%d %d", &M.row, &M.column);
	printf("�������Թ���\n");
	for (i = 0; i <M.row + 1; i++){
		gets(mz[i]);
	}
	for (i = 0; i < M.row; i++){
		for (j = 0; j < M.column; j++){
			M.s[i][j] = mz[i + 1][j];//���Թ����浽�ṹ����
			M.a[i][j] = 0;//δ�߹���Ϊ0���տ�ʼ��δ�߹�
		}
	}
	return OK;
}//InitMaze

Status Pass(MazeType M, PosType pos){
	//�жϵ�ǰλ���ܷ�ͨ��
	if ((M.row < pos.x) || (M.column < pos.y)) return ERROR;
	if ((M.a[pos.x][pos.y] == 0) && (M.s[pos.x][pos.y] == ' ')) return TRUE;
	return FALSE;
}//Pass

Status FootPrint(MazeType &M, PosType pos){
	//���Թ��ĵ�ǰλ��pos����Ϊ"�߹�"����a[x][y]Ϊ1  
	if ((pos.x>M.row) || (pos.y>M.column)) return ERROR;
	M.a[pos.x][pos.y] = 1;
	return TRUE;
}//FootPrint

PosType NextPos(PosType pos, int d){
	//��ȡposλ��d�����λ��  
	switch (d){
	case 1: pos.y++; break;//��
	case 2: pos.x++; break;//��
	case 3: pos.y--; break;//��
	case 4: pos.x--; break;//�� 
	}
	return pos;
}//NextPos

Status MarkPrint(MazeType &M, PosType pos){
	//���Թ�M��posλ�ã���Ϊ���ߣ��ɹ�����OK�����򷵻�ERROR  
	if (pos.x>M.row || pos.y>M.column) return ERROR;
	M.a[pos.x][pos.y] = 1;
	return OK;
}//MarkPrint

Status	MazePath(SqStack &S, MazeType &maze, PosType start, PosType end){
	//���Թ�maze�д��ڴ����start������end��ͨ���������һ�������ջ�У�������TRUE,���򷵻�FALSE
	PosType curpos; curpos = start;
	int curstep = 1; SElemType e;
	do{
		if (Pass(maze, curpos)){
			FootPrint(maze, curpos);//�����㼣
			e.ord = curstep; e.di = 1; e.seat = curpos;
			Push(S, e);//����·��
			if ((curpos.x == end.x) && (curpos.y == end.y)) return TRUE;//�����յ�
			curpos = NextPos(curpos, 1);//�¸�λ��Ϊ��ǰλ�õĶ���
			//printf("%d %d\n", curpos.x, curpos.y);//����
			curstep++;
		}//if  
		else{//��ǰλ�ò���ͨ��  
			if (!StackEmpty(S)){
				Pop(S, e);
				while (e.di == 4 && !StackEmpty(S)){//���ܶ�������
					MarkPrint(maze, e.seat); Pop(S, e);
				}//while  
				if (e.di<4){//�з���δ̽����
					e.di++; Push(S, e);
					curpos = NextPos(e.seat, e.di);
				}//if  
			}//if  
		}//else  
	} while (!StackEmpty(S));
	return FALSE;
}//MazePath

void f(MazeType M){
	//�����������
	int i, j;
	for (i = 0; i < M.row; i++){
		for (j = 0; j < M.column; j++){
			printf("%d", M.a[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	SqStack S; MazeType m; PosType start, end;
	InitStack(S);
	printf("������������꣺");
	scanf("%d %d", &start.x, &start.y);
	printf("�������յ����꣺");
	scanf("%d %d", &end.x, &end.y);
	InitMaze(m);//��ʼ���Թ�
	MazePath(S, m, start, end);//���Թ����
	StackTraverse(S);//�����Ľ��
	f(m);//��֤����
	return 0;
}



