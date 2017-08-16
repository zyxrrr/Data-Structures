#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

#define MaxVertexNum 10
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

	scanf("%d", &Nv);
	Graph = CreateGraph(Nv);
	scanf("%d", &(Graph->Ne));
	if (Graph->Ne != 0){
		E = (Edge)malloc(sizeof(struct ENode));
		E->Weight = 1;
		for (i = 0; i < Graph->Ne; i++){
			scanf("%d %d", &E->V1, &E->V2);

			InsertEdge(Graph, E);
		}
	}
	return Graph;
}

void Visit(Vertex V)
{
	printf("%d ", V);
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


void BFS(MGraph Graph, Vertex S, void(*Visit)(Vertex),int Visited[])
{   /* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
	Queue Q;
	Vertex V, W;

	Q = CreateQueue(MaxVertexNum); /* 创建空队列, MaxSize为外部定义的常数 */
	/* 访问顶点S：此处可根据具体访问需要改写 */
	Visit(S);
	Visited[S] = 1; /* 标记S已访问 */
	AddQ(Q, S); /* S入队列 */

	while (!IsEmpty(Q)) {
		V = DeleteQ(Q);  /* 弹出V */
		for (W = 0; W<Graph->Nv; W++) /* 对图中的每个顶点W */
			/* 若W是V的邻接点并且未访问过 */
		if (!Visited[W] && IsEdge(Graph, V, W)) {
			/* 访问顶点W */
			Visit(W);
			Visited[W] = 1; /* 标记W已访问 */
			AddQ(Q, W); /* W入队列 */
		}
	} /* while结束*/
}

void ListComponentsBFS(MGraph Graph,int Visited[]){
	int i;
	for (i = 0; i < Graph->Nv; i++){		
		if (!Visited[i]){
			printf("{ ");
			BFS(Graph, i, *Visit, Visited);
			printf("}\n");
		}			
	}
}

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
	Vertex AdjV;
	//WeightType 
	PtrToAdjVNode Next;
};

typedef struct Vnode{
	PtrToAdjVNode FirstEdge;
}AdjList[MaxVertexNum];

typedef struct AGNode *PtrToAGNode;
struct AGNode{
	int Nv;
	int Ne;
	AdjList G;
};
typedef PtrToAGNode LGraph;

LGraph CreateLGraph(int VertexNum){
	Vertex V;
	LGraph Graph;

	Graph =(LGraph)malloc(sizeof(struct AGNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	for (V = 0; V < Graph->Nv; V++){
		Graph->G[V].FirstEdge = NULL;
	}
	return Graph;
}

void InsertLGEdge(LGraph Graph, Edge E){
	PtrToAdjVNode NewNode;
	PtrToAdjVNode NewNode1;
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	NewNode1 = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode1->AdjV = E->V1;
	NewNode1->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode1;
}

LGraph BuildLGraph(MGraph Graph){
	LGraph lgraph;
	int i,j;
	//int Nv;
	//scanf("%d")
//	lgraph = (LGraph)malloc(sizeof(struct AGNode));
	lgraph = CreateLGraph(Graph->Nv);


	lgraph->Ne = Graph->Ne;
//	lgraph->Nv = Graph->Nv;
	Edge E = (Edge)malloc(sizeof(struct ENode));
	E->Weight = 1;
	for (i = (Graph->Nv) - 1; i >= 0; i--){
		for (j = i ; j >= 0; j--){
			if (Graph->G[i][j] == 1){
				E->V1 = i;
				E->V2 = j;
				InsertLGEdge(lgraph, E);
			}
		}
		
	}
	return lgraph;
}

void DFS(LGraph Graph, Vertex V, void(*Visit)(Vertex))
{   /* 以V为出发点对邻接表存储的图Graph进行DFS搜索 */
	PtrToAdjVNode W;

	Visit(V); /* 访问第V个顶点 */
	Visited[V] = 1; /* 标记V已访问 */

	for (W = Graph->G[V].FirstEdge; W; W = W->Next){/* 对V的每个邻接点W->AdjV */
		if (!Visited[W->AdjV])    /* 若W->AdjV未被访问 */
			DFS(Graph, W->AdjV, Visit);    /* 则递归访问之 */
	}
	
	
}

void ListComponentDFS(LGraph lgraph, int Visited[]){
	int i;
	for (i = 0; i < lgraph->Nv; i++){
		if (!Visited[i]){
			printf("{ ");
			DFS(lgraph, i, Visit);
			printf("}\n");
//			DFS(lgraph, i, Visit, Visited);
		}
	}
}

int main(){
	int i;
	MGraph Graph = BuildGraph();
//	int Visited[MaxVertexNum];
	for (i = 0; i < MaxVertexNum; i++){
		Visited[i] = 0;
	}
//	BFS(Graph, 0, *Visit, Visited);


	LGraph lgraph = BuildLGraph(Graph);
	ListComponentDFS(lgraph, Visited);
	
	for (i = 0; i < MaxVertexNum; i++){
		Visited[i] = 0;
	}
	ListComponentsBFS(Graph, Visited);
}