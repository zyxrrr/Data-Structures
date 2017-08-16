#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

struct TreeNode{	
	Tree left;
	Tree right;
}T[MaxTree];

typedef
enum {
	false, true
} bool;

typedef int Position;
struct QNode {
	int *Data;     /* 存储元素的数组 */
	Position Front, Rear;  /* 队列的头、尾指针 */
	int MaxSize;           /* 队列最大容量 */
};
typedef struct QNode *Queue;

Queue CreateQueue(int MaxSize)
{
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Data = (int *)malloc(MaxSize * sizeof(int));
	Q->Front = Q->Rear = 0;
	Q->MaxSize = MaxSize;
	return Q;
}

bool IsFull(Queue Q)
{
	return ((Q->Rear + 1) % Q->MaxSize == Q->Front);
}

bool AddQ(Queue Q, int X)
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

int DeleteQ(Queue Q)
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


int BuildTree(struct TreeNode T[]){
	int N, Root,i = -1;
	char cl, cr;
	int check[MaxTree];
	scanf("%d", &N);
	if (N)
	{
		for (i = 0; i < N; i++)
			check[i] = 0;
		for (i = 0; i < N; i++){
			scanf("\n%c %c", &cl, &cr);
			if (cl!='-')
			{
				T[i].left = cl - '0';
				check[T[i].left] = 1;
			}
			else
			{
				T[i].left = Null;
			}
			if (cr!='-')
			{
				T[i].right = cr - '0';
				check[T[i].right] = 1;
			}
			else
			{
				T[i].right = Null;
			}
		}
		for (i = 0; i < N; i++){
			if (!check[i])
				break;
		}
		Root = i;
	}
	return Root;
}

void PrintLeaves(Tree R){
	Tree tmp;
	Queue Q;
	Q = CreateQueue(MaxTree);
	AddQ(Q, R);
	int flag = 0;
	while (!IsEmpty(Q))
	{
		tmp = DeleteQ(Q);
		if ((T[tmp].left == Null) && (T[tmp].right == Null)){
			if (flag)
				printf(" ");
			printf("%d", tmp);
			flag = 1;
		}
			
		if (T[tmp].left != Null)
			AddQ(Q, T[tmp].left);
		if (T[tmp].right != Null)
			AddQ(Q, T[tmp].right);
	}
}

int main(){
	Tree R;

	R = BuildTree(T);
	if (R == Null)
		printf("%d", R);
	else
		PrintLeaves(R);

	return 0;
}