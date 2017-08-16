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
	int data[MAXSIZE];
	for (int i = 0; i < MAXSIZE; i++)
	{
		result[i] = 1;
	}
	int tmp = 0;
	int tmpPop = 0;
	Stack s = NULL;
	int i, j, ii,ij;
	int posi;
	//对每行遍历
	for (i_res = 0; i_res < k; i_res++)
	{
		for ( ij = 0; ij < n; ij++)
		{
			data[ij] = ij + 1;//存入堆栈的数据
		}

		s = CreateStack(m);
		
		for (i = 0; i < n; i++)
		{
			scanf("%d", test + i);//读入每一行
		}
		//根据第一个数建立堆栈
		for (i = 1; i <= test[0]; i++)
		{
			flag=Push(s, i);
		}
		posi = i-1;
		if (flag == false)
		{
			result[i_res] = 0;
			continue;
		}
		tmpPop = Pop(s);
		//测试后面的n-1个数
		for (i = 1; i <= n - 1; i++)
		{
			tmp = test[i];
			if (tmp > tmpPop)
			{
//				for (j = tmpPop + 1; j <= tmp; j++)
//				{
//					flag = Push(s, j);
//				}
				while (s->Data[s->Top] != tmp&&posi<n)
				{
					flag = Push(s, data[posi]);
					posi++;
				}

				tmpPop = Pop(s);
			}
			else
			{
				tmpPop = Pop(s);
				if (tmp==tmpPop)
				{
					tmpPop = Pop(s);
				}
				else
				{
					result[i_res] = 0;
					continue;
				}
			}

			if (flag == false)
			{
				result[i_res] = 0;
				continue;
			}

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


