#include<stdio.h>
#include<stdlib.h>
/* 图的邻接矩阵表示法 */

#define ERROR -1
#define MaxVertexNum 500    /* 最大顶点数设为100 */
#define INFINITY 655350        /* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */
//typedef char DataType;        /* 顶点存储的数据类型设为字符型 */

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode{
	Vertex V1, V2;      /* 有向边<V1, V2> */
	WeightType Weight;  /* 权重 */
	int Cost;           /*路费*/
};
typedef PtrToENode Edge;

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv;  /* 顶点数 */
	int Ne;  /* 边数   */
	WeightType G[MaxVertexNum][MaxVertexNum]; /* 邻接矩阵 */
	int Gcost[MaxVertexNum][MaxVertexNum];
	int S;
	int D;
//	DataType Data[MaxVertexNum];      /* 存顶点的数据 */
	/* 注意：很多情况下，顶点无数据，此时Data[]可以不用出现 */
};
typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */



MGraph CreateGraph(int VertexNum)
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode)); /* 建立图 */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 初始化邻接矩阵 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
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
	/* 插入边 <V1, V2> */
	Graph->G[E->V1][E->V2] = E->Weight;
	/* 若是无向图，还要插入边<V2, V1> */
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

	scanf("%d", &Nv);   /* 读入顶点个数 */
	Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */

	scanf("%d", &(Graph->Ne));   /* 读入边数 */
	scanf("%d %d", &(Graph->S), &(Graph->D));

	if (Graph->Ne != 0) { /* 如果有边 */
		E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */
		/* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
		for (i = 0; i<Graph->Ne; i++) {
			scanf("%d %d %d %d", &E->V1, &E->V2, &E->Weight,&E->Cost);
			/* 注意：如果权重不是整型，Weight的读入格式要改 */
			InsertEdge(Graph, E);
		}
	}
	
	return Graph;
}


/* 邻接矩阵存储 - 有权图的单源最短路算法 */

Vertex FindMinDist(MGraph Graph, int dist[], int collected[])
{ /* 返回未被收录顶点中dist最小者 */
	Vertex MinV, V;
	int MinDist = INFINITY;

	for (V = 0; V<Graph->Nv; V++) {
		if (collected[V] == 0 && dist[V]<MinDist) {
			/* 若V未被收录，且dist[V]更小 */
			MinDist = dist[V]; /* 更新最小距离 */
			MinV = V; /* 更新对应顶点 */
		}
	}
	if (MinDist < INFINITY) /* 若找到最小dist */
		return MinV; /* 返回对应的顶点下标 */
	else 
		return ERROR;  /* 若这样的顶点不存在，返回错误标记 */
}

void Dijkstra(MGraph Graph, int dist[], int cost[],Vertex S)
{
	int collected[MaxVertexNum];

	Vertex V, W;

	/* 初始化：此处默认邻接矩阵中不存在的边用INFINITY表示 */
	for (V = 0; V<Graph->Nv; V++) {
		dist[V] = Graph->G[S][V];
		cost[V] = Graph->Gcost[S][V];
		collected[V] = 0;
	}
	/* 先将起点收入集合 */
	dist[S] = 0;
	cost[S] = 0;
	collected[S] = 1;

	while (1) {
		/* V = 未被收录顶点中dist最小者 */
		V = FindMinDist(Graph, dist, collected);
		if (V == ERROR) /* 若这样的V不存在 */
			break;      /* 算法结束 */
		collected[V] = 1;  /* 收录V */
		for (W = 0; W < Graph->Nv; W++){/* 对图中的每个顶点W */
			/* 若W是V的邻接点并且未被收录 */
			if (collected[W] == 0 && Graph->G[V][W]<INFINITY) {
				
				/* 若收录V使得dist[W]变小 */
				if (dist[V] + Graph->G[V][W] < dist[W]) {
					dist[W] = dist[V] + Graph->G[V][W]; /* 更新dist[W] */
					cost[W] = cost[V] + Graph->Gcost[V][W];
				}
				else if (dist[V] + Graph->G[V][W] == dist[W] && cost[W] > cost[V] + Graph->Gcost[V][W]){
					cost[W] = cost[V] + Graph->Gcost[V][W];
				}
			}
		} 
		
	} /* while结束*/
	
}

int main(){
	MGraph Graph = BuildGraph();
	int dist[MaxVertexNum] = {};
	int cost[MaxVertexNum] = {};
	Dijkstra(Graph, dist, cost, Graph->S);
	printf("%d %d", dist[Graph->D], cost[Graph->D]);
}