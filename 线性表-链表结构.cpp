//������������Ա������ʾ��ʵ��
//���ߣ�ë���� ѧ�ţ�15436341 ʱ�䣺2016��9��20�� �汾��1.0

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

//���庯������״̬����
#define OK           1
#define ERROR        0
#define OVERFLOW         -2  //�������
#define TRUE              1
#define FALSE             0

typedef int Status;//���庯�����ͷ���ֵ���룬ֵΪ��������״̬��
typedef int ElemType;//Ԫ������

typedef struct LNode{//�������
	ElemType       data;
	struct LNode  *next;
}LNode, *LinkList;

Status InitList(LinkList &L, int n){
	//����һ���յ���������
	LinkList p,q; int i;
	L = (LinkList)malloc(sizeof(LNode)); q = L;
	L->next = NULL;//����һ����ͷ�ڵ�ĵ�����
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