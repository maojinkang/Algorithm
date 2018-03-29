//本程序完成线性表链表表示和实现
//作者：毛靖康 学号：15436341 时间：2016年9月20日 版本：1.0

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

//定义函数返回状态代码
#define OK           1
#define ERROR        0
#define OVERFLOW         -2  //数据溢出
#define TRUE              1
#define FALSE             0

typedef int Status;//定义函数类型返回值代码，值为函数返回状态码
typedef int ElemType;//元素类型

typedef struct LNode{//结点类型
	ElemType       data;
	struct LNode  *next;
}LNode, *LinkList;

Status InitList(LinkList &L, int n){
	//构造一个空的线性链表
	LinkList p,q; int i;
	L = (LinkList)malloc(sizeof(LNode)); q = L;
	L->next = NULL;//建立一个带头节点的单链表
	for (i = 0; i < n; i++){
		p = (LinkList)malloc(sizeof(LNode));
		cin>>(p->data);
		q->next = p; p->next = NULL;
		q = p;
	}
	return OK;
}//InitList

int main()
{
	LinkList L,q; int i;
	InitList(L, 10);
	q = L;
	for (i = 0; i < 10; i++)
	{
		q = q->next;
		printf("%d ",q->data);
	}
}