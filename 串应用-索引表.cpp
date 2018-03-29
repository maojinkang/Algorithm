//本程序完成词索引表的操作
//作者：毛靖康 学号：15436341 版本：V1.0
//创建时间：2016/11/18
#include<stdio.h>
#include<stdlib.h>

//函数返回状态码
#define OK			 1
#define ERROR		 0
#define OVERFLOW	-2
#define TURE		 1
#define FALSE		 0

//定义函数类型返回值代码，值为函数返回状态码
typedef int Status;

//常量
#define MaxBookNum	1000					//假设只对1000本书建索引表
#define MaxKeyNum	2500					//索引表最大容量
#define MaxLineLen	500						//书目串的最大长度
#define MaxWordNum	10						//词表最大容量


typedef struct{//串的堆分配存储表示
	char *ch;			//若是非空串，则按串长分配存储空间，否则ch的值为NULL
	int length;			//串长度
}HString;

typedef struct{
	char *item[1000];			//字符串数组
	int last;			//词表长度
}WordListType;//词表类型

typedef int ElemTpe;	//链表数据元素类型

typedef struct LNode{
	ElemTpe data;
	struct LNode *next;
}*LinkList;//链表

typedef struct{
	HString key;		//关键词
	LinkList bnolist;	//存放书号索引的链表
}IdxTermType;//索引项类型

typedef struct{
	IdxTermType item[MaxKeyNum + 1];
	int last;
}IdxListType;//索引表类型

char *buf;				//书目缓存区
WordListType wdlist;	//词表
/*---------------------------------------------
						串操作
---------------------------------------------*/

/*---------------------------------------------
函数名：ChuShiHua
函数参数：S串结构体
函数功能：初始化指针ch使其为NULL
返回值：1-初始化成功
-----------------------------------------------*/
Status ChuShiHua(HString &S){
	S.ch = NULL; S.length = 0;
	return OK;
}

/*---------------------------------------------
函数名：StrAssign
函数参数：T需要生成的串，chars指向串常量
函数功能：生成一个其值为串常量chars的串T
返回值：0-生成失败 1-生成成功
---------------------------------------------*/
Status StrAssign(HString &T, char *chars){
	int i, j; char *c;
	if (T.ch) free(T.ch);					//释放原有空间
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
函数名：StrLength
函数参数：S为串结构体
函数功能：计算串的长度
返回值：返回串长
---------------------------------------------*/
int StrLength(HString S){
	return S.length;
}

/*---------------------------------------------
函数名：StrCompare
函数参数：S,T为串结构体
函数功能：串的比较
返回值：>0--S>T  =0--S=T  <0--S<T
---------------------------------------------*/
int StrCompare(HString S, HString T){
	int i;
	for (i = 0; i<S.length&&i<T.length; i++)
	if (S.ch[i] != T.ch[i]) return S.ch[i] - T.ch[i];
	return S.length - T.length;
}

/*---------------------------------------------
函数名：ClearString
函数参数：S为串结构体
函数功能：将S清为空串
返回值：1-已清空
---------------------------------------------*/
Status ClearString(HString &S){
	if (S.ch) { free(S.ch);  S.ch = NULL; }
	S.length = 0;
	return OK;
}

/*---------------------------------------------
函数名：Concat
函数参数：T,S1,S2为串结构体,s2,s3为需要连接连接的串
函数功能：用T返回s2，s1连接成的新串
返回值：1-函数运行成功 -2-内存溢出
---------------------------------------------*/
Status Concat(HString &T, HString S1, HString S2){
	int i;
	if (T.ch) free(T.ch);
	if (!(T.ch = (char *)malloc((S1.length + S2.length+1)*sizeof(char))))
		exit(OVERFLOW);
	for (i = 0; i < S1.length; i++)
		T.ch[i] = S1.ch[i];
	T.length = S1.length + S2.length;
	for (int j=0; i < T.length; i++,j++)
		T.ch[i] = S2.ch[j];
	T.ch[i] = '\0';
	return OK;
}

/*---------------------------------------------
函数名：SubString
函数参数：Sub S串结构体，pos为S的第pos个字符 len为Sub的长度
函数功能：用Sub返回，S的第pos个字符起长度为len的子串
返回值：1-函数运行成功 0-参数出错
---------------------------------------------*/
Status SubString(HString &Sub, HString S, int pos, int len){
	if (pos<1 || pos>S.length || len<0 || len>S.length - pos + 1)
		return ERROR;
	int i;
	if (Sub.ch) free(Sub.ch);
	if (len == 0) { Sub.ch = NULL; Sub.length = 0; return OK; }
	Sub.ch = (char *)malloc((len+1)*sizeof(char));				//len个字符的串有len+1的长度第len+1的值为‘\0’
	for (i = 0; i < len; i++)
		Sub.ch[i] = S.ch[pos - 1 + i];
	Sub.ch[len] = '\0';
	Sub.length = len;
	return OK;
}

/*---------------------------------------------
					索引表操作
---------------------------------------------*/

/*---------------------------------------------
函数名：GetWord
函数参数：Sub S串结构体，pos为S的第pos个字符 len为Sub的长度
函数功能：用wd返回词表wdlist中的第i个关键词
返回值：无
---------------------------------------------*/
void GetWord(int i, HString &wd){
	char *p;
	p = *(wdlist.item + i);
	StrAssign(wd, p);
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