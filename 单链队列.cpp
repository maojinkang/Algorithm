//������ʵ�ֵ������еĻ�������
//���ߣ�ë���� ѧ�ţ�15436341 �汾��1.0
#include<stdio.h>
#include<stdlib.h>

//����״̬���ش���
#define OK         1
#define ERROR      0
#define OVERFLOW  -2//�洢�ռ��ʼ������
#define TRUE       1
#define FALSE      0

typedef int Status;//���庯�����ͷ���ֵ���룬ֵΪ��������״̬��
typedef int QElemType;//��������

typedef struct QNode{//���ṹ��
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front;//��ͷָ��
	QueuePtr rear;//��βָ��
}LinkQueue;

Status InitQueue(LinkQueue &Q){
//��ʼ������
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}//InitQueue

Status DestroyQueue(LinkQueue &Q){
//���ٶ���
	while (Q.front){
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}//DestroyQueue

Status ClearQueue(LinkQueue &Q){
//��Q���Ϊ�ն���
	QueuePtr P;
	while (Q.front != Q.rear){
		P = Q.front;
		Q.front = Q.front->next;
		free(P);
	}
	return OK;
}//ClearQueue

Status QueueEmpty(LinkQueue Q){
	//Q���ڣ��ж϶����Ƿ�Ϊ�գ�Ϊ�շ���TRUR,���򷵻�FALSE
	if (Q.front == Q.rear&&Q.front!=NULL) return TRUE;
	return FALSE;
}//QueueEmpty

int QueueLength(LinkQueue Q){
//���ض��г���
	QueuePtr P; int i = 0; P = Q.front;
	while (P != Q.rear){
		P = P->next;
		i++;
	}
	return i;
}//QueueLength

Status EnQueue(LinkQueue &Q, QElemType e){
//����Ԫ��eΪQ���µĶ�βԪ��
	QueuePtr p;
	if (!(p = (QueuePtr)malloc(sizeof(QNode)))) exit(OVERFLOW);
	p->data = e; p->next = Q.rear->next;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}//EnQueue

Status GetHead(LinkQueue Q, QElemType &e){
//�����в�Ϊ�գ���e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR
	if (QueueEmpty(Q)) return ERROR;
	e = Q.front->next->data;
	return OK;
}//GetHead

Status DeQueue(LinkQueue &Q, QElemType &e){
//�����в�Ϊ�գ���e����Q�Ķ�ͷԪ��,��ɾ����ͷԪ�أ�������OK�����򷵻�ERROR
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
//����
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
	InitQueue(Q);//��ʼ������
	int i,e;
	for (i = 0; i <1; i++)
		EnQueue(Q, i+1);
	printf("���г���Ϊ��%d\n", QueueLength(Q));
	GetHead(Q, e);
	printf("��һ��Ԫ�ص�ֵΪ��%d\n", e);
	printf("���ӵ�Ԫ��Ϊ��");
	for (i = 0; i < 1; i++)
	{
		DeQueue(Q, e);
		printf("%d ", e);
	}
	printf("\n�����е�Ԫ���У�");
	QueueTraverse(Q, map);
	printf("\n���г��ȸı�Ϊ%d\n", QueueLength(Q));
	//ClearQueue(Q);
	/*DestroyQueue(Q);
	if (QueueEmpty(Q)) printf("���������\n");*/
}
