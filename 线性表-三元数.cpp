//时间2016.9.7，该程序为三元组的实现
//作者毛靖康,学号15436341

#include<stdio.h>
#include<stdlib.h>

//定义函数结果状态代码
#define TRUE       1
#define FALSE      0 
#define OK         1
#define ERROR      0
#define OVERFLOW  -2

//定义Status为函数类型，值为函数结果状态代码
typedef int Status;

//定义元素成员ElemType
typedef int ElemType;
typedef ElemType *Triplet;

//三元组的基本操作实现
Status InitTriplet(Triplet &T,int e1,int e2,int e3){
//构造三元组T，并将元素赋值为e1，e2，e3
	T=(ElemType *)malloc(3*sizeof(ElemType));
	if(!T) exit(OVERFLOW);
	T[0]=e1;T[1]=e2;T[2]=e3;
	return OK;
}//InitTriplet

Status DestroyTriplet(Triplet &T){
//销毁三元组
	free(T);T=NULL;
	return OK;
}//DestroyTriplet

Status Get(Triplet &T,int i,ElemType &e){
//用e获得三元组中第i个元素，且1<=i<=3
	if(i<1||i>3) return ERROR;
	e=T[i-1];
	return OK;
}//Get

Status Put(Triplet &T,int i,ElemType e){
//改变三元组中第i个元素的值，赋值为e，且1<=i<=3
	if(i<1||i>3) return ERROR;
	T[i-1]=e;
	return OK;
}//Put

Status IsAscending(Triplet &T){
//如果三元组升序输出1，否则输出0
	return (T[0]<=T[1])&&(T[1]<=T[2]);
}//IsAscending

Status IsDescending(Triplet &T){
//如果三元组降序输出1，否则输出0
	return T[0]>=T[1]&&T[1]>=T[2];
}//IsDescending

Status Max(Triplet &T,ElemType &e){
//用e返回三元组的最大值
	e=(T[0]>=T[1])?(T[0]>=T[2]?T[0]:T[2]):(T[1]>=T[2]?T[1]:T[2]);
	return OK;
}//Max

Status Min(Triplet &T,ElemType &e){
//用e返回三元组的最小值
	e=(T[0]<=T[1])?(T[0]<=T[2]?T[0]:T[2]):(T[1]<=T[2]?T[1]:T[2]);
	return OK;
}//Min

int main()
{
	Triplet T;int e;
	if(InitTriplet(T,1,2,3))
	{
		printf("%d,%d,%d\n",T[0],T[1],T[2]);
		printf("%d\n",IsAscending(T));
		printf("%d\n",IsDescending(T));
		Get(T,3,e);
		printf("%d\n",e);
		Max(T,e);
		printf("%d\n",e);
		Min(T,e);
		printf("%d\n",e);
		e=15;Put(T,2,e);
		printf("%d,%d,%d\n",T[0],T[1],T[2]);
		DestroyTriplet(T);
		printf("%d\n",T);
	}
	return 0;
}