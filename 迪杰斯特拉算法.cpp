#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define OK				1
#define ERROR			0
#define FALSE			0
#define TRUE			1
#define INFINITY		200000//无穷大
#define MAX_VERTEX_NUM	20//最大结点数

typedef int Status;//函数返回状态码
typedef int VRType;//顶点关系类型
typedef char VertexType[MAX_VERTEX_NUM];   //顶点类型      


typedef bool PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef int ShortPathTable[MAX_VERTEX_NUM];
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];				//顶点向量
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];		//邻接矩阵
	int vexnum, arcnum;								//顶点数 弧数.
}MGraph;

Status LocateVex(MGraph G, VertexType u){
	//初始条件: 图G存在,u和G中顶点有相同特征
	// 操作结果: 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1
	int i;
	for (i = 0; i<G.vexnum; ++i)
	if (strcmp(u, G.vexs[i]) == 0) return i;
	return -1;
}//LocateVex

Status CreateDG(MGraph &G){
	//采用邻接矩阵构造有向图
	int i, j, k;
	VertexType va, vb;
	printf("请输入图的顶点数和弧数\n");
	scanf("%d", &G.vexnum);
	scanf("%d", &G.arcnum);
	for (i = 0; i < G.vexnum; ++i){
		printf("请输入第%d顶点名\n", i + 1);
		scanf("%s", &G.vexs[i]);
	}
	for (i = 0; i < G.vexnum; ++i){//初始化邻接矩阵  
		for (j = 0; j < G.vexnum; ++j){
			G.arcs[i][j] = INFINITY; 
		}//for
	}//for
	for (k = 0; k < G.arcnum; ++k){
		printf("请输入第%d弧的头尾结点\n", k + 1);
		scanf("%s", &va); scanf("%s", &vb);
		i = LocateVex(G, va);//确定横坐标
		j = LocateVex(G, vb);//确定纵坐标
		printf("请输入该弧度的权值\n");
		scanf("%d", &G.arcs[i][j]);
	}//for
	return OK;
}//CreateDG


void Display(MGraph &G){
	//输出邻接矩阵
	printf("该图的邻接矩阵为：\n");
	for (int i = 0; i < G.vexnum; ++i){
		for (int j = 0; j < G.vexnum; ++j){
			printf("%10d ",G.arcs[i][j]);
		}
		printf("\n");
	}
}//Display

void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D){
	//用迪杰斯特拉算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及其带权长度D[V]
	//若P[v][w]为TRUE,则w是从v0到v当前求得最短路径上的点
	//final[v]为TURE当且仅当v属于S，即已经求得最短路径上的顶点
	int v, w, i, j; bool final[MAX_VERTEX_NUM];
	for (v = 0; v<G.vexnum; v++){
		final[v] = false; //初始化   
		D[v] = G.arcs[v0][v];
		for (w = 0; w<G.vexnum; w++)  
			P[v][w] = false;//每条路径都先设为空   
		if (D[v]<INFINITY)
		{ P[v][v0] = true;  P[v][v] = true; }//如果v与v0直接连接，则添加路径   
	}
	D[v0] = 0;  final[v0] = true; //初始化，v0顶点属于S集合，即找到最短路径的集合   
	for (i = 1; i<G.vexnum; i++){//每次循环求得一个v0到某个v顶点的最短路径，并将v加到S集合   
		int min = INFINITY;
		for (w = 0; w<G.vexnum; w++)
		if (!final[w]&&D[w]<min)
		{ v = w; min = D[w]; }//找到距离V0最近的点   
		final[v] = true;
		for (w = 0; w<G.vexnum; w++)//更新当前最短路径及距离   
		if (!final[w] && (min + G.arcs[v][w])<D[w]){//没有被确定为为最近   
			D[w] = min + G.arcs[v][w];
			for (j = 0; j<G.vexnum; j++){//将v的路径赋值给w   
				if (P[v][j] = true)P[w][j] = true;
			}//if
			P[w][w] = true;//添加路径的最后一个点w 
		}//for
	}
}//ShortestPath_DIJ

void Print_ShortestPath(MGraph G, int v0, ShortPathTable D){
	//输出源点到除自身以外结点的最小权值 0表示没有路径
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
	printf("请输入源点序号：\n");
	scanf("%d", &n);
	ShortestPath_DIJ(G, n, P, D);
	Print_ShortestPath(G, n, D);
	getchar();
	return 0;
}