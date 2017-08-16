/*
#include<stdio.h>

int maxsubseqsum1(int a[], int N)
{
	int thisSum, maxSum = 0;
	int i, j, k;
	for (i = 0; i < N; i++)
	{
		for (j = i; j < N; j++)
		{
			thisSum = 0;
			for (k = i; k <= j; k++)
			{
				thisSum += a[k];
				if (thisSum>maxSum)
				{
					maxSum = thisSum;
				}
			}
		}
	}
	return maxSum;
}

int maxsubseqsum2(int a[], int N)
{
	int thisSum, maxSum = 0;
	int i, j;
	for (i = 0; i < N; i++)
	{
		thisSum = 0;
		for (j = i; j < N; j++)
		{
			thisSum += a[j];
			if (thisSum>maxSum)
			{
				maxSum = thisSum;
			}
		}
	}
	return maxSum;
}

int maxsubseqsum4(int a[], int N)
{
	int thisSum, maxSum=0;
	for (int i = 0; i < N; i++)
	{
		thisSum += a[i];
		if (thisSum>maxSum)
		{
			maxSum = thisSum;
		}
		else if (thisSum < 0)
		{
			thisSum = 0;
		}
	}
	return maxSum;
}

int maxsubseqsum3(int a[], int N)
{
	
}

int divideAndConquer(int list[], int left, int right)
{

}

int max3(int A, int B, int C)
	{
		int max;
		if (A > B)
		{
			max = A;
		}			
		else
		{
			max = B;
		}
		if (max < C)
			max = C;
		return max;
	}


	*/