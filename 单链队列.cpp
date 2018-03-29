//本程序实现单链队列的基本操作
//作者：毛靖康 学号：15436341 版本：1.0
#include<stdio.h>
#include<stdlib.h>

//函数状态返回代码
#define OK         1
#define ERROR      0
#define OVERFLOW  -2//存储空间初始分配量
#define TRUE       1
#define FALSE      0

typedef int Status;//定义函数类型返回值代码，值为函数返回状态码
typedef int QElemType;//数据类型

typedef struct QNode{//结点结构体
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front;//队头指针
	QueuePtr rear;//队尾指针
}LinkQueue;

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
	if (Q.rear==p) Q.front = Q.rear;
	free(p);
	return OK;
}//DeQueue

Status QueueTraverse(LinkQueue Q, void (* visit)(QElemType)){
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

int main()
{
	LinkQueue Q;
	InitQueue(Q);//初始化队列
	int i,e;
	for (i = 0; i <1; i++)
		EnQueue(Q, i+1);
	printf("队列长度为：%d\n", QueueLength(Q));
	GetHead(Q, e);
	printf("第一个元素的值为：%d\n", e);
	printf("出队的元素为：");
	for (i = 0; i < 1; i++)
	{
		DeQueue(Q, e);
		printf("%d ", e);
	}
	printf("\n队列中的元素有：");
	QueueTraverse(Q, map);
	printf("\n队列长度改变为%d\n", QueueLength(Q));
	//ClearQueue(Q);
	/*DestroyQueue(Q);
	if (QueueEmpty(Q)) printf("队列已清空\n");*/
}
