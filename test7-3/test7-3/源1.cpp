#include<stdio.h>
#include<stdlib.h>
/* ͼ���ڽӾ����ʾ�� */

#define ERROR -1
#define MaxVertexNum 500    /* ��󶥵�����Ϊ100 */
#define INFINITY 655350        /* ����Ϊ˫�ֽ��޷������������ֵ65535*/
typedef int Vertex;         /* �ö����±��ʾ����,Ϊ���� */
typedef int WeightType;        /* �ߵ�Ȩֵ��Ϊ���� */
//typedef char DataType;        /* ����洢������������Ϊ�ַ��� */

/* �ߵĶ��� */
typedef struct ENode *PtrToENode;
struct ENode{
	Vertex V1, V2;      /* �����<V1, V2> */
	WeightType Weight;  /* Ȩ�� */
	int Cost;           /*·��*/
};
typedef PtrToENode Edge;

/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv;  /* ������ */
	int Ne;  /* ����   */
	WeightType G[MaxVertexNum][MaxVertexNum]; /* �ڽӾ��� */
	int Gcost[MaxVertexNum][MaxVertexNum];
	int S;
	int D;
//	DataType Data[MaxVertexNum];      /* �涥������� */
	/* ע�⣺�ܶ�����£����������ݣ���ʱData[]���Բ��ó��� */
};
typedef PtrToGNode MGraph; /* ���ڽӾ���洢��ͼ���� */



MGraph CreateGraph(int VertexNum)
{ /* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode)); /* ����ͼ */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* ��ʼ���ڽӾ��� */
	/* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
	for (V = 0; V < Graph->Nv; V++){
		for (W = 0; W < Graph->Nv; W++){
			Graph->G[V][W] = INFINITY;
			Graph->Gcost[V][W] = INFINITY;
		}			
	}
	

	return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
	/* ����� <V1, V2> */
	Graph->G[E->V1][E->V2] = E->Weight;
	/* ��������ͼ����Ҫ�����<V2, V1> */
	Graph->G[E->V2][E->V1] = E->Weight;

	Graph->Gcost[E->V1][E->V2] = E->Cost;
	Graph->Gcost[E->V2][E->V1] = E->Cost;
}

MGraph BuildGraph()
{
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	scanf("%d", &Nv);   /* ���붥����� */
	Graph = CreateGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */

	scanf("%d", &(Graph->Ne));   /* ������� */
	scanf("%d %d", &(Graph->S), &(Graph->D));

	if (Graph->Ne != 0) { /* ����б� */
		E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */
		/* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
		for (i = 0; i<Graph->Ne; i++) {
			scanf("%d %d %d %d", &E->V1, &E->V2, &E->Weight,&E->Cost);
			/* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
			InsertEdge(Graph, E);
		}
	}
	
	return Graph;
}


/* �ڽӾ���洢 - ��Ȩͼ�ĵ�Դ���·�㷨 */

Vertex FindMinDist(MGraph Graph, int dist[], int collected[])
{ /* ����δ����¼������dist��С�� */
	Vertex MinV, V;
	int MinDist = INFINITY;

	for (V = 0; V<Graph->Nv; V++) {
		if (collected[V] == 0 && dist[V]<MinDist) {
			/* ��Vδ����¼����dist[V]��С */
			MinDist = dist[V]; /* ������С���� */
			MinV = V; /* ���¶�Ӧ���� */
		}
	}
	if (MinDist < INFINITY) /* ���ҵ���Сdist */
		return MinV; /* ���ض�Ӧ�Ķ����±� */
	else 
		return ERROR;  /* �������Ķ��㲻���ڣ����ش����� */
}

void Dijkstra(MGraph Graph, int dist[], int cost[],Vertex S)
{
	int collected[MaxVertexNum];

	Vertex V, W;

	/* ��ʼ�����˴�Ĭ���ڽӾ����в����ڵı���INFINITY��ʾ */
	for (V = 0; V<Graph->Nv; V++) {
		dist[V] = Graph->G[S][V];
		cost[V] = Graph->Gcost[S][V];
		collected[V] = 0;
	}
	/* �Ƚ�������뼯�� */
	dist[S] = 0;
	cost[S] = 0;
	collected[S] = 1;

	while (1) {
		/* V = δ����¼������dist��С�� */
		V = FindMinDist(Graph, dist, collected);
		if (V == ERROR) /* ��������V������ */
			break;      /* �㷨���� */
		collected[V] = 1;  /* ��¼V */
		for (W = 0; W < Graph->Nv; W++){/* ��ͼ�е�ÿ������W */
			/* ��W��V���ڽӵ㲢��δ����¼ */
			if (collected[W] == 0 && Graph->G[V][W]<INFINITY) {
				
				/* ����¼Vʹ��dist[W]��С */
				if (dist[V] + Graph->G[V][W] < dist[W]) {
					dist[W] = dist[V] + Graph->G[V][W]; /* ����dist[W] */
					cost[W] = cost[V] + Graph->Gcost[V][W];
				}
				else if (dist[V] + Graph->G[V][W] == dist[W] && cost[W] > cost[V] + Graph->Gcost[V][W]){
					cost[W] = cost[V] + Graph->Gcost[V][W];
				}
			}
		} 
		
	} /* while����*/
	
}

int main(){
	MGraph Graph = BuildGraph();
	int dist[MaxVertexNum] = {};
	int cost[MaxVertexNum] = {};
	Dijkstra(Graph, dist, cost, Graph->S);
	printf("%d %d", dist[Graph->D], cost[Graph->D]);
}