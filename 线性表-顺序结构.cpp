//本程序实现线性表基本操作
//作者：毛靖康 版本号：1.0 学号：15436341
#include<stdio.h>
#include<stdlib.h>

//定义函数返回状态码
#define OK                1
#define ERROR             0
#define OVERFLOW         -2  //数据溢出
#define LIST_INIT_SIZE   100 //线性表存储空间初始分配量
#define TRUE              1
#define FALSE             0
#define LISTINCREMENT    10 //线性表存储空间增加量

typedef int Status;//定义函数类型返回值代码，值为函数返回状态码
typedef int ElemType;//元素类型

typedef struct{
	ElemType *elem;//存储空间基址
	int length;   //当前长度
	int listsize; //当前分配的存储空间容量
}SqList;

Status InitList_Sq(SqList &L){
	//构造一个空的线性表L
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}//InitList_Sq

Status ClearList_Sq(SqList &L){
	//将线性表L重置为空表
	L.length=0;
	return OK;
}//ClearList_Sq

Status DestroyList_Sq(SqList &L){
	//销毁线性表L
	free(L.elem); L.elem = NULL;
	L.length = 0;
	L.listsize = 0;
	return OK;
}//DestroyList_Sq

int ListLength_Sq(SqList L){
	//返回L中数据元素的个数
	if (!L.elem) return 0;
	return L.length;
}//ListLength_Sq

Status GetElem_Sq(SqList L, int i, ElemType  &e){
	//用e返回L中第i个数据元素的值
	if ((i<1) || (i>L.length)) return ERROR;
	e = L.elem[i-1];
	return OK;
}//GetElem_Sq

Status ListEmpty_Sq(SqList L){
//判断线性表是否为空
	if (L.length == 0) return TRUE;
	return FALSE;
}//ListEmpty_Sq

Status ListInsert_Sq(SqList &L, int i, ElemType e){
//在线性表第i个位置之前插入新的元素e，L的长度加1
	if ((i<1) || (i>L.length+1)) return ERROR;
	ElemType *q, *p, *newbase;
	if (L.length >= L.listsize){//当前存储空间已满，增加分配
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
//在线性表L中查找第1个值与e满足compare（）的元素的位序
//若找到，则返回其在L中的位序，否则返回0
	int *p, i = 1; p = L.elem;
	while (i <= L.length&&!(*compare)(*p++, e)) ++i;
	if (i <= L.length) return i;
	else return 0;
}//LocateElem_Sq

Status ListDelete_Sq(SqList &L, int i, ElemType  &e){
//在线性表中删除第i个元素，并返回其值，且长度减1
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
//判断线性表是否有e元素，若没有返回0，否则返回该元素在线性表的位置
	int i;
	for (i = 0; i < L.length; i++){
		if (L.elem[i] == e) return i + 1;
	}
	return 0;
}//IsElem_Sq

Status PriorElem_Sq(SqList L, ElemType  cur_e, ElemType  &pre_e){
//若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e没意义
	int temp = IsElem_Sq(L, cur_e);
	if (temp == 0 || temp == 1) return ERROR;
	pre_e = L.elem[temp - 2];
	return OK;
}//PriorElem_Sq

Status NextElem_Sq(SqList L, ElemType  cur_e, ElemType  &next_e){
	//若cur_e是L的数据元素，且不是最后一个，则用pre_e返回它的后继，否则操作失败，pre_e没意义
	int temp = IsElem_Sq(L, cur_e);
	if (temp == 0 || temp == L.length) return ERROR;
	next_e = L.elem[temp];
	return OK;
}//NextElem_Sq

void MergeList(SqList La, SqList Lb, SqList &Lc){
//归并La，Lb得到的新线性表Lc
	InitList_Sq(Lc);
	int i = 1, j = 1, k = 0,ai,bj; int La_len, Lb_len;
	La_len = ListLength_Sq(La); Lb_len = ListLength_Sq(Lb);
	while ((i <= La_len) && (j <= Lb_len)){//La,Lb均非空	  
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
	SqList L, Lb, Lc; int i, e; InitList_Sq(L); InitList_Sq(Lb); InitList_Sq(Lc);//创建线性表
	for (i = 0; i < 10; i++)
	{
		L.elem[i] = i + 1; L.length++;
		Lb.elem[i] = i + 1; Lb.length++;
	}//线性表赋值
	for (i = 0; i<10; i++)
		printf("%d ", L.elem[i]);//输出线性表
	printf("\n");
	ListDelete_Sq(L, 6, e);//删除第6个元素
	for (i = 0; i<L.length; i++)
		printf("%d ", L.elem[i]);
	printf("\n%d\n",e);
	GetElem_Sq(L, 5, e);//e=第5个元素的值
	printf("%d ", e);
	e = 6;
	ListInsert_Sq(L, 6, e);//在第6个位置添加元素
	for (i = 0; i < L.length; i++)
		printf("%d ", L.elem[i]);
	printf("\n");
	if (IsElem_Sq(L, 15)) printf("%d\n", IsElem_Sq(L, 15));//判断L中是否有e元素
	else printf("ERROR\n");
	MergeList(L, Lb, Lc);//将L，Lb合并到Lc中
	for (i = 0; i < Lc.length; i++)
		printf("%d ", Lc.elem[i]);
	printf("\n");
	if (NextElem_Sq(L, 10, e)) printf("%d\n", e);//输出x的后继
	else printf("该线性表中没有该元素或者该元素是最后一个\n");
	if (PriorElem_Sq(L, 1, e)) printf("%d\n", e);//输出x的前驱
	else printf("该线性表中没有该元素或者该元素是第一个\n");
	DestroyList_Sq(Lc);//销毁线性表
	if (!Lc.elem) printf("线性表已销毁\n");
	return 0;
}