#include<stdio.h>
#include<stdlib.h>

#define MaxVertexNum 500


typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int Distance;        /* 边的权值设为整型 */
typedef int Money;

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode{
	Vertex V1, V2;      /* 有向边<V1, V2> */
	Distance d;  /* 权重 */
	Money m;
};
typedef PtrToENode Edge;

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
	Vertex AdjV;        /* 邻接点下标 */
	Distance d;  /* 边权重 */
	Money m;
	PtrToAdjVNode Next;    /* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct Vnode{
	PtrToAdjVNode FirstEdge;/* 边表头指针 */
} AdjList[MaxVertexNum];    /* AdjList是邻接表类型 */

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv;     /* 顶点数 */
	int Ne;     /* 边数   */
	AdjList G;  /* 邻接表 */
};
typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */

void InsertEdge(LGraph Graph, Edge E);
int main(){
	int N, M, S, D;
	int i,V;
	scanf("%d %d %d %d", &N, &M, &S, &D);
	LGraph Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Ne = M;
	Graph->Nv = N;
	for (V = 0; V < Graph->Nv; V++){
		Graph->G[V].FirstEdge = NULL;
	}		
	Edge E = (Edge)malloc(sizeof(struct ENode));
	for (i = 0; i < N; i++){
		scanf("%d %d %d %d", &(E->V1), &(E->V2), &(E->d), &(E->m));
		InsertEdge(Graph, E);
	}

}

void InsertEdge(LGraph Graph, Edge E)
{
	PtrToAdjVNode NewNode;

	/* 插入边 <V1, V2> */
	/* 为V2建立新的邻接点 */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->d = E->d;
	NewNode->m = E->m;
	/* 将V2插入V1的表头 */
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	/* 若是无向图，还要插入边 <V2, V1> */
	/* 为V1建立新的邻接点 */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->d = E->d;
	NewNode->m = E->m;
	/* 将V1插入V2的表头 */
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}