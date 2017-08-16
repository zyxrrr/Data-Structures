#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

#define MaxVertexNum 100
#define ERROR -1
int G[MaxVertexNum][MaxVertexNum] ;
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
		printf("队列满");
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
		printf("队列空");
		return ERROR;
	}
	else  {
		Q->Front = (Q->Front + 1) % Q->MaxSize;
		return  Q->Data[Q->Front];
	}
}





/* 图的邻接表表示法 */

#define MaxVertexNum 100    /* 最大顶点数设为100 */
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */
typedef char DataType;        /* 顶点存储的数据类型设为字符型 */

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode{
	Vertex V1, V2;      /* 有向边<V1, V2> */
	WeightType Weight;  /* 权重 */
};
typedef PtrToENode Edge;

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
	Vertex AdjV;        /* 邻接点下标 */
	WeightType Weight;  /* 边权重 */
	PtrToAdjVNode Next;    /* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct Vnode{
	PtrToAdjVNode FirstEdge;/* 边表头指针 */
//	DataType Data;            /* 存顶点的数据 */
	/* 注意：很多情况下，顶点无数据，此时Data可以不用出现 */
} AdjList[MaxVertexNum];    /* AdjList是邻接表类型 */

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv;     /* 顶点数 */
	int Ne;     /* 边数   */
	AdjList G;  /* 邻接表 */
};
typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */



LGraph CreateGraph(int VertexNum)
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode)); /* 建立图 */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 初始化邻接表头指针 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
	for (V = 0; V<Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
	PtrToAdjVNode NewNode;


	G[E->V1][E->V2] = E->Weight;



	/* 插入边 <V1, V2> */
	/* 为V2建立新的邻接点 */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;
	/* 将V2插入V1的表头 */
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	/* 若是无向图，还要插入边 <V2, V1> */
	/* 为V1建立新的邻接点 */
/*	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;*/
	/* 将V1插入V2的表头 */
//	NewNode->Next = Graph->G[E->V2].FirstEdge;
//	Graph->G[E->V2].FirstEdge = NewNode; 
}

LGraph BuildGraph()
{
	LGraph Graph;
	Edge E;
//	Vertex V;
	int Nv, i;

	

	scanf("%d", &Nv);   /* 读入顶点个数 */
	Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */

	for (int i = 0; i < Graph->Nv; i++){
		for (int j = 0; j < Graph->Nv; j++){
			G[i][j] = 100000;
		}
	}

	scanf("%d", &(Graph->Ne));   /* 读入边数 */
	if (Graph->Ne != 0) { /* 如果有边 */
		E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */
		/* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
		for (i = 0; i<Graph->Ne; i++) {
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			/* 注意：如果权重不是整型，Weight的读入格式要改 */
			InsertEdge(Graph, E);
		}
	}

	/* 如果顶点有数据的话，读入数据 */
//	for (V = 0; V<Graph->Nv; V++)
//		scanf(" %c", &(Graph->G[V].Data));

	return Graph;
}

/* 邻接表存储 - 拓扑排序算法 */
int max(int a, int b){
	return a >= b ? a : b;
}

int TopSort(LGraph Graph)
{ /* 对Graph进行拓扑排序,  TopOrder[]顺序存储排序后的顶点下标 */
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

	/* 初始化Indegree[] */
	for (V = 0; V<Graph->Nv; V++)
		Indegree[V] = 0;

	/* 遍历图，得到Indegree[] */
	for (V = 0; V < Graph->Nv; V++)
	{
		G[V][V] = 0;
		for (W = Graph->G[V].FirstEdge; W; W = W->Next){			
			Indegree[W->AdjV]++; /* 对有向边<V, W->AdjV>累计终点的入度 */
		}
			
	}
		

	/* 将所有入度为0的顶点入列 */
	for (V = 0; V<Graph->Nv; V++)
		if (Indegree[V] == 0)
			AddQ(Q, V);

	/* 下面进入拓扑排序 */
	cnt = 0;
	flag = 0;
	while (!IsEmpty(Q)){

		V = DeleteQ(Q); /* 弹出一个入度为0的顶点 */
//		flag = V;
		if (flag == 0)
		{
			front = V;
			flag = 1;
		}			
		

		Earliest[V] = max(G[front][V] + Earliest[front], Earliest[front]);
		cnt++;
//		TopOrder[cnt++] = V; /* 将之存为结果序列的下一个元素 */
		/* 对V的每个邻接点W->AdjV */
		for (W = Graph->G[V].FirstEdge; W; W = W->Next)
			if (--Indegree[W->AdjV] == 0)/* 若删除V使得W->AdjV入度为0 */
				AddQ(Q, W->AdjV); /* 则该顶点入列 */

		front = V;
	} /* while结束*/
//	max1 = Earliest[0];
//	for (int i = 0; i < Graph->Nv; i++){
//		sum = Earliest[i];		
////		if (sum>max1)
//			max1 = sum;
//	}

	if (cnt != Graph->Nv)
		return 0; /* 说明图中有回路, 返回不成功标志 */
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