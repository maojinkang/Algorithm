//---------哈弗曼树----
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
using namespace std;
#define ERROR 0
#define OK 1
typedef int Status;
//哈夫曼树的存储和哈夫曼编码的存储
typedef struct{
	int weight;//权值
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;       //动态分配数组存储哈夫曼树
typedef char **HuffmanCode; //动态分配数组存储哈夫曼编码表


Status Select(HuffmanTree HT, int n, int &s1, int &s2) {
	//在哈夫曼树HT[1..n] 搜索最大权值和最小权值并用s1,s2 返回它们的下标
	int temp=999, i;
	s1 = s2 = 0;
	for (i = 1; i<= n;i++)
	if (HT[i].weight < temp&&HT[i].parent==0){
		s1 = i; temp = HT[i].weight;
	}
	temp = 999;
	for (i = 1; i <= n; i++)
	if (HT[i].weight<temp&&i != s1&&HT[i].parent == 0){
		s2 = i; temp = HT[i].weight;
	}
	if (s1 == 0 && s2 == 0) return ERROR;
	return OK;
}//select

//求huffman编码的算法：
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int w[], int n){
	//w存放N个字符的权值（均?>0)，构造hufmantree HT,并求N个字符有huffman编码HC
	HuffmanTree p;
	char *cd;
	int s1, s2, i, c, m, start, f;
	if (n<1) return;
	m = 2 * n - 1;                                       //哈夫曼树的结点数 
	HT = (HuffmanTree)malloc((m + 1)*sizeof(HTNode));  //0号单元未用
	p = HT; p++;
	for (i = 1; i <= n; ++i){
		p->weight = w[i - 1];
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
		p++;
	}//将各结点赋初值
	for (; i <= m; ++i, ++p){
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}//后续结点赋初值

	for (i = n + 1; i <= m; ++i)
	{
		Select(HT, i - 1, s1, s2);
		//在HT[1..i-1]选择parent为0且weight最小=的两个结点，其序号为S1，S2
		//每次创建的树放在i的位置其中（i>n）
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s2; HT[i].rchild = s1;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	printf("\n哈夫曼树是:\n");
	printf("     NO [weight  parent  lchild  rchild]\n");
	printf("        --------------------------------\n");
	for (i = 1; i <= m; i++)
		printf("%6d [%6d,%6d,%6d,  %6d ]\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
	//从叶子到根逆向求每个字符的Huffman  编码
	HC = (HuffmanCode)malloc((n + 1)*sizeof(char*));
	cd = (char *)malloc(n*sizeof(char));
	cd[n - 1] = '\0';
	for (i = 1; i <= n; ++i)
	{
		start = n - 1;
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		if (HT[f].lchild == c)  cd[--start] = '0';
		else  cd[--start] = '1';
		HC[i] = (char*)malloc((n-start)*sizeof(char));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
}//end  huffmancoding


int main()
{
	HuffmanTree HT;
	int n, i, w[20];
	HuffmanCode HC;
	printf("请输入哈夫曼树的节点数:\n");
	scanf("%d", &n);
	printf("请输入哈夫曼树的结点权 w[%d]:\n", n);
	for (i = 0; i<n; i++)
		scanf("%d", &w[i]);
	HuffmanCoding(HT, HC, w, n);
	getchar();
	printf("\n这个哈夫曼树编码是:\n");
	for (i = 1; i <= n; i++)
		printf("%s\n", HC[i]);
}