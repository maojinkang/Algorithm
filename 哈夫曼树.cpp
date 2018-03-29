//---------��������----
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
using namespace std;
#define ERROR 0
#define OK 1
typedef int Status;
//���������Ĵ洢�͹���������Ĵ洢
typedef struct{
	int weight;//Ȩֵ
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;       //��̬��������洢��������
typedef char **HuffmanCode; //��̬��������洢�����������


Status Select(HuffmanTree HT, int n, int &s1, int &s2) {
	//�ڹ�������HT[1..n] �������Ȩֵ����СȨֵ����s1,s2 �������ǵ��±�
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

//��huffman������㷨��
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int w[], int n){
	//w���N���ַ���Ȩֵ����?>0)������hufmantree HT,����N���ַ���huffman����HC
	HuffmanTree p;
	char *cd;
	int s1, s2, i, c, m, start, f;
	if (n<1) return;
	m = 2 * n - 1;                                       //���������Ľ���� 
	HT = (HuffmanTree)malloc((m + 1)*sizeof(HTNode));  //0�ŵ�Ԫδ��
	p = HT; p++;
	for (i = 1; i <= n; ++i){
		p->weight = w[i - 1];
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
		p++;
	}//������㸳��ֵ
	for (; i <= m; ++i, ++p){
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}//������㸳��ֵ

	for (i = n + 1; i <= m; ++i)
	{
		Select(HT, i - 1, s1, s2);
		//��HT[1..i-1]ѡ��parentΪ0��weight��С=��������㣬�����ΪS1��S2
		//ÿ�δ�����������i��λ�����У�i>n��
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s2; HT[i].rchild = s1;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	printf("\n����������:\n");
	printf("     NO [weight  parent  lchild  rchild]\n");
	printf("        --------------------------------\n");
	for (i = 1; i <= m; i++)
		printf("%6d [%6d,%6d,%6d,  %6d ]\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
	//��Ҷ�ӵ���������ÿ���ַ���Huffman  ����
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
	printf("��������������Ľڵ���:\n");
	scanf("%d", &n);
	printf("��������������Ľ��Ȩ w[%d]:\n", n);
	for (i = 0; i<n; i++)
		scanf("%d", &w[i]);
	HuffmanCoding(HT, HC, w, n);
	getchar();
	printf("\n�����������������:\n");
	for (i = 1; i <= n; i++)
		printf("%s\n", HC[i]);
}