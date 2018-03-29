//������ʵ��ģ�������Ŷ�
//���ߣ�ë���� �汾��1.0
//����ʱ�䣺2016/11/5 22:20
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//����״̬���ش���
#define OK         1
#define ERROR      0
#define OVERFLOW  -2					//�������
#define TRUE       1
#define FALSE      0

typedef int Status; //���庯�����ͷ���ֵ���룬ֵΪ��������״̬��


typedef struct{
	int ArrivalTime;					//����ʱ��
	int Duration;						//�������������ʱ��
} QElemType;//������������

typedef struct{
	int OccurTime;						//�¼�����ʱ��
	int NType;							//�¼����ͣ�0��ʾ�����¼���1-4��ʾ�ĸ����ڵ��뿪�¼�
}Event,ElemType;//��������Ԫ��

typedef struct LNode{//����������
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

typedef LinkList EventList;				//�¼���������

typedef struct QNode{//���ṹ��
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct{
	QueuePtr front;						//��ͷָ��
	QueuePtr rear;						//��βָ��
}LinkQueue;


//************************************
//�����������
//************************************

Status InitList(LinkList &S){
	//��ʼ������
	S= (LinkList)malloc(sizeof(LNode));
	if (!S) exit(OVERFLOW);
	S->next = NULL;
	return OK;
}//InitList

Status ListDestroy(LinkList &L){
	//��������
	LinkList p = L, s;
	while (p->next != NULL){
		s = p; p = p->next;  free(s);
	}
	return OK;
}//ListDestroy

Status OrderInsert(LinkList &L, Event e, int (* compare)(Event, Event)){
//��OccurTime��С�����˳������ ��ͬ�����Ƚ�������ǰ��
	LinkList s;
	LinkList p = L;
	if (p->next == NULL){						//����û���¼�
		s = (LinkList)malloc(sizeof(LNode));
		s->data = e; s->next = p->next;
		p->next = s;
	}//if
	else{
		while (compare(e, p->next->data) != -1){		//�·����¼���ǰһ���¼�����ʱ���� ֱ�ӹ��ں���
			p = p->next;
			if (p->next == NULL){
				s = (LinkList)malloc(sizeof(LNode));
				s->data = e; s->next = p->next;
				p->next = s;
				return OK;
			}
		}//while
		s = (LinkList)malloc(sizeof(LNode));	//����ǰһ�����¼�֮ǰ
		s->data = e; s->next = p->next;
		p->next = s;
	}//else
	return OK;
}

Status DeleteFirst(LinkList &L, ElemType &e){
//ɾ�������һ��Ԫ��,����e����
	LinkList s, p = L;
	s = p->next;
	e = s->data;
	p->next = p->next->next;
	free(s);
	return OK;
}//DeleteFirst

Status ListEmpty(LinkList L){
//�ж������Ƿ�Ϊ�գ�Ϊ�շ��� TRUR�����򷵻�FALSE
	if (L->next == NULL)
		return TRUE;
	return FALSE;
}//ListEmpty

//************************************
//���в���
//************************************

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
	if (Q.rear == p)  Q.rear = Q.front;
	free(p);
	return OK;
}//DeQueue

Status QueueTraverse(LinkQueue Q, void(*visit)(QElemType)){
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


//************************************
//�����Ŷ�ģ��
//************************************

//��Ҫ����
EventList		ev;								//�¼���
Event           en;								//�¼�
LinkQueue		q[5];							//4���ͻ�����
QElemType		customer;						//�ͻ���¼
int			TotalTime, CustomerNum;				//�ۼƿͻ�����ʱ�䣬�ͻ���
#define		CloseTime		30					//����ʱ��

int cmp(Event a, Event b){
//���¼�a����ʱ��<,=,>�¼�b�ķ���ʱ�̷ֱ𷵻�-1 0 1
	if (a.OccurTime < b.OccurTime) return -1;
	if (a.OccurTime == b.OccurTime) return 0;
	return 1;
}//cmp

void OpenForDay(){
//��ʼ������
	int i;
	TotalTime = 0; CustomerNum = 0;
	InitList(ev);
	en.NType = 0; en.OccurTime = 0;				//�趨��һ���ͻ������¼�
	OrderInsert(ev, en, cmp);					//�����¼���
	for (i = 1; i <= 4; ++i) InitQueue(q[i]);	//����Ϊ��
}//OpenForDay

Status Random(int &a, int &b){
//���������
	//srand((int)time(0));
	a = 1+rand()%30;							//����ʱ��
	b = 1+rand()%5;								//��һ�ͻ�����ʱ����
	printf("����ʱ��:%d ��һ�ͻ�����ʱ����:%d\n", a, b);
	return OK;
}//Random

int Minimum(LinkQueue q[]){
	//����̶��еı��
	int l[5];
	for (int i = 1; i <= 4; i++){				//ÿ�����еĳ���
		l[i] = q[i].rear - q[i].front;
	}
	int a = l[1]>l[2] ? 2 : 1;
	int b = l[3]>l[4] ? 4 : 3;
	return l[a]>l[b] ? b : a;
}//Minimum

void CustomerArrived(){
//����ͻ������¼� ��en.NType=0
	Event e; QElemType e1;
	int durtime, intertime;						//����ʱ�� ��һ�ͻ�����ʱ����
	++CustomerNum;
	Random(durtime, intertime);					//���������
	int t = en.OccurTime + intertime;			//�¸��ͻ�����ʱ��
	if (t < CloseTime){
		e.OccurTime = t; e.NType = 0;
		OrderInsert(ev, e, cmp);
	}
	int i = Minimum(q);							//����̶��еı��
	e1.ArrivalTime = en.OccurTime;
	e1.Duration = durtime;
	EnQueue(q[i], e1);							//���
	if (QueueLength(q[i]) == 1){
		e.OccurTime = en.OccurTime + durtime;
		e.NType = i;
		OrderInsert(ev, e, cmp);				//�����г���Ϊ1 �����һ���뿪�¼� ��Ϊֻ��ǰһ�����뿪�� ������˲����뿪
	}
}//CustomerArrived

void CustomerDeparture(){
//����ͻ������¼� ��en.NType>0
	int i; Event e;
	i = en.NType;								//��Bank_Simulation������en�ı�
	DeQueue(q[i], customer);		//ɾ����i���е���ͷ�û�
	TotalTime += en.OccurTime - customer.ArrivalTime;//�ۼƿͻ�����ʱ��
	if (!QueueEmpty(q[i])){						//�趨��i���е�һ���뿪�¼��������¼���
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
	printf("ƽ������ʱ��: %f\n", (float)TotalTime / CustomerNum);
}//Bank_Simulation

int main()
{
	//int a, b;									//���������
	//for (int i = 0; i < 10; i++){Random(a, b);}
	//srand((int)time(0));
	
	Bank_Simulation();
	printf("%d\n",CustomerNum);
	return 0;
}