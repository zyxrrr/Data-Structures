#include<stdio.h>
#include<stdlib.h>

#define MaxV 101

typedef int ElementType;
typedef int Position1;
struct QNode {
	ElementType *Data;     /* �洢Ԫ�ص����� */
	Position1 Front, Rear;  /* ���е�ͷ��βָ�� */
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

bool IsFull(Queue Q)
{
	return ((Q->Rear + 1) % Q->MaxSize == Q->Front);
}

bool AddQ(Queue Q, ElementType X)
{
	if (IsFull(Q)) {
		printf("������");
		return false;
	}
	else {
		Q->Rear = (Q->Rear + 1) % Q->MaxSize;
		Q->Data[Q->Rear] = X;
		return true;
	}
}

bool IsEmpty(Queue Q)
{
	return (Q->Front == Q->Rear);
}

ElementType DeleteQ(Queue Q)
{
	if (IsEmpty(Q)) {
		printf("���п�");
		return -1;
	}
	else  {
		Q->Front = (Q->Front + 1) % Q->MaxSize;
		return  Q->Data[Q->Front];
	}
}

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
	int AdjV;
	PtrToAdjVNode Next;
//	A Next;
};
//typedef PtrToAdjVNode A;

typedef struct Vnode{
	PtrToAdjVNode FirstEdge;
}AdjList[MaxV];

typedef struct GNode *PtrToGNode;
struct GNode
{
	int Nv;
	int Ne;
	int D;
	AdjList G;
	Position P;
};
typedef PtrToGNode LGraph;

typedef struct Crr{
	int x;
	int y;
}Position[MaxV];

LGraph BuildLGraph();
double getDistance(int x,int y,int x1,int y1);
void Unweighted(LGraph Graph, int dist[], int path[], int S);

int main(){
	LGraph Graph=BuildLGraph();

}

LGraph BuildLGraph(){
	int i,j;
	double mind,nowd;
	LGraph Graph = (LGraph)malloc(sizeof(struct GNode));
	scanf("%d %d", &(Graph->Nv), &(Graph->D));
	for (i = 0; i < Graph->Nv; i++){
		scanf("%d %d", &(Graph->P[i + 1].x), &(Graph->P[i + 1].y));
	}
	Graph->P[0].x = 0;
	Graph->P[0].y = 0;
/*	mind = getDistance(Graph->P[1].x, Graph->P[1].y);
	for (i = 2; i <= Graph->Nv; i++){
		nowd = getDistance(Graph->P[i].x, Graph->P[i].y);
		if (nowd<)
	}
	*/
	return Graph;
}

double getDistance(int x, int y,int x1,int y1){
//	double x1 = double(x);
//	double y1 = double(y);
	int tmpx = x - x1;
	int tmpy = y - y1;
	return (tmpx*tmpx + tmpy*tmpy);
}

/* dist[]��path[]ȫ����ʼ��Ϊ-1 */
void Unweighted(LGraph Graph, int dist[], int path[], int  S)
{
	Queue Q;
	int  V;
	PtrToAdjVNode W;

	Q = CreateQueue(Graph->Nv); /* �����ն���, MaxSizeΪ�ⲿ����ĳ��� */
	dist[S] = 0; /* ��ʼ��Դ�� */
	AddQ(Q, S);

	while (!IsEmpty(Q)){
		V = DeleteQ(Q);
		for (W = Graph->G[V].FirstEdge; W; W = W->Next) /* ��V��ÿ���ڽӵ�W->AdjV */
		if (dist[W->AdjV] == -1) { /* ��W->AdjVδ�����ʹ� */
			dist[W->AdjV] = dist[V] + 1; /* W->AdjV��S�ľ������ */
			path[W->AdjV] = V; /* ��V��¼��S��W->AdjV��·���� */
			AddQ(Q, W->AdjV);
		}
	} /* while����*/
}