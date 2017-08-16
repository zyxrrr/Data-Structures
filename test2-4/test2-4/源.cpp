#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define MAXSIZE 1000
#define ERROR - 1;
typedef int Position;
struct SNode {
	int *Data; /* 存储元素的数组 */
	Position Top;      /* 栈顶指针 */
	int MaxSize;       /* 堆栈最大容量 */
};
typedef struct SNode *Stack;


Stack CreateStack(int MaxSize)
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
//	SNode *S = (SNode *)malloc(sizeof(struct SNode));
	S->Data = (int *)malloc(MaxSize * sizeof(int));
	S->Top = -1;
	S->MaxSize = MaxSize;
	return S;
}

bool IsFull(Stack S)
{
	return (S->Top == S->MaxSize - 1);
}

bool Push(Stack S, int X)
{
	if (IsFull(S)) {
//		printf("堆栈满");
		return false;
	}
	else {
		S->Data[++(S->Top)] = X;
		return true;
	}
}

bool IsEmpty(Stack S)
{
	return (S->Top == -1);
}

int Pop(Stack S)
{
	if (IsEmpty(S)) {
//		printf("堆栈空");
		return ERROR; /* ERROR是ElementType的特殊值，标志错误 */
	}
	else
		return (S->Data[(S->Top)--]);
}


int main()
{
	int m, n, k = 0;
	int i_res;
	bool flag;
	scanf("%d %d %d", &m, &n, &k);
//	int a[MAXSIZE];
	int test[MAXSIZE];
	int result[MAXSIZE];
	for (int i = 0; i < MAXSIZE; i++)
	{
		result[i] = 1;
	}
	int tmp = 0;
	int tmpPop = 0;
	Stack s = NULL;

	//对每行遍历
	for (i_res = 0; i_res < k;i_res++)
	{
		s = CreateStack(m);
		int i,j,ii;
		for (i = 0; i < n; i++)
		{
			scanf("%d", test+i);//读入每一行
		}
		tmp = test[0];
		for (j = 1; j <= tmp; j++)
		{
			flag = Push(s, j);
			if (flag == false)
			{
				result[i_res] = 0;
				continue;
			}
		}
		if (result[i_res] == 0)
			continue;

		tmpPop=Pop(s);

		for (j = 1; j <= n; j++)
		{
			tmp = test[j];
			if (tmp > tmpPop)
			{
				for (ii = tmpPop + 1; ii <= tmp; ii++)
				{
					flag = Push(s, ii);
					if (flag == false)
					{
						result[i_res] = 0;
						continue;
					}
				}
				tmpPop=Pop(s);
			}
			else 
			{
				tmpPop = Pop(s);
				if (tmpPop!=tmp)
				{
					result[i_res] = 0;
					continue;
				}
				
			}
			if (result[i_res] == 0)
				continue;
		}
		
		
	}

	for (int i = 0; i < k; i++)
	{
		if (result[i] == 0)
			printf("NO\n");
		else
			printf("YES\n");
	}
}


