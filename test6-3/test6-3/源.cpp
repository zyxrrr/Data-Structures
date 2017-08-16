#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

#define max 10000
int Visited[max];

typedef int vertex;
typedef int weight;
typedef struct ENode *PtrToENode;
struct ENode
{
	vertex v1, v2;
	weight w;
};
typedef PtrToENode Edge;

typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv;
	int Ne;
	int G[max][max];
};
typedef PtrToGNode MGraph;

MGraph CreateGraph(int N){
	MGraph Graph;
	vertex i, j;
	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Ne = 0;
	Graph->Nv = N;
	for ( i = 0; i < Graph->Nv; i++){
		for ( j = 0; j < Graph->Nv; j++){
			Graph->G[i][j] = 0;
		}
	}
	
	return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
	/* 插入边 <V1, V2> */
	Graph->G[E->v1][E->v2] = E->w;
	/* 若是无向图，还要插入边<V2, V1> */
	Graph->G[E->v2][E->v1] = E->w;
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

int  AddQ(Queue Q, ElementType X)
{
	if (IsFull(Q)) {
		printf("队列满");
		return 0;
	}
	else {
		Q->Rear = (Q->Rear + 1) % Q->MaxSize;
		Q->Data[Q->Rear] = X;
		return 1;
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


int BFS(MGraph Graph,vertex V){
	Queue Q = CreateQueue(max);
	int count,level,last,tail = 0;
	level = 0;
	Visited[V] = 1;
	count = 1;
	last = V;	
	AddQ(Q, V);
	while (!IsEmpty(Q))
	{
		V = DeleteQ(Q);
		for (int i = 0;(( i < Graph->Nv) && (Graph->G[V][i] == 1)); i++){//这样写会导致后一个判断失败时，不进入循环，程序出错
			if ((!Visited[i]) ){
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
		if (level==6)
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
		Queue Q = CreateQueue(max);
		printf("%d", i+1);
		count = BFS(Graph, i);
		per = (double)(count) / N;
//		printf("%d\n", count);
		printf(": %.2f", per * 100);
		printf("%%");
		printf("\n");
	}
}

int main(){
	int Nv, Ne,i,v1,v2;
	

	scanf("%d %d", &Nv, &Ne);
	MGraph Graph=CreateGraph(Nv);
	Graph->Ne = Ne;
	Edge E = (Edge)malloc(sizeof(struct ENode));
	E->w = 1;
	for (i = 0; i < Ne; i++){
		scanf("%d %d", &v1, &v2);
		E->v1 = v1-1;
		E->v2 = v2-1;
		InsertEdge(Graph, E);
	}

	SDS(Graph);
}