#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

#define MaxV 101
#define INFINITE 10001
typedef struct GraphNode *PtrToGraph;
struct GraphNode{
	int Nv;
	int Ne;
	int G[MaxV][MaxV];
};
typedef PtrToGraph MGraph;

typedef struct ResultNode *PtrToRes;
struct ResultNode{
	int Nv;
	int Num[MaxV];
	int Len[MaxV];
};
typedef PtrToRes MRes;

MGraph BuildGraph();
MGraph InsertGraph(MGraph Graph,int v1,int v2,int len);
MRes Floyd(MGraph Graph);
void PrintResult(MRes res);

int main(){
	MGraph Graph=BuildGraph();
	MRes res = Floyd(Graph);
	PrintResult(res);
/*	printf("%d", INFINITE);
	for (int i = 1; i <= res->Nv; i++){
		printf("%d %d\n", i, res->Len[i]);
	}*/
}

MGraph BuildGraph(){
	int i, j;
	int v1, v2, str_len;
	MGraph Graph = (MGraph)malloc(sizeof(struct GraphNode));
	
	scanf("%d %d", &(Graph->Nv), &(Graph->Ne));

	for (i = 1; i <= Graph->Nv; i++){
		for (j = 1; j <= Graph->Nv; j++){
			Graph->G[i][j] = INFINITE;
		}
	}

	for (i = 0; i < Graph->Ne; i++){
		scanf("%d %d %d", &v1, &v2, &str_len);
		InsertGraph(Graph, v1, v2, str_len);
	}
	return Graph;
}

MGraph InsertGraph(MGraph Graph,int v1, int v2, int len){
	Graph->G[v1][v2] = len;
	Graph->G[v2][v1] = len;
	return Graph;
}

MRes Floyd(MGraph Graph){
	int i, j, k,max;
	int D[MaxV][MaxV];
	MRes result = (MRes)malloc(sizeof(struct ResultNode));
	/* 初始化 */
	for (i = 1; i <= Graph->Nv; i++){
		for (j = 1; j<=Graph->Nv; j++) {
			D[i][j] = Graph->G[i][j];
//			path[i][j] = -1;
		}
	}
	

	for (k = 1; k <= Graph->Nv; k++){
		for (i = 1; i <= Graph->Nv; i++){
			for (j = 1; j <= Graph->Nv; j++){
				if (D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
	//				result->Num[i] = i;
	//				result->Num[i] = D[i][j];
	//				if (i == j && D[i][j]<0) /* 若发现负值圈 */
	//					return false; /* 不能正确解决，返回错误标记 */
	//				path[i][j] = k;
				}
			}
		}
	}
	
	for (i = 1; i <= Graph->Nv; i++){
		max = 0;
		result->Num[i] = i;
		for (j = 1; j <= Graph->Nv; j++){
			if (i!=j && D[i][j] > max){
				max = D[i][j];
				result->Len[i] = max;
			}	
		}
	}
	result->Nv = Graph->Nv;
	return result;
}

void PrintResult(MRes res){
	int i,min,j;
	j = 0;
	int flag = 0;
//	min = res->Len[1];//这样会出错，当需要输出最小为第一个点时，不能进入后面的if进行赋值
	min = INFINITE;
	for (i = 1; i <= res->Nv; i++){		
		if (res->Len[i] < INFINITE){
			flag = 1;
			if (res->Len[i]<min){
				min = res->Len[i];
				j = i;
			}
		}
	}
	if (flag){
		printf("%d %d\n", j, min);
	}
	else
	{
		printf("0\n");
	}
}