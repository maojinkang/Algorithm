//ʱ��2016.9.7���ó���Ϊ��Ԫ���ʵ��
//����ë����,ѧ��15436341

#include<stdio.h>
#include<stdlib.h>

//���庯�����״̬����
#define TRUE       1
#define FALSE      0 
#define OK         1
#define ERROR      0
#define OVERFLOW  -2

//����StatusΪ�������ͣ�ֵΪ�������״̬����
typedef int Status;

//����Ԫ�س�ԱElemType
typedef int ElemType;
typedef ElemType *Triplet;

//��Ԫ��Ļ�������ʵ��
Status InitTriplet(Triplet &T,int e1,int e2,int e3){
//������Ԫ��T������Ԫ�ظ�ֵΪe1��e2��e3
	T=(ElemType *)malloc(3*sizeof(ElemType));
	if(!T) exit(OVERFLOW);
	T[0]=e1;T[1]=e2;T[2]=e3;
	return OK;
}//InitTriplet

Status DestroyTriplet(Triplet &T){
//������Ԫ��
	free(T);T=NULL;
	return OK;
}//DestroyTriplet

Status Get(Triplet &T,int i,ElemType &e){
//��e�����Ԫ���е�i��Ԫ�أ���1<=i<=3
	if(i<1||i>3) return ERROR;
	e=T[i-1];
	return OK;
}//Get

Status Put(Triplet &T,int i,ElemType e){
//�ı���Ԫ���е�i��Ԫ�ص�ֵ����ֵΪe����1<=i<=3
	if(i<1||i>3) return ERROR;
	T[i-1]=e;
	return OK;
}//Put

Status IsAscending(Triplet &T){
//�����Ԫ���������1���������0
	return (T[0]<=T[1])&&(T[1]<=T[2]);
}//IsAscending

Status IsDescending(Triplet &T){
//�����Ԫ�齵�����1���������0
	return T[0]>=T[1]&&T[1]>=T[2];
}//IsDescending

Status Max(Triplet &T,ElemType &e){
//��e������Ԫ������ֵ
	e=(T[0]>=T[1])?(T[0]>=T[2]?T[0]:T[2]):(T[1]>=T[2]?T[1]:T[2]);
	return OK;
}//Max

Status Min(Triplet &T,ElemType &e){
//��e������Ԫ�����Сֵ
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