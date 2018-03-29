#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define OK				1
#define ERROR			0
#define FALSE			0
#define TRUE			1
#define INFINITY		200000//�����
#define MAX_VERTEX_NUM	20//�������

typedef int Status;//��������״̬��
typedef int VRType;//�����ϵ����
typedef char VertexType[MAX_VERTEX_NUM];   //��������      


typedef bool PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef int ShortPathTable[MAX_VERTEX_NUM];
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];				//��������
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];		//�ڽӾ���
	int vexnum, arcnum;								//������ ����.
}MGraph;

Status LocateVex(MGraph G, VertexType u){
	//��ʼ����: ͼG����,u��G�ж�������ͬ����
	// �������: ��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1
	int i;
	for (i = 0; i<G.vexnum; ++i)
	if (strcmp(u, G.vexs[i]) == 0) return i;
	return -1;
}//LocateVex

Status CreateDG(MGraph &G){
	//�����ڽӾ���������ͼ
	int i, j, k;
	VertexType va, vb;
	printf("������ͼ�Ķ������ͻ���\n");
	scanf("%d", &G.vexnum);
	scanf("%d", &G.arcnum);
	for (i = 0; i < G.vexnum; ++i){
		printf("�������%d������\n", i + 1);
		scanf("%s", &G.vexs[i]);
	}
	for (i = 0; i < G.vexnum; ++i){//��ʼ���ڽӾ���  
		for (j = 0; j < G.vexnum; ++j){
			G.arcs[i][j] = INFINITY; 
		}//for
	}//for
	for (k = 0; k < G.arcnum; ++k){
		printf("�������%d����ͷβ���\n", k + 1);
		scanf("%s", &va); scanf("%s", &vb);
		i = LocateVex(G, va);//ȷ��������
		j = LocateVex(G, vb);//ȷ��������
		printf("������û��ȵ�Ȩֵ\n");
		scanf("%d", &G.arcs[i][j]);
	}//for
	return OK;
}//CreateDG


void Display(MGraph &G){
	//����ڽӾ���
	printf("��ͼ���ڽӾ���Ϊ��\n");
	for (int i = 0; i < G.vexnum; ++i){
		for (int j = 0; j < G.vexnum; ++j){
			printf("%10d ",G.arcs[i][j]);
		}
		printf("\n");
	}
}//Display

void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D){
	//�õϽ�˹�����㷨��������G��v0���㵽���ඥ��v�����·��P[v]�����Ȩ����D[V]
	//��P[v][w]ΪTRUE,��w�Ǵ�v0��v��ǰ������·���ϵĵ�
	//final[v]ΪTURE���ҽ���v����S�����Ѿ�������·���ϵĶ���
	int v, w, i, j; bool final[MAX_VERTEX_NUM];
	for (v = 0; v<G.vexnum; v++){
		final[v] = false; //��ʼ��   
		D[v] = G.arcs[v0][v];
		for (w = 0; w<G.vexnum; w++)  
			P[v][w] = false;//ÿ��·��������Ϊ��   
		if (D[v]<INFINITY)
		{ P[v][v0] = true;  P[v][v] = true; }//���v��v0ֱ�����ӣ������·��   
	}
	D[v0] = 0;  final[v0] = true; //��ʼ����v0��������S���ϣ����ҵ����·���ļ���   
	for (i = 1; i<G.vexnum; i++){//ÿ��ѭ�����һ��v0��ĳ��v��������·��������v�ӵ�S����   
		int min = INFINITY;
		for (w = 0; w<G.vexnum; w++)
		if (!final[w]&&D[w]<min)
		{ v = w; min = D[w]; }//�ҵ�����V0����ĵ�   
		final[v] = true;
		for (w = 0; w<G.vexnum; w++)//���µ�ǰ���·��������   
		if (!final[w] && (min + G.arcs[v][w])<D[w]){//û�б�ȷ��ΪΪ���   
			D[w] = min + G.arcs[v][w];
			for (j = 0; j<G.vexnum; j++){//��v��·����ֵ��w   
				if (P[v][j] = true)P[w][j] = true;
			}//if
			P[w][w] = true;//���·�������һ����w 
		}//for
	}
}//ShortestPath_DIJ

void Print_ShortestPath(MGraph G, int v0, ShortPathTable D){
	//���Դ�㵽���������������СȨֵ 0��ʾû��·��
	for (int i = 0; i<G.vexnum; i++){
		if (i == v0) continue;
		printf("%s->%s:", G.vexs[v0], G.vexs[i]);
		if (D[i] == INFINITY) D[i] = 0;
		printf("%d\n", D[i]);
	}
}

int main()
{
	int n;
	MGraph G; PathMatrix P; ShortPathTable D;
	CreateDG(G);
	Display(G);
	printf("������Դ����ţ�\n");
	scanf("%d", &n);
	ShortestPath_DIJ(G, n, P, D);
	Print_ShortestPath(G, n, D);
	getchar();
	return 0;
}