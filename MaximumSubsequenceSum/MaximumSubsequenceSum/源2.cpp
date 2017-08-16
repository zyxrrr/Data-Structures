#include<stdio.h>
#pragma warning(disable:4996)

/*
int maxsubseqsum2(int a[], int N,int b[])
{
	int thisSum, maxSum = 0;
	int i, j;
	int first = 0;
	int last=N-1;
	for (i = 0; i < N; i++)
	{
		thisSum = 0;
		for (j = i; j < N; j++)
		{
			thisSum += a[j];
			if (thisSum>maxSum)
			{
				maxSum = thisSum;
				first = i;
				last = j;
			}
		}
		b[0] = first;
		b[1] = last;
	}
	return maxSum;
}

int main()
{
	int n, i;
	int res[2];
	scanf("%d", &n);
	int list[10000];
	for (i = 0; i < n; i++)
	{
		scanf("%d", &list[i]);
	}
	int max = maxsubseqsum2(list, n, res);
	printf("%d ", max);
	printf("%d ", res[0]);
	printf("%d\n", res[1]);
	}*/