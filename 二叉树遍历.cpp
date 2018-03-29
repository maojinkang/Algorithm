#include<stdio.h>
#include<stdlib.h>

#define OK			1
#define ERROR		0
#define OVERFLOW	-1
typedef int Status;			//�������ͷ���ֵ���룬ֵΪ��������״̬��
typedef char TElemType;		//��������������

typedef struct BiTNode{		//��������ʽ�洢
	TElemType data;
	struct BiTNode *lchild, *rchild;//���Һ���ָ��
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
		if (T->data) Visit(T->data);
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

Status out(TElemType e){
	printf("%c", e);
	return OK;
}
Status nmb(BiTree T,char a[], char b[]){
//��֪��������ǰ�� �������������

}//nmb

int main()
{
	char a[20], b[20]; BiTree T;
	gets(a); gets(b);
	nmb(T, a, b);
	return 0;
}

/*                         
ABCDEGF
CBEGDFA
CGEFDBA
*/