#include<stdio.h>
#include<stdlib.h>

#define MaxVertexNum 500


typedef int Vertex;         /* �ö����±��ʾ����,Ϊ���� */
typedef int Distance;        /* �ߵ�Ȩֵ��Ϊ���� */
typedef int Money;

/* �ߵĶ��� */
typedef struct ENode *PtrToENode;
struct ENode{
	Vertex V1, V2;      /* �����<V1, V2> */
	Distance d;  /* Ȩ�� */
	Money m;
};
typedef PtrToENode Edge;

/* �ڽӵ�Ķ��� */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
	Vertex AdjV;        /* �ڽӵ��±� */
	Distance d;  /* ��Ȩ�� */
	Money m;
	PtrToAdjVNode Next;    /* ָ����һ���ڽӵ��ָ�� */
};

/* �����ͷ���Ķ��� */
typedef struct Vnode{
	PtrToAdjVNode FirstEdge;/* �߱�ͷָ�� */
} AdjList[MaxVertexNum];    /* AdjList���ڽӱ����� */

/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv;     /* ������ */
	int Ne;     /* ����   */
	AdjList G;  /* �ڽӱ� */
};
typedef PtrToGNode LGraph; /* ���ڽӱ�ʽ�洢��ͼ���� */

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

	/* ����� <V1, V2> */
	/* ΪV2�����µ��ڽӵ� */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->d = E->d;
	NewNode->m = E->m;
	/* ��V2����V1�ı�ͷ */
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	/* ��������ͼ����Ҫ����� <V2, V1> */
	/* ΪV1�����µ��ڽӵ� */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->d = E->d;
	NewNode->m = E->m;
	/* ��V1����V2�ı�ͷ */
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}