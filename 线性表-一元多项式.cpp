//������ʵ����һԪ����ʽ�ı�ʾ����Ӽ�
//���ߣ�ë���� ѧ�ţ�15436341 �汾��1.0
#include<stdio.h>
#include<stdlib.h>

//���庯������״̬��
#define OK                1
#define ERROR             0  //����
#define OVERFLOW         -2  //�������
#define TRUE              1  
#define FALSE             0

typedef int Status;//���庯�����ͷ���ֵ���룬ֵΪ��������״̬��

typedef struct {//��ı�ʾ������ʽ������ΪLinkList������Ԫ��
	float coef;//ϵ��
	int expn;//ָ��
}term, ElemType;

typedef struct LinkList_polynomial{
	//�����洢�ṹ
	ElemType data;
	struct LinkList_polynomial *next;//ָ����
}*polynomial, LinkList;

Status InitList(polynomial &P){
//����һ���յ����Ա�L
	P = (polynomial)malloc(sizeof(LinkList));
	if (!P) exit(OVERFLOW);
	P->next = NULL;
	return OK;
}//InitList

Status MakeNode(polynomial &p, term e){
	//������pָ���ֵΪe�Ľ�㣬������OK��������ʧ�ܣ��򷵻�ERROR
	p = (polynomial)malloc(sizeof(LinkList));
	if (!p) return ERROR;
	p->data.coef = e.coef; p->data.expn = e.expn;
	return OK;
}//MakeNode

Status ListEmpty(polynomial L){
//�����Ա�Ϊ�շ���TRUE�����򷵻�FALSE
	if (!L->next) return TRUE;
	return FALSE;
}//ListEmpty

Status DelFirst(polynomial h, polynomial &q){
//��֪hָ�����������ͷ��㣬ɾ�������еĵ�һ����㲢��q����
	q = h->next; h->next = h->next->next;
	return OK;
}//DelFirst

Status InsFirst(polynomial &h, polynomial s){
//��s��ָ�������ڵ�һ�����֮ǰ
	s->next = h->next; h->next = s;
	return OK;
}//InsFirst

int PolynLength(polynomial P){
//����һԪ����ʽP�е�����
	if (!P) return ERROR;
	int i = 0; polynomial q = P->next;
	while (q){
		i++;
		q=q->next;
	}
	return i;
}//PolynLength

Status SetCurElem(polynomial &p, term e){
//��֪pָ�����������е�һ����㣬��e����p��ָ����е����ݵ�ֵ
	p->data.coef = e.coef; p->data.expn = e.expn;
	return OK;
}//SetCurElem

int LocateElem(polynomial &L, term e, polynomial &q,int(*compare)(term, term)){
	//�����Ա��в���data��e��ȵ�Ԫ�أ�û�з���FALSE�����ص�һ������compare>0Ԫ�ص�ǰ�������򷵻�TRUE
	int i = 0;
	polynomial p = L->next,pp=L;
	while (p && (compare(p->data, e)<0)){
		pp = p; p = p->next;
	}
	if(!p||compare(p->data,e)>0){
		q=pp;return FALSE;
	}
	return TRUE;
}//LocateElem

int cmp(term a, term b){
//��a��ָ��ֵ<��>��=b��ָ��ֵ���ֱ𷵻�-1��0��+1
	if (a.expn == b.expn) return 0;
	if (a.expn < b.expn) return -1;
	return 1;
}//cmp

void CreatPolyn(polynomial &P,int m){
//����m���ϵ����ָ����������ʾһԪ����ʽ����������
	term e; int i;
	InitList(P); polynomial s,h = P,q; 
	e.coef = 0.0; e.expn = -1; SetCurElem(h, e);//����ͷ��������Ԫ��
	for (i = 1; i <= m; i++){//��������m��������
		scanf("%f %d", &e.coef, &e.expn);
		if (!LocateElem(P, e, q,cmp)){//��ǰ�����в����ڸ�ָ����
			if (MakeNode(s, e)) //���ɽ����sָ��ý�� dataΪe
				InsFirst(q, s); //��q֮ǰ�����㣬�����Ľ������
		}
	}
}//CreatPolyn

void DestroyPolyn(polynomial &P){
	//�������Ա�
	polynomial p;
	while (P){
		p = P->next;
		free(P);
		P = p;
	}
}//DestroyPolyn

void PrintPolyn(polynomial P){
//��ӡ��һԪ����ʽP
	if (!P) printf("����\n");
	polynomial p;
	p = P->next;
	if (p == NULL) printf("0");
	while (p)
	{
		printf("%.1fX^%d", p->data.coef, p->data.expn);
		p = p->next;
		if (p != NULL)
			if (p->data.coef > 0) printf("+");
	}
	printf("\n");
}//PrintPolyn

void AddPolyn(polynomial &Pa, polynomial &Pb){
//����ʽ���Pa=Pb+Pa
	polynomial ha, hb, qa, qb; term a, b; term sum;
	ha = Pa; hb = Pb;//ha hbָ��Pa Pb��ͷ���
	qa = Pa->next; qb = Pb->next;//ָ���һ��Ԫ��
	while (qa&&qb){//qa qb�ǿ�                          //ha��hbָ��qa��qbǰһ��Ԫ��
		a = qa->data; b = qb->data;
		switch (cmp(a,b)){
		case -1://qaָ��Ľ���ָ��С��pbָ�����ָ��
			ha = qa; qa = qa->next; break;
		case 0://qaָ��Ľ���ָ������pbָ�����ָ��
			sum.coef = a.coef + b.coef; sum.expn = a.expn;
			if (sum.coef!= 0.0){
				SetCurElem(qa, sum); ha = qa;}
			else{
				DelFirst(ha, qa); free(qa);}
			DelFirst(hb, qb); free(qb); qb = hb->next;
			qa = ha->next; break;
		case 1://qaָ��Ľ���ָ������pbָ�����ָ��
			DelFirst(hb, qb); InsFirst(ha, qb);
			qb = hb->next; ha = ha->next; break;
		}//switch
	}//while
	if (!ListEmpty(Pb)) ha->next = qb;
	free(Pb);
}//AddPolyn

void SubtractPolyn(polynomial &Pa, polynomial &Pb){
	//����ʽ���Pa=Pa-Pb,�൱��Pa=Pa+��-Pb��
	polynomial ha, hb, qa, qb,bb; term a, b; term sum;
	ha = Pa; hb = Pb; bb = Pb->next;//ha hbָ��Pa Pb��ͷ���
	while (bb){//��Pb�е�ÿ������ϵ����Ϊ���෴��
		bb->data.coef = -bb->data.coef;
		bb = bb->next;
	}
	qa = Pa->next; qb = Pb->next;//ָ���һ��Ԫ��
	while (qa&&qb){//qa qb�ǿ�                               //ha��hbָ��qa��qbǰһ��Ԫ��
		a = qa->data; b = qb->data;
		switch (cmp(a, b)){
		case -1://qaָ��Ľ���ָ��С��pbָ�����ָ��
			ha = qa; qa = qa->next; break;
		case 0://qaָ��Ľ���ָ������pbָ�����ָ��
			sum.coef = a.coef + b.coef; sum.expn = a.expn;
			if (sum.coef != 0.0){
				SetCurElem(qa, sum); ha = qa;}
			else{
				DelFirst(ha, qa); free(qa);}
			DelFirst(hb, qb); free(qb); 
			qb = hb->next;qa = ha->next; break;
		case 1://qaָ��Ľ���ָ������pbָ�����ָ��
			DelFirst(hb, qb); InsFirst(ha, qb);
			qb = hb->next; ha = ha->next; break;
		}//switch
	}//while
	if (!ListEmpty(Pb)) ha->next = qb;
	free(Pb); Pb = NULL;
}//SubtractPolyn

void MultiplyPolyn(polynomial &Pa, polynomial &Pb, polynomial &Pc){
	//��ɶ���ʽ�������
	polynomial pa, pb, hb, s, pc,pd, Pd; term e; InitList(Pc);
	pa = Pa->next; pb = Pb->next; hb = Pb;
	while (pb){
		pa = Pa->next; InitList(Pd); pd = Pd->next; pc = Pc;
		while (pd){
			e.coef = pd->data.coef; e.expn = pd->data.expn;
			if (MakeNode(s, e)) { pc->next = s; s->next = NULL; pc = pc->next; }//pc��ֵΪǰi-1��ĺ�
			pd=pd->next;
		}
		pd = Pd;
		while (pa){
			e.coef = pa->data.coef*pb->data.coef;
			e.expn = pa->data.expn + pb->data.expn;
			pa = pa->next;
			if (MakeNode(s, e)) { pd->next = s; s->next = NULL; pd = pd->next; }//pd��ֵΪbi*A(X)X^(ei)
		}//while
		AddPolyn(Pc, Pd);//Pd�Զ����٣���Ҫ���´��� //ֵΪbi*A(X)X^(ei)�ĺ�
		DelFirst(hb, pb); free(pb);
		pb = hb->next; 
	}//while
	free(Pb); DestroyPolyn(Pa);//�������Ա�Pa��Pb
}//MultiplyPolyn

int main()
{
	polynomial L; polynomial L2,L3;
	CreatPolyn(L, 2); CreatPolyn(L2, 3);//����һԪ����ʽ
	//AddPolyn(L, L2);//һԪ����ʽ���
	//SubtractPolyn(L, L2);//һԪ����ʽ���
	MultiplyPolyn(L, L2,L3);//һԪ����ʽ���
	PrintPolyn(L3);//��ӡһԪ����ʽ
	return 0;
}