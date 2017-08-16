#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

#define MaxVertexNum 100
#define ERROR -1
int G[MaxVertexNum][MaxVertexNum] ;
typedef int ElementType;
typedef int Position;
struct QNode {
	ElementType *Data;     /* �洢Ԫ�ص����� */
	Position Front, Rear;  /* ���е�ͷ��βָ�� */
	int MaxSize;           /* ����������� */
};
typedef struct QNode *Queue;

Queue CreateQueue(int MaxSize)
{
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
	Q->Front = Q->Rear = 0;
	Q->MaxSize = MaxSize;
	return Q;
}

int IsFull(Queue Q)
{
	if ((Q->Rear + 1) % Q->MaxSize == Q->Front)
		return 1;
	else
		return 0;
}

int AddQ(Queue Q, ElementType X)
{
	if (IsFull(Q)) {
		printf("������");
		return 0;
	}
	else {
		Q->Rear = (Q->Rear + 1) % Q->MaxSize;
		Q->Data[Q->Rear] = X;
		return 1;
	}
}

int IsEmpty(Queue Q)
{
	if (Q->Front == Q->Rear)
		return 1;
	else
		return 0;
}

ElementType DeleteQ(Queue Q)
{
	if (IsEmpty(Q)) {
		printf("���п�");
		return ERROR;
	}
	else  {
		Q->Front = (Q->Front + 1) % Q->MaxSize;
		return  Q->Data[Q->Front];
	}
}





/* ͼ���ڽӱ��ʾ�� */

#define MaxVertexNum 100    /* ��󶥵�����Ϊ100 */
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

/* �ڽӵ�Ķ��� */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
	Vertex AdjV;        /* �ڽӵ��±� */
	WeightType Weight;  /* ��Ȩ�� */
	PtrToAdjVNode Next;    /* ָ����һ���ڽӵ��ָ�� */
};

/* �����ͷ���Ķ��� */
typedef struct Vnode{
	PtrToAdjVNode FirstEdge;/* �߱�ͷָ�� */
//	DataType Data;            /* �涥������� */
	/* ע�⣺�ܶ�����£����������ݣ���ʱData���Բ��ó��� */
} AdjList[MaxVertexNum];    /* AdjList���ڽӱ����� */

/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv;     /* ������ */
	int Ne;     /* ����   */
	AdjList G;  /* �ڽӱ� */
};
typedef PtrToGNode LGraph; /* ���ڽӱ�ʽ�洢��ͼ���� */



LGraph CreateGraph(int VertexNum)
{ /* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode)); /* ����ͼ */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* ��ʼ���ڽӱ�ͷָ�� */
	/* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
	for (V = 0; V<Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
	PtrToAdjVNode NewNode;


	G[E->V1][E->V2] = E->Weight;



	/* ����� <V1, V2> */
	/* ΪV2�����µ��ڽӵ� */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;
	/* ��V2����V1�ı�ͷ */
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	/* ��������ͼ����Ҫ����� <V2, V1> */
	/* ΪV1�����µ��ڽӵ� */
/*	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;*/
	/* ��V1����V2�ı�ͷ */
//	NewNode->Next = Graph->G[E->V2].FirstEdge;
//	Graph->G[E->V2].FirstEdge = NewNode; 
}

LGraph BuildGraph()
{
	LGraph Graph;
	Edge E;
//	Vertex V;
	int Nv, i;

	

	scanf("%d", &Nv);   /* ���붥����� */
	Graph = CreateGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */

	for (int i = 0; i < Graph->Nv; i++){
		for (int j = 0; j < Graph->Nv; j++){
			G[i][j] = 100000;
		}
	}

	scanf("%d", &(Graph->Ne));   /* ������� */
	if (Graph->Ne != 0) { /* ����б� */
		E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */
		/* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
		for (i = 0; i<Graph->Ne; i++) {
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			/* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
			InsertEdge(Graph, E);
		}
	}

	/* ������������ݵĻ����������� */
//	for (V = 0; V<Graph->Nv; V++)
//		scanf(" %c", &(Graph->G[V].Data));

	return Graph;
}

/* �ڽӱ�洢 - ���������㷨 */
int max(int a, int b){
	return a >= b ? a : b;
}

int TopSort(LGraph Graph)
{ /* ��Graph������������,  TopOrder[]˳��洢�����Ķ����±� */
	int flag = 0;
//	int sum;
	int Indegree[MaxVertexNum], cnt,i;
	int front;

	Vertex V;
	PtrToAdjVNode W;
	Queue Q = CreateQueue(Graph->Nv);
	int Earliest[MaxVertexNum];
	for (i = 0; i < MaxVertexNum; i++)
		Earliest[i] = 0;

	/* ��ʼ��Indegree[] */
	for (V = 0; V<Graph->Nv; V++)
		Indegree[V] = 0;

	/* ����ͼ���õ�Indegree[] */
	for (V = 0; V < Graph->Nv; V++)
	{
		G[V][V] = 0;
		for (W = Graph->G[V].FirstEdge; W; W = W->Next){			
			Indegree[W->AdjV]++; /* �������<V, W->AdjV>�ۼ��յ����� */
		}
			
	}
		

	/* ���������Ϊ0�Ķ������� */
	for (V = 0; V<Graph->Nv; V++)
		if (Indegree[V] == 0)
			AddQ(Q, V);

	/* ��������������� */
	cnt = 0;
	flag = 0;
	while (!IsEmpty(Q)){

		V = DeleteQ(Q); /* ����һ�����Ϊ0�Ķ��� */
//		flag = V;
		if (flag == 0)
		{
			front = V;
			flag = 1;
		}			
		

		Earliest[V] = max(G[front][V] + Earliest[front], Earliest[front]);
		cnt++;
//		TopOrder[cnt++] = V; /* ��֮��Ϊ������е���һ��Ԫ�� */
		/* ��V��ÿ���ڽӵ�W->AdjV */
		for (W = Graph->G[V].FirstEdge; W; W = W->Next)
			if (--Indegree[W->AdjV] == 0)/* ��ɾ��Vʹ��W->AdjV���Ϊ0 */
				AddQ(Q, W->AdjV); /* ��ö������� */

		front = V;
	} /* while����*/
//	max1 = Earliest[0];
//	for (int i = 0; i < Graph->Nv; i++){
//		sum = Earliest[i];		
////		if (sum>max1)
//			max1 = sum;
//	}

	if (cnt != Graph->Nv)
		return 0; /* ˵��ͼ���л�·, ���ز��ɹ���־ */
	else
	{
//	return max1;
		return Earliest[V];
	}
	
}


int main(){
	LGraph G1 = BuildGraph();
	int sum = TopSort(G1);

	if (sum)
		printf("%d\n", sum);
	else
		printf("Impossible\n");
}