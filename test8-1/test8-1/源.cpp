#include<stdio.h>
#include<stdlib.h>

/* ͼ���ڽӾ����ʾ�� */

#define MaxVertexNum 1000    /* ��󶥵�����Ϊ100 */
#define INFINITY 65535        /* ����Ϊ˫�ֽ��޷������������ֵ65535*/
#define ERROR -1
typedef int Vertex;         /* �ö����±��ʾ����,Ϊ���� */
typedef int WeightType;        /* �ߵ�Ȩֵ��Ϊ���� */
typedef char DataType;        /* ����洢������������Ϊ�ַ��� */

/* �ߵĶ��� */
typedef struct ENode *PtrToENode;
struct ENode{
	Vertex V1, V2;      /* �����<V1, V2> */
	WeightType Weight;  /* Ȩ�� */
};
typedef PtrToENode Edge;

/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv;  /* ������ */
	int Ne;  /* ����   */
	WeightType G[MaxVertexNum][MaxVertexNum]; /* �ڽӾ��� */
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
	for (V = 0; V<Graph->Nv; V++)
		for (W = 0; W<Graph->Nv; W++)
			Graph->G[V][W] = INFINITY;

	return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
	/* ����� <V1, V2> */
	Graph->G[E->V1][E->V2] = E->Weight;
	/* ��������ͼ����Ҫ�����<V2, V1> */
	Graph->G[E->V2][E->V1] = E->Weight;
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
	if (Graph->Ne != 0) { /* ����б� */
		E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */
		/* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
		for (i = 0; i<Graph->Ne; i++) {
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			/* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
			E->V1 = E->V1 - 1;
			E->V2 = E->V2 - 1;
			InsertEdge(Graph, E);
		}
	}

	/* ������������ݵĻ����������� */
//	for (V = 0; V<Graph->Nv; V++)
//		scanf(" %c", &(Graph->Data[V]));

	return Graph;
}


/* �ڽӾ���洢 - Prim��С�������㷨 */

Vertex FindMinDist(MGraph Graph, WeightType dist[])
{ /* ����δ����¼������dist��С�� */
	Vertex MinV, V;
	WeightType MinDist = INFINITY;

	for (V = 0; V<Graph->Nv; V++) {
		if (dist[V] != 0 && dist[V]<MinDist) {
			/* ��Vδ����¼����dist[V]��С */
			MinDist = dist[V]; /* ������С���� */
			MinV = V; /* ���¶�Ӧ���� */
		}
	}
	if (MinDist < INFINITY) /* ���ҵ���Сdist */
		return MinV; /* ���ض�Ӧ�Ķ����±� */
	else 
		return ERROR;  /* �������Ķ��㲻���ڣ�����-1��Ϊ��� */
}

int Prim(MGraph Graph)
{ /* ����С����������Ϊ�ڽӱ�洢��ͼMST��������СȨ�غ� */
	WeightType dist[MaxVertexNum], TotalWeight;
	Vertex parent[MaxVertexNum], V, W;
	int VCount;
	Edge E;

	/* ��ʼ����Ĭ�ϳ�ʼ���±���0 */
	for (V = 0; V<Graph->Nv; V++) {
		/* ���������V��Wû��ֱ�ӵıߣ���Graph->G[V][W]����ΪINFINITY */
		dist[V] = Graph->G[0][V];
		parent[V] = 0; /* ���Ҷ������ж���ĸ���㶼�ǳ�ʼ��0 */
	}
	TotalWeight = 0; /* ��ʼ��Ȩ�غ�     */
	VCount = 0;      /* ��ʼ����¼�Ķ����� */
	/* �����������ж��㵫û�бߵ�ͼ��ע�����ڽӱ�汾 */
//	MST = CreateGraph(Graph->Nv);
	E = (Edge)malloc(sizeof(struct ENode)); /* �����յı߽�� */

	/* ����ʼ��0��¼��MST */
	dist[0] = 0;
	VCount++;
	parent[0] = -1; /* ��ǰ������0 */

	while (1) {
		V = FindMinDist(Graph, dist);
		/* V = δ����¼������dist��С�� */
		if (V == ERROR) /* ��������V������ */
			break;   /* �㷨���� */

		/* ��V����Ӧ�ı�<parent[V], V>��¼��MST */
		E->V1 = parent[V];
		E->V2 = V;
		E->Weight = dist[V];
//		InsertEdge(MST, E);
		TotalWeight += dist[V];
		dist[V] = 0;
		VCount++;

		for (W = 0; W<Graph->Nv; W++) /* ��ͼ�е�ÿ������W */
		if (dist[W] != 0 && Graph->G[V][W]<INFINITY) {
			/* ��W��V���ڽӵ㲢��δ����¼ */
			if (Graph->G[V][W] < dist[W]) {
				/* ����¼Vʹ��dist[W]��С */
				dist[W] = Graph->G[V][W]; /* ����dist[W] */
				parent[W] = V; /* ������ */
			}
		}
	} /* while����*/
	if (VCount < Graph->Nv) /* MST���յĶ��㲻��|V|�� */
		TotalWeight = ERROR;
	return TotalWeight;   /* �㷨ִ����ϣ�������СȨ�غͻ������ */
}

int main(){
	MGraph G = BuildGraph();
	int Totla=Prim(G);
	if (Totla == -1)
		printf("-1\n");
	else
		printf("%d\n", Totla);

}