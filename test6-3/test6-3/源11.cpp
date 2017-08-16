#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef
enum {

	false, true
} bool;

#define MaxVertexNum 10000
int Visited[MaxVertexNum];
typedef struct GNode *PtrToGNode;
typedef int WeightType;
struct GNode
{
	int Nv;
	int Ne;
	WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

typedef int Vertex;
MGraph CreateGraph(int VertexNum){
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	for (V = 0; V < Graph->Nv; V++){
		for (W = 0; W < Graph->Nv; W++){
			Graph->G[V][W] = 0;//0代表没有边
		}
	}
	return Graph;
}

typedef struct ENode *PtrToENode;
struct ENode{
	Vertex V1, V2;
	WeightType Weight;
};
typedef PtrToENode Edge;

void InsertEdge(MGraph Graph, Edge E){
	Graph->G[E->V1][E->V2] = E->Weight;
	Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildGraph(){
	MGraph Graph;
	Edge E;
	int Nv, i;
//	int tmp1, tmp2;
	scanf("%d", &Nv);
	Graph = CreateGraph(Nv);
	scanf("%d", &(Graph->Ne));
	if (Graph->Ne != 0){
		E = (Edge)malloc(sizeof(struct ENode));
		E->Weight = 1;
		for (i = 0; i < Graph->Ne; i++){
			scanf("%d %d", &E->V1, &E->V2);
			E->V1 = E->V1 - 1;
			E->V2 = E->V2 - 1;
			InsertEdge(Graph, E);
		}
	}
	return Graph;
}



int IsEdge(MGraph Graph, Vertex V, Vertex W){
	return Graph->G[V][W] == 1 ? 1 : 0;
}


typedef int ElementType;
typedef int Position;
struct QNode {
	ElementType *Data;     /* 存储元素的数组 */
	Position Front, Rear;  /* 队列的头、尾指针 */
	int MaxSize;           /* 队列最大容量 */
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
		printf("队列满");
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
		printf("队列空");
		return -1;
	}
	else  {
		Q->Front = (Q->Front + 1) % Q->MaxSize;
		return  Q->Data[Q->Front];
	}
}





int BFS(MGraph Graph, Vertex V){
	Queue Q = CreateQueue(MaxVertexNum); /* 创建空队列, MaxSize为外部定义的常数 */
	int count, level, last, tail ,i= 0;
	level = 0;
	Visited[V] = 1;
	count = 1;
	last = V;
	AddQ(Q, V);
	while (!IsEmpty(Q))
	{
		V = DeleteQ(Q);
		for ( i = 0; i < Graph->Nv ; i++){
			if (!Visited[i] && IsEdge(Graph,i,V)){
				Visited[i] = 1;
				AddQ(Q, i);
				count++;
				tail = i;
			}
		}
		if (V == last){
			level++;
			last = tail;
		}
		if (level == 6)
		{
			break;
		}
	}
	return count;
}

void SDS(MGraph Graph){
	double per;
	int count,i,j;
	double N = (double)(Graph->Nv);
	for ( i = 0; i < Graph->Nv; i++){
		for ( j = 0; j < Graph->Nv; j++)
		{
			Visited[j] = 0;
		}
	//	Queue Q = CreateQueue(max);
		printf("%d", i + 1);
		count = BFS(Graph, i);
		per = (double)(count) / N;
		//		printf("%d\n", count);
		printf(": %.2f", per * 100);
		printf("%%");
		printf("\n");
	}
}

int main(){
	int i;
	MGraph Graph = BuildGraph();

	for (i = 0; i < MaxVertexNum; i++){
		Visited[i] = 0;
	}

	SDS(Graph);

	
}