//��������ɴ��Ļ�������
//���ߣ�ë���� ѧ�ţ�15436341 �汾��V1.0
//����ʱ�䣺2016/10/31
#include<stdio.h>
#include<stdlib.h>

//��������״̬��
#define OK			 1
#define ERROR		 0
#define OVERFLOW	-2
#define TURE		 1
#define FALSE		 0

//���庯�����ͷ���ֵ���룬ֵΪ��������״̬��
typedef int Status;

//���Ķѷ���洢��ʾ
typedef struct{
	char *ch;								//���Ƿǿմ����򰴴�������洢�ռ䣬����ch��ֵΪNULL
	int length;								//������
}HString;


/*---------------------------------------------
��������ChuShiHua
����������S���ṹ��
�������ܣ���ʼ��ָ��chʹ��ΪNULL
����ֵ��1-��ʼ���ɹ�
-----------------------------------------------*/
Status ChuShiHua(HString &S){
	S.ch = NULL; S.length = 0;
	return OK;
}

/*---------------------------------------------
��������StrAssign
����������T��Ҫ���ɵĴ���charsָ�򴮳���
�������ܣ�����һ����ֵΪ������chars�Ĵ�T
����ֵ��0-����ʧ�� 1-���ɳɹ�
---------------------------------------------*/
Status StrAssign(HString &T, char *chars){
	int i, j; char *c;
	if (T.ch) free(T.ch);					//�ͷ�ԭ�пռ�
	for (i = 0, c = chars; *c; i++, c++);
	if (i == 0){ T.ch = NULL; T.length = 0; }
	else{
		if (!(T.ch = (char *)malloc(i*sizeof(char)))) exit(OVERFLOW);
		for (j = 0; j < i; j++)
			T.ch[j] = chars[j];
		T.length = i;
	}
	return OK;
}

/*---------------------------------------------
��������StrLength
����������SΪ���ṹ��
�������ܣ����㴮�ĳ���
����ֵ�����ش���
---------------------------------------------*/
int StrLength(HString S){
	return S.length;
}

/*---------------------------------------------
��������StrCompare
����������S,TΪ���ṹ��
�������ܣ����ıȽ�
����ֵ��>0--S>T  =0--S=T  <0--S<T
---------------------------------------------*/
int StrCompare(HString S, HString T){
	int i;
	for (i = 0; i<S.length&&i<T.length; i++)
	if (S.ch[i] != T.ch[i]) return S.ch[i] - T.ch[i];
	return S.length - T.length;
}

/*---------------------------------------------
��������ClearString
����������SΪ���ṹ��
�������ܣ���S��Ϊ�մ�
����ֵ��1-�����
---------------------------------------------*/
Status ClearString(HString &S){
	if (S.ch) { free(S.ch);  S.ch = NULL; }
	S.length = 0;
	return OK;
}

/*---------------------------------------------
��������Concat
����������T,S1,S2Ϊ���ṹ��,s2,s3Ϊ��Ҫ�������ӵĴ�
�������ܣ���T����s2��s1���ӳɵ��´�
����ֵ��1-�������гɹ� -2-�ڴ����
---------------------------------------------*/
Status Concat(HString &T, HString S1, HString S2){
	int i;
	if (T.ch) free(T.ch);
	if (!(T.ch = (char *)malloc((S1.length + S2.length + 1)*sizeof(char))))
		exit(OVERFLOW);
	for (i = 0; i < S1.length; i++)
		T.ch[i] = S1.ch[i];
	T.length = S1.length + S2.length;
	for (int j = 0; i < T.length; i++, j++)
		T.ch[i] = S2.ch[j];
	T.ch[i] = '\0';
	return OK;
}

/*---------------------------------------------
��������SubString
����������Sub S���ṹ�壬posΪS�ĵ�pos���ַ� lenΪSub�ĳ���
�������ܣ���Sub���أ�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
����ֵ��1-�������гɹ� 0-��������
---------------------------------------------*/
Status SubString(HString &Sub, HString S, int pos, int len){
	if (pos<1 || pos>S.length || len<0 || len>S.length - pos + 1)
		return ERROR;
	int i;
	if (Sub.ch) free(Sub.ch);
	if (len == 0) { Sub.ch = NULL; Sub.length = 0; return OK; }
	Sub.ch = (char *)malloc((len + 1)*sizeof(char));				//len���ַ��Ĵ���len+1�ĳ��ȵ�len+1��ֵΪ��\0��
	for (i = 0; i < len; i++)
		Sub.ch[i] = S.ch[pos - 1 + i];
	Sub.ch[len] = '\0';
	Sub.length = len;
	return OK;
}

int main()
{
	HString S, T, E; ChuShiHua(S); ChuShiHua(T); ChuShiHua(E);
	char ss[100];
	scanf("%s", &ss);
	StrAssign(S, ss);
	scanf("%s", &ss);
	StrAssign(T, ss);
	Concat(E, S, T);
	printf("%s", E.ch);
}