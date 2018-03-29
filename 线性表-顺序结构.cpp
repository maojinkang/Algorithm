//������ʵ�����Ա��������
//���ߣ�ë���� �汾�ţ�1.0 ѧ�ţ�15436341
#include<stdio.h>
#include<stdlib.h>

//���庯������״̬��
#define OK                1
#define ERROR             0
#define OVERFLOW         -2  //�������
#define LIST_INIT_SIZE   100 //���Ա�洢�ռ��ʼ������
#define TRUE              1
#define FALSE             0
#define LISTINCREMENT    10 //���Ա�洢�ռ�������

typedef int Status;//���庯�����ͷ���ֵ���룬ֵΪ��������״̬��
typedef int ElemType;//Ԫ������

typedef struct{
	ElemType *elem;//�洢�ռ��ַ
	int length;   //��ǰ����
	int listsize; //��ǰ����Ĵ洢�ռ�����
}SqList;

Status InitList_Sq(SqList &L){
	//����һ���յ����Ա�L
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}//InitList_Sq

Status ClearList_Sq(SqList &L){
	//�����Ա�L����Ϊ�ձ�
	L.length=0;
	return OK;
}//ClearList_Sq

Status DestroyList_Sq(SqList &L){
	//�������Ա�L
	free(L.elem); L.elem = NULL;
	L.length = 0;
	L.listsize = 0;
	return OK;
}//DestroyList_Sq

int ListLength_Sq(SqList L){
	//����L������Ԫ�صĸ���
	if (!L.elem) return 0;
	return L.length;
}//ListLength_Sq

Status GetElem_Sq(SqList L, int i, ElemType  &e){
	//��e����L�е�i������Ԫ�ص�ֵ
	if ((i<1) || (i>L.length)) return ERROR;
	e = L.elem[i-1];
	return OK;
}//GetElem_Sq

Status ListEmpty_Sq(SqList L){
//�ж����Ա��Ƿ�Ϊ��
	if (L.length == 0) return TRUE;
	return FALSE;
}//ListEmpty_Sq

Status ListInsert_Sq(SqList &L, int i, ElemType e){
//�����Ա��i��λ��֮ǰ�����µ�Ԫ��e��L�ĳ��ȼ�1
	if ((i<1) || (i>L.length+1)) return ERROR;
	ElemType *q, *p, *newbase;
	if (L.length >= L.listsize){//��ǰ�洢�ռ����������ӷ���
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT)*sizeof(ElemType));
		if (!newbase) exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]); p >= q; --p) *(p + 1) = *p;
	*q = e;
	++L.length;
	return OK;
}//ListInsert_Sq

int LocateElem_Sq(SqList L, ElemType  e, Status(*compare)(ElemType, ElemType)){
//�����Ա�L�в��ҵ�1��ֵ��e����compare������Ԫ�ص�λ��
//���ҵ����򷵻�����L�е�λ�򣬷��򷵻�0
	int *p, i = 1; p = L.elem;
	while (i <= L.length&&!(*compare)(*p++, e)) ++i;
	if (i <= L.length) return i;
	else return 0;
}//LocateElem_Sq

Status ListDelete_Sq(SqList &L, int i, ElemType  &e){
//�����Ա���ɾ����i��Ԫ�أ���������ֵ���ҳ��ȼ�1
	ElemType *p,*q;
	if ((i<1) || (i>L.length)) return ERROR;
	p = &(L.elem[i - 1]);
	e = *p;
	q = L.elem + L.length - 1;
	for (++p; p <= q; ++p) *(p - 1) = *p;
	--L.length;
	return OK;
}//ListDelete_Sq

int IsElem_Sq(SqList L, ElemType  e){
//�ж����Ա��Ƿ���eԪ�أ���û�з���0�����򷵻ظ�Ԫ�������Ա��λ��
	int i;
	for (i = 0; i < L.length; i++){
		if (L.elem[i] == e) return i + 1;
	}
	return 0;
}//IsElem_Sq

Status PriorElem_Sq(SqList L, ElemType  cur_e, ElemType  &pre_e){
//��cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ�ܣ�pre_eû����
	int temp = IsElem_Sq(L, cur_e);
	if (temp == 0 || temp == 1) return ERROR;
	pre_e = L.elem[temp - 2];
	return OK;
}//PriorElem_Sq

Status NextElem_Sq(SqList L, ElemType  cur_e, ElemType  &next_e){
	//��cur_e��L������Ԫ�أ��Ҳ������һ��������pre_e�������ĺ�̣��������ʧ�ܣ�pre_eû����
	int temp = IsElem_Sq(L, cur_e);
	if (temp == 0 || temp == L.length) return ERROR;
	next_e = L.elem[temp];
	return OK;
}//NextElem_Sq

void MergeList(SqList La, SqList Lb, SqList &Lc){
//�鲢La��Lb�õ��������Ա�Lc
	InitList_Sq(Lc);
	int i = 1, j = 1, k = 0,ai,bj; int La_len, Lb_len;
	La_len = ListLength_Sq(La); Lb_len = ListLength_Sq(Lb);
	while ((i <= La_len) && (j <= Lb_len)){//La,Lb���ǿ�	  
		GetElem_Sq(La, i, ai); GetElem_Sq(Lb, j, bj);
		if (ai <= bj) { ListInsert_Sq(Lc, ++k, ai); ++i; }
		else { ListInsert_Sq(Lc, ++k, bj); ++j; }
	}
	while (i <= La_len){
		GetElem_Sq(La, i++, ai); ListInsert_Sq(Lc, ++k, ai);
	}
	while (j <= Lb_len){
		GetElem_Sq(Lb, j++, bj); ListInsert_Sq(Lc, ++k, bj);
	}
}//MergeList

int   main()
{
	SqList L, Lb, Lc; int i, e; InitList_Sq(L); InitList_Sq(Lb); InitList_Sq(Lc);//�������Ա�
	for (i = 0; i < 10; i++)
	{
		L.elem[i] = i + 1; L.length++;
		Lb.elem[i] = i + 1; Lb.length++;
	}//���Ա�ֵ
	for (i = 0; i<10; i++)
		printf("%d ", L.elem[i]);//������Ա�
	printf("\n");
	ListDelete_Sq(L, 6, e);//ɾ����6��Ԫ��
	for (i = 0; i<L.length; i++)
		printf("%d ", L.elem[i]);
	printf("\n%d\n",e);
	GetElem_Sq(L, 5, e);//e=��5��Ԫ�ص�ֵ
	printf("%d ", e);
	e = 6;
	ListInsert_Sq(L, 6, e);//�ڵ�6��λ�����Ԫ��
	for (i = 0; i < L.length; i++)
		printf("%d ", L.elem[i]);
	printf("\n");
	if (IsElem_Sq(L, 15)) printf("%d\n", IsElem_Sq(L, 15));//�ж�L���Ƿ���eԪ��
	else printf("ERROR\n");
	MergeList(L, Lb, Lc);//��L��Lb�ϲ���Lc��
	for (i = 0; i < Lc.length; i++)
		printf("%d ", Lc.elem[i]);
	printf("\n");
	if (NextElem_Sq(L, 10, e)) printf("%d\n", e);//���x�ĺ��
	else printf("�����Ա���û�и�Ԫ�ػ��߸�Ԫ�������һ��\n");
	if (PriorElem_Sq(L, 1, e)) printf("%d\n", e);//���x��ǰ��
	else printf("�����Ա���û�и�Ԫ�ػ��߸�Ԫ���ǵ�һ��\n");
	DestroyList_Sq(Lc);//�������Ա�
	if (!Lc.elem) printf("���Ա�������\n");
	return 0;
}