//��������ɶ������Ļ�������
//���ߣ�ë���� ѧ�ţ�15436341 �汾��1.0
//����ʱ�䣺2016/12/6

#include<stdio.h>
#include<stdlib.h>

#define OK				 1
#define ERROR			-1
#define OVERFLOW		-2
#define TEUE			 1
#define FAKSE			 0

typedef int Status;			//�������ͷ���ֵ���룬ֵΪ��������״̬��
typedef char TElemType;		//��������������

typedef struct BiTNode{		//��������ʽ�洢
	TElemType data;
	struct BiTNode *lchild,*rchild;//���Һ���ָ��
}BiTNode, *BiTree;

Status CreateBiTree(BiTree &T){
	//���Ⱥ�˳������������н���ֵ���ո��ַ���ʾ����
	//������������ʾ������
	char e;
	scanf("%c", &e);
	if (e == ' ') T = NULL;
	else {
		if (!(T = (BiTree)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		T->data = e;					//���ڵ�
		CreateBiTree(T->lchild);		//��������
		CreateBiTree(T->rchild);		//������
	}
	return OK;
}//CreateBiTree

Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e)){
//�����������������ÿ��������Visit����
	if (T){
		if(T->data) Visit(T->data);
		if (T->lchild) PreOrderTraverse(T->lchild, Visit);
		if (T->rchild) PreOrderTraverse(T->rchild, Visit);
	}
	return OK;
}//PreOrderTraverse

Status InOrderTraverse(BiTree T, Status(*Visit)(TElemType e)){
	//�����������������ÿ��������Visit����
	if (T){
		if (T->lchild) InOrderTraverse(T->lchild, Visit);
		if (T->data) Visit(T->data);
		if (T->rchild) InOrderTraverse(T->rchild, Visit);
	}
	return OK;
}//InOrderTraverse

Status PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e)){
	//�����������������ÿ��������Visit����
	if (T){
		if (T->lchild) PostOrderTraverse(T->lchild, Visit);
		if (T->rchild) PostOrderTraverse(T->rchild, Visit);
		if (T->data) Visit(T->data);
	}
	return OK;
}//PostnOrderTraverse

void LeveOrderTraverse(BiTree T){
	//��α���
	BiTNode *queue[30];
	int front, rear;
	if (T == NULL)return;
	front = 0;//ָ���
	rear = 0;
	queue[rear++] = T;
	while (front != rear)
	{
		printf("%c", queue[front]->data);
		if (queue[front]->lchild != NULL)
			queue[rear++] = queue[front]->lchild;
		if (queue[front]->rchild != NULL)
			queue[rear++] = queue[front]->rchild;
		front++;
	}
}

int MAX(int a,int b){
	return a > b ? a : b;
}

int GetHight(BiTree T){
//����������ĸ߶�
	if (!T) return 0;
	return MAX(GetHight(T->lchild), GetHight(T->rchild)) + 1;
}

int CountNode(BiTree T){
	//����ڵ���
	if (!T) return 0;
	return CountNode(T->lchild) + CountNode(T->rchild) + 1;
}

int CountLeafNode(BiTree T){
//����Ҷ�ӽڵ���
	if (!T) return 0;
	if ((!T->lchild) && (!T->rchild)) return 1;
	return CountLeafNode(T->lchild) + CountLeafNode(T->rchild);
}

Status out(TElemType e){
	printf("%c", e);
	return OK;
}

int main()
{
	BiTree T;
	CreateBiTree(T);
	PreOrderTraverse(T, out);
	printf("\n");
	InOrderTraverse(T, out);
	printf("\n");
	PostOrderTraverse(T, out);
	printf("\n");
	LeveOrderTraverse(T);
	printf("\n");
	printf("�߶� �ڵ��� Ҷ�ӽڵ���\n");
	printf("%5d %5d %5d\n", GetHight(T), CountNode(T), CountLeafNode(T));//�߶� �ڵ��� Ҷ�ӽڵ���
	return 0;
}
//ABC  DE G  F   //