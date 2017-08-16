#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

#define MaxSize 100
//typedef position1 position;
typedef struct position{
	int  x;
	int  y;
}Pos[MaxSize];

typedef struct GraphNode *PtrToGraph;
struct GraphNode{
//	position Cro[100];
	Pos P;
	int Nc;
	double D;
	int visited[100];
};
typedef PtrToGraph Graph;

void Save007(Graph G);
int DFS(Graph G,int v);
int FirstJump(Graph G,int v);
int IsSafe(Graph G,int v);
int Jump(Graph G, int W, int V);

int main(){
//	position Cro[100];
	int Nc, i;
	int D;
	Graph G = (Graph)malloc(sizeof(struct GraphNode));	
	scanf("%d %d", &Nc, &D);
	G->D = D;
	G->Nc = Nc;
	for (i = 0; i < Nc; i++){
		scanf("%d %d", &(G->P[i].x), &(G->P[i].y));
		G->visited[i] = 0;
	}
	Save007(G);
}


void Save007(Graph G){
	int i,answer=0;
	for (i = 0; i < G->Nc; i++){
		if (!G->visited[i] && FirstJump(G,i)){
			answer = DFS(G,i);
			if (answer == 1)
				break;
		}
	}

	if (answer == 1)
		printf("Yes\n");
	else
		printf("No\n");
}

int FirstJump(Graph G,int v){
	double D = (G->P[v].x)*(G->P[v].x) + (G->P[v].y)*(G->P[v].y);
	double Dmax = (G->D + 7.5)*(G->D + 7.5);
	if (D <= Dmax)
		return 1;
	else
		return 0;
}

int DFS(Graph G, int v){
	int answer = 0;
	G->visited[v] = 1;
	if (IsSafe(G,v))
	{
		answer = 1;
	}
	else
	{
		for (int W = 0; W < G->Nc; W++){
			if ((!G->visited[W]) && (Jump(G, v, W)))
			{
				answer = DFS(G, W);
				if (answer == 1)
					break;
			}
		}
	}
	return answer;
}

int IsSafe(Graph G,int v){
	double x = G->P[v].x;
	double y = G->P[v].y;
	double D = G->D;
	int res = 0;
	if ((x + 50) <= D)
		res = 1;
	if ((50 - x) <= D)
		res = 1;
	if ((y + 50) <= D)
		res = 1;
	if ((50 - y) <= D)
		res = 1;
	return res;
}

int Jump(Graph G, int W, int V){
	double x1 = G->P[V].x;
	double y1 = G->P[V].y;
	double x2 = G->P[W].x;
	double y2 = G->P[W].y;
	double D = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
	double Dmax = (G->D)*(G->D);
	return (D <= Dmax) ? 1 : 0;
}