#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//函数返回状态码
#define OK                1
#define ERROR             0
#define OVERFLOW         -2  //数据溢出
#define LIST_INIT_SIZE   100 //存储空间初始分配量
#define TRUE              1
#define FALSE             0
#define LISTINCREMENT    10 //存储空间增加量

typedef int Status;//定义函数类型返回值代码，值为函数返回状态码
//typedef char SElemType;//元素类型

typedef struct{
	char s[50][50];//迷宫数据//s指向二维数组
	int a[50][50];//足迹//a指向二维数组
	int row;//行数
	int column;//列数
}MazeType;

typedef struct{
	int x;//横坐标
	int y;//纵坐标
}PosType;//坐标类型

typedef struct{
	int ord;//通道块在路径上的“序号”
	PosType seat;//坐标
	int di;//方向
}SElemType;//栈的元素类型

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

Status GetTop(SqStack S, SElemType &e){
	//若栈不为空，用e返回栈顶元素的值
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1);
	return OK;
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
	if (S.top == S.base) return ERROR;
	e = *--S.top;
	return OK;
} // Pop

Status StackTraverse(SqStack S){
	//从栈底到栈顶依次对每个元素进行访问  
	SElemType *p; p = S.base;
	if (S.base == S.top) return FALSE;//栈为空
	while (p != S.top)
	{
		printf("(%d,%d)\n", p->seat.x, p->seat.y);
		p++;
	}
	printf("\n");
	return OK;
}//StackTraverse

Status InitMaze(MazeType &M){
	//初始化迷宫
	int i, j;
	char mz[50][50];
	printf("请输入迷宫的行数和列数：");
	scanf("%d %d", &M.row, &M.column);
	printf("请输入迷宫：\n");
	for (i = 0; i <M.row + 1; i++){
		gets(mz[i]);
	}
	for (i = 0; i < M.row; i++){
		for (j = 0; j < M.column; j++){
			M.s[i][j] = mz[i + 1][j];//将迷宫保存到结构体中
			M.a[i][j] = 0;//未走过的为0，刚开始都未走过
		}
	}
	return OK;
}//InitMaze

Status Pass(MazeType M, PosType pos){
	//判断当前位置能否通过
	if ((M.row < pos.x) || (M.column < pos.y)) return ERROR;
	if ((M.a[pos.x][pos.y] == 0) && (M.s[pos.x][pos.y] == ' ')) return TRUE;
	return FALSE;
}//Pass

Status FootPrint(MazeType &M, PosType pos){
	//将迷宫的当前位置pos设置为"走过"，即a[x][y]为1  
	if ((pos.x>M.row) || (pos.y>M.column)) return ERROR;
	M.a[pos.x][pos.y] = 1;
	return TRUE;
}//FootPrint

PosType NextPos(PosType pos, int d){
	//获取pos位置d方向的位置  
	switch (d){
	case 1: pos.y++; break;//东
	case 2: pos.x++; break;//南
	case 3: pos.y--; break;//西
	case 4: pos.x--; break;//北 
	}
	return pos;
}//NextPos

Status MarkPrint(MazeType &M, PosType pos){
	//将迷宫M的pos位置，设为已走，成功返回OK；否则返回ERROR  
	if (pos.x>M.row || pos.y>M.column) return ERROR;
	M.a[pos.x][pos.y] = 1;
	return OK;
}//MarkPrint

Status	MazePath(SqStack &S, MazeType &maze, PosType start, PosType end){
	//若迷宫maze中存在从入口start到出口end的通道，则求得一条存放在栈中，并返回TRUE,否则返回FALSE
	PosType curpos; curpos = start;
	int curstep = 1; SElemType e;
	do{
		if (Pass(maze, curpos)){
			FootPrint(maze, curpos);//留下足迹
			e.ord = curstep; e.di = 1; e.seat = curpos;
			Push(S, e);//加入路径
			if ((curpos.x == end.x) && (curpos.y == end.y)) return TRUE;//到达终点
			curpos = NextPos(curpos, 1);//下个位置为当前位置的东邻
			//printf("%d %d\n", curpos.x, curpos.y);//测试
			curstep++;
		}//if  
		else{//当前位置不能通过  
			if (!StackEmpty(S)){
				Pop(S, e);
				while (e.di == 4 && !StackEmpty(S)){//四周都不可走
					MarkPrint(maze, e.seat); Pop(S, e);
				}//while  
				if (e.di<4){//有方向还未探索过
					e.di++; Push(S, e);
					curpos = NextPos(e.seat, e.di);
				}//if  
			}//if  
		}//else  
	} while (!StackEmpty(S));
	return FALSE;
}//MazePath

void f(MazeType M){
	//搜索过程输出
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
	printf("请输入起点坐标：");
	scanf("%d %d", &start.x, &start.y);
	printf("请输入终点坐标：");
	scanf("%d %d", &end.x, &end.y);
	InitMaze(m);//初始化迷宫
	MazePath(S, m, start, end);//对迷宫求解
	StackTraverse(S);//输出解的结果
	f(m);//验证过程
	return 0;
}



