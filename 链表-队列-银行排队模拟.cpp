//本程序实现模拟银行排队
//作者：毛靖康 版本：1.0
//创建时间：2016/11/5 22:20
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//函数状态返回代码
#define OK         1
#define ERROR      0
#define OVERFLOW  -2					//数据溢出
#define TRUE       1
#define FALSE      0

typedef int Status; //定义函数类型返回值代码，值为函数返回状态码


typedef struct{
	int ArrivalTime;					//到达时间
	int Duration;						//办理事务所需的时间
} QElemType;//队列数据类型

typedef struct{
	int OccurTime;						//事件发生时刻
	int NType;							//事件类型，0表示到达事件，1-4表示四个窗口的离开事件
}Event,ElemType;//有序链表元素

typedef struct LNode{//有序链表定义
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

typedef LinkList EventList;				//事件链表类型

typedef struct QNode{//结点结构体
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct{
	QueuePtr front;						//队头指针
	QueuePtr rear;						//队尾指针
}LinkQueue;


//************************************
//有序链表操作
//************************************

Status InitList(LinkList &S){
	//初始化链表
	S= (LinkList)malloc(sizeof(LNode));
	if (!S) exit(OVERFLOW);
	S->next = NULL;
	return OK;
}//InitList

Status ListDestroy(LinkList &L){
	//销毁链表
	LinkList p = L, s;
	while (p->next != NULL){
		s = p; p = p->next;  free(s);
	}
	return OK;
}//ListDestroy

Status OrderInsert(LinkList &L, Event e, int (* compare)(Event, Event)){
//按OccurTime由小到大的顺序排列 相同的则先进来的排前面
	LinkList s;
	LinkList p = L;
	if (p->next == NULL){						//表中没有事件
		s = (LinkList)malloc(sizeof(LNode));
		s->data = e; s->next = p->next;
		p->next = s;
	}//if
	else{
		while (compare(e, p->next->data) != -1){		//新发生事件比前一个事件发生时间晚 直接挂在后面
			p = p->next;
			if (p->next == NULL){
				s = (LinkList)malloc(sizeof(LNode));
				s->data = e; s->next = p->next;
				p->next = s;
				return OK;
			}
		}//while
		s = (LinkList)malloc(sizeof(LNode));	//挂在前一个的事件之前
		s->data = e; s->next = p->next;
		p->next = s;
	}//else
	return OK;
}

Status DeleteFirst(LinkList &L, ElemType &e){
//删除链表第一个元素,并用e带回
	LinkList s, p = L;
	s = p->next;
	e = s->data;
	p->next = p->next->next;
	free(s);
	return OK;
}//DeleteFirst

Status ListEmpty(LinkList L){
//判断链表是否为空，为空返回 TRUR，否则返回FALSE
	if (L->next == NULL)
		return TRUE;
	return FALSE;
}//ListEmpty

//************************************
//队列操作
//************************************

Status InitQueue(LinkQueue &Q){
	//初始化队列
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}//InitQueue

Status DestroyQueue(LinkQueue &Q){
	//销毁队列
	while (Q.front){
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}//DestroyQueue

Status ClearQueue(LinkQueue &Q){
	//将Q清空为空队列
	QueuePtr P;
	while (Q.front != Q.rear){
		P = Q.front;
		Q.front = Q.front->next;
		free(P);
	}
	return OK;
}//ClearQueue

Status QueueEmpty(LinkQueue Q){
	//Q存在，判断队列是否为空，为空返回TRUR,否则返回FALSE
	if (Q.front == Q.rear&&Q.front!=NULL) return TRUE;
	return FALSE;
}//QueueEmpty

int QueueLength(LinkQueue Q){
	//返回队列长度
	QueuePtr P; int i = 0; P = Q.front;
	while (P != Q.rear){
		P = P->next;
		i++;
	}
	return i;
}//QueueLength

Status EnQueue(LinkQueue &Q, QElemType e){
	//插入元素e为Q的新的队尾元素
	QueuePtr p;
	if (!(p = (QueuePtr)malloc(sizeof(QNode)))) exit(OVERFLOW);
	p->data = e; p->next = Q.rear->next;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}//EnQueue

Status GetHead(LinkQueue Q, QElemType &e){
	//若队列不为空，用e返回Q的队头元素，并返回OK，否则返回ERROR
	if (QueueEmpty(Q)) return ERROR;
	e = Q.front->next->data;
	return OK;
}//GetHead

Status DeQueue(LinkQueue &Q, QElemType &e){
	//若队列不为空，用e返回Q的队头元素,并删除队头元素，并返回OK，否则返回ERROR
	if (QueueEmpty(Q)) return ERROR;
	QueuePtr p;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)  Q.rear = Q.front;
	free(p);
	return OK;
}//DeQueue

Status QueueTraverse(LinkQueue Q, void(*visit)(QElemType)){
	//遍历
	if (QueueEmpty(Q)) return ERROR;
	QueuePtr P; P = Q.front->next;
	while (P)
	{
		visit(P->data);
		P = P->next;
	}
	return OK;
}//QueueTraverse

void map(QElemType e)
{
	printf("%d ", e);
}


//************************************
//银行排队模拟
//************************************

//主要变量
EventList		ev;								//事件表
Event           en;								//事件
LinkQueue		q[5];							//4个客户队列
QElemType		customer;						//客户记录
int			TotalTime, CustomerNum;				//累计客户逗留时间，客户数
#define		CloseTime		30					//关门时刻

int cmp(Event a, Event b){
//依事件a发生时刻<,=,>事件b的发生时刻分别返回-1 0 1
	if (a.OccurTime < b.OccurTime) return -1;
	if (a.OccurTime == b.OccurTime) return 0;
	return 1;
}//cmp

void OpenForDay(){
//初始化操作
	int i;
	TotalTime = 0; CustomerNum = 0;
	InitList(ev);
	en.NType = 0; en.OccurTime = 0;				//设定第一个客户到达事件
	OrderInsert(ev, en, cmp);					//插入事件表
	for (i = 1; i <= 4; ++i) InitQueue(q[i]);	//队列为空
}//OpenForDay

Status Random(int &a, int &b){
//生成随机数
	//srand((int)time(0));
	a = 1+rand()%30;							//处理时间
	b = 1+rand()%5;								//下一客户到达时间间隔
	printf("处理时间:%d 下一客户到达时间间隔:%d\n", a, b);
	return OK;
}//Random

int Minimum(LinkQueue q[]){
	//求最短队列的编号
	int l[5];
	for (int i = 1; i <= 4; i++){				//每个队列的长度
		l[i] = q[i].rear - q[i].front;
	}
	int a = l[1]>l[2] ? 2 : 1;
	int b = l[3]>l[4] ? 4 : 3;
	return l[a]>l[b] ? b : a;
}//Minimum

void CustomerArrived(){
//处理客户到达事件 即en.NType=0
	Event e; QElemType e1;
	int durtime, intertime;						//处理时间 下一客户到达时间间隔
	++CustomerNum;
	Random(durtime, intertime);					//生成随机数
	int t = en.OccurTime + intertime;			//下个客户到达时刻
	if (t < CloseTime){
		e.OccurTime = t; e.NType = 0;
		OrderInsert(ev, e, cmp);
	}
	int i = Minimum(q);							//求最短队列的编号
	e1.ArrivalTime = en.OccurTime;
	e1.Duration = durtime;
	EnQueue(q[i], e1);							//入队
	if (QueueLength(q[i]) == 1){
		e.OccurTime = en.OccurTime + durtime;
		e.NType = i;
		OrderInsert(ev, e, cmp);				//若队列长度为1 则插入一个离开事件 因为只有前一个人离开了 后面的人才能离开
	}
}//CustomerArrived

void CustomerDeparture(){
//处理客户到达事件 即en.NType>0
	int i; Event e;
	i = en.NType;								//在Bank_Simulation（）中en改变
	DeQueue(q[i], customer);		//删除第i队列的排头用户
	TotalTime += en.OccurTime - customer.ArrivalTime;//累计客户逗留时间
	if (!QueueEmpty(q[i])){						//设定第i队列的一个离开事件并插入事件表
		GetHead(q[i], customer);
		e.OccurTime = en.OccurTime + customer.Duration;
		e.NType = i;
		OrderInsert(ev, e, cmp);
	}
}//CustomerDeparture

void Bank_Simulation(){
	ElemType tmp;
	OpenForDay();
	while (!ListEmpty(ev))
	{
		DeleteFirst(ev, tmp);
		en = tmp;
		if (en.NType == 0)
			CustomerArrived();
		else
			CustomerDeparture();
	}
	printf("平均逗留时间: %f\n", (float)TotalTime / CustomerNum);
}//Bank_Simulation

int main()
{
	//int a, b;									//测试随机数
	//for (int i = 0; i < 10; i++){Random(a, b);}
	//srand((int)time(0));
	
	Bank_Simulation();
	printf("%d\n",CustomerNum);
	return 0;
}