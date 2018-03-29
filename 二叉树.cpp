//本程序完成二叉树的基本操作
//作者：毛靖康 学号：15436341 版本：1.0
//创建时间：2016/12/6

#include<stdio.h>
#include<stdlib.h>

#define OK				 1
#define ERROR			-1
#define OVERFLOW		-2
#define TEUE			 1
#define FAKSE			 0

typedef int Status;			//函数类型返回值代码，值为函数返回状态码
typedef char TElemType;		//二叉树数据类型

typedef struct BiTNode{		//二叉树链式存储
	TElemType data;
	struct BiTNode *lchild,*rchild;//左右孩子指针
}BiTNode, *BiTree;

Status CreateBiTree(BiTree &T){
	//按先后顺序输入二叉树中结点的值，空格字符表示空树
	//构造二叉链表表示二叉树
	char e;
	scanf("%c", &e);
	if (e == ' ') T = NULL;
	else {
		if (!(T = (BiTree)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		T->data = e;					//根节点
		CreateBiTree(T->lchild);		//左左子树
		CreateBiTree(T->rchild);		//右子树
	}
	return OK;
}//CreateBiTree

Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e)){
//先序遍历二叉树，对每个结点调用Visit函数
	if (T){
		if(T->data) Visit(T->data);
		if (T->lchild) PreOrderTraverse(T->lchild, Visit);
		if (T->rchild) PreOrderTraverse(T->rchild, Visit);
	}
	return OK;
}//PreOrderTraverse

Status InOrderTraverse(BiTree T, Status(*Visit)(TElemType e)){
	//中序遍历二叉树，对每个结点调用Visit函数
	if (T){
		if (T->lchild) InOrderTraverse(T->lchild, Visit);
		if (T->data) Visit(T->data);
		if (T->rchild) InOrderTraverse(T->rchild, Visit);
	}
	return OK;
}//InOrderTraverse

Status PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e)){
	//后序遍历二叉树，对每个结点调用Visit函数
	if (T){
		if (T->lchild) PostOrderTraverse(T->lchild, Visit);
		if (T->rchild) PostOrderTraverse(T->rchild, Visit);
		if (T->data) Visit(T->data);
	}
	return OK;
}//PostnOrderTraverse

void LeveOrderTraverse(BiTree T){
	//层次遍历
	BiTNode *queue[30];
	int front, rear;
	if (T == NULL)return;
	front = 0;//指向根
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
//计算二叉树的高度
	if (!T) return 0;
	return MAX(GetHight(T->lchild), GetHight(T->rchild)) + 1;
}

int CountNode(BiTree T){
	//计算节点数
	if (!T) return 0;
	return CountNode(T->lchild) + CountNode(T->rchild) + 1;
}

int CountLeafNode(BiTree T){
//计算叶子节点数
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
	printf("高度 节点数 叶子节点数\n");
	printf("%5d %5d %5d\n", GetHight(T), CountNode(T), CountLeafNode(T));//高度 节点数 叶子节点数
	return 0;
}
//ABC  DE G  F   //