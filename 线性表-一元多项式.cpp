//本程序实现了一元多项式的表示及相加减
//作者：毛靖康 学号：15436341 版本：1.0
#include<stdio.h>
#include<stdlib.h>

//定义函数返回状态码
#define OK                1
#define ERROR             0  //错误
#define OVERFLOW         -2  //数据溢出
#define TRUE              1  
#define FALSE             0

typedef int Status;//定义函数类型返回值代码，值为函数返回状态码

typedef struct {//项的表示，多项式的项作为LinkList的数据元素
	float coef;//系数
	int expn;//指数
}term, ElemType;

typedef struct LinkList_polynomial{
	//单链存储结构
	ElemType data;
	struct LinkList_polynomial *next;//指向后继
}*polynomial, LinkList;

Status InitList(polynomial &P){
//创建一个空的线性表L
	P = (polynomial)malloc(sizeof(LinkList));
	if (!P) exit(OVERFLOW);
	P->next = NULL;
	return OK;
}//InitList

Status MakeNode(polynomial &p, term e){
	//分配由p指向的值为e的结点，并返回OK，若分配失败，则返回ERROR
	p = (polynomial)malloc(sizeof(LinkList));
	if (!p) return ERROR;
	p->data.coef = e.coef; p->data.expn = e.expn;
	return OK;
}//MakeNode

Status ListEmpty(polynomial L){
//若线性表为空返回TRUE，否则返回FALSE
	if (!L->next) return TRUE;
	return FALSE;
}//ListEmpty

Status DelFirst(polynomial h, polynomial &q){
//已知h指向线性链表的头结点，删除链表中的第一个结点并以q返回
	q = h->next; h->next = h->next->next;
	return OK;
}//DelFirst

Status InsFirst(polynomial &h, polynomial s){
//将s所指结点插入在第一个结点之前
	s->next = h->next; h->next = s;
	return OK;
}//InsFirst

int PolynLength(polynomial P){
//返回一元多项式P中的项数
	if (!P) return ERROR;
	int i = 0; polynomial q = P->next;
	while (q){
		i++;
		q=q->next;
	}
	return i;
}//PolynLength

Status SetCurElem(polynomial &p, term e){
//已知p指向线性链表中的一个结点，用e更新p所指结点中的数据的值
	p->data.coef = e.coef; p->data.expn = e.expn;
	return OK;
}//SetCurElem

int LocateElem(polynomial &L, term e, polynomial &q,int(*compare)(term, term)){
	//在线性表中查找data与e相等的元素，没有返回FALSE并返回第一个满足compare>0元素的前驱，否则返回TRUE
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
//依a的指数值<或>或=b的指数值，分别返回-1，0和+1
	if (a.expn == b.expn) return 0;
	if (a.expn < b.expn) return -1;
	return 1;
}//cmp

void CreatPolyn(polynomial &P,int m){
//输入m项的系数和指数，建立表示一元多项式的有序链表
	term e; int i;
	InitList(P); polynomial s,h = P,q; 
	e.coef = 0.0; e.expn = -1; SetCurElem(h, e);//设置头结点的数据元素
	for (i = 1; i <= m; i++){//依次输入m个非零项
		scanf("%f %d", &e.coef, &e.expn);
		if (!LocateElem(P, e, q,cmp)){//当前链表中不存在该指数项
			if (MakeNode(s, e)) //生成结点且s指向该结点 data为e
				InsFirst(q, s); //在q之前插入结点，插入后的结点有序
		}
	}
}//CreatPolyn

void DestroyPolyn(polynomial &P){
	//销毁线性表
	polynomial p;
	while (P){
		p = P->next;
		free(P);
		P = p;
	}
}//DestroyPolyn

void PrintPolyn(polynomial P){
//打印出一元多项式P
	if (!P) printf("错误\n");
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
//多项式相加Pa=Pb+Pa
	polynomial ha, hb, qa, qb; term a, b; term sum;
	ha = Pa; hb = Pb;//ha hb指向Pa Pb的头结点
	qa = Pa->next; qb = Pb->next;//指向第一个元素
	while (qa&&qb){//qa qb非空                          //ha，hb指向qa，qb前一个元素
		a = qa->data; b = qb->data;
		switch (cmp(a,b)){
		case -1://qa指向的结点的指数小于pb指向结点的指数
			ha = qa; qa = qa->next; break;
		case 0://qa指向的结点的指数等于pb指向结点的指数
			sum.coef = a.coef + b.coef; sum.expn = a.expn;
			if (sum.coef!= 0.0){
				SetCurElem(qa, sum); ha = qa;}
			else{
				DelFirst(ha, qa); free(qa);}
			DelFirst(hb, qb); free(qb); qb = hb->next;
			qa = ha->next; break;
		case 1://qa指向的结点的指数大于pb指向结点的指数
			DelFirst(hb, qb); InsFirst(ha, qb);
			qb = hb->next; ha = ha->next; break;
		}//switch
	}//while
	if (!ListEmpty(Pb)) ha->next = qb;
	free(Pb);
}//AddPolyn

void SubtractPolyn(polynomial &Pa, polynomial &Pb){
	//多项式相减Pa=Pa-Pb,相当于Pa=Pa+（-Pb）
	polynomial ha, hb, qa, qb,bb; term a, b; term sum;
	ha = Pa; hb = Pb; bb = Pb->next;//ha hb指向Pa Pb的头结点
	while (bb){//将Pb中的每个结点的系数变为其相反数
		bb->data.coef = -bb->data.coef;
		bb = bb->next;
	}
	qa = Pa->next; qb = Pb->next;//指向第一个元素
	while (qa&&qb){//qa qb非空                               //ha，hb指向qa，qb前一个元素
		a = qa->data; b = qb->data;
		switch (cmp(a, b)){
		case -1://qa指向的结点的指数小于pb指向结点的指数
			ha = qa; qa = qa->next; break;
		case 0://qa指向的结点的指数等于pb指向结点的指数
			sum.coef = a.coef + b.coef; sum.expn = a.expn;
			if (sum.coef != 0.0){
				SetCurElem(qa, sum); ha = qa;}
			else{
				DelFirst(ha, qa); free(qa);}
			DelFirst(hb, qb); free(qb); 
			qb = hb->next;qa = ha->next; break;
		case 1://qa指向的结点的指数大于pb指向结点的指数
			DelFirst(hb, qb); InsFirst(ha, qb);
			qb = hb->next; ha = ha->next; break;
		}//switch
	}//while
	if (!ListEmpty(Pb)) ha->next = qb;
	free(Pb); Pb = NULL;
}//SubtractPolyn

void MultiplyPolyn(polynomial &Pa, polynomial &Pb, polynomial &Pc){
	//完成多项式相乘运算
	polynomial pa, pb, hb, s, pc,pd, Pd; term e; InitList(Pc);
	pa = Pa->next; pb = Pb->next; hb = Pb;
	while (pb){
		pa = Pa->next; InitList(Pd); pd = Pd->next; pc = Pc;
		while (pd){
			e.coef = pd->data.coef; e.expn = pd->data.expn;
			if (MakeNode(s, e)) { pc->next = s; s->next = NULL; pc = pc->next; }//pc的值为前i-1项的和
			pd=pd->next;
		}
		pd = Pd;
		while (pa){
			e.coef = pa->data.coef*pb->data.coef;
			e.expn = pa->data.expn + pb->data.expn;
			pa = pa->next;
			if (MakeNode(s, e)) { pd->next = s; s->next = NULL; pd = pd->next; }//pd的值为bi*A(X)X^(ei)
		}//while
		AddPolyn(Pc, Pd);//Pd自动销毁，需要重新创建 //值为bi*A(X)X^(ei)的和
		DelFirst(hb, pb); free(pb);
		pb = hb->next; 
	}//while
	free(Pb); DestroyPolyn(Pa);//销毁线性表Pa，Pb
}//MultiplyPolyn

int main()
{
	polynomial L; polynomial L2,L3;
	CreatPolyn(L, 2); CreatPolyn(L2, 3);//建立一元多项式
	//AddPolyn(L, L2);//一元多项式相加
	//SubtractPolyn(L, L2);//一元多项式相减
	MultiplyPolyn(L, L2,L3);//一元多项式相乘
	PrintPolyn(L3);//打印一元多项式
	return 0;
}