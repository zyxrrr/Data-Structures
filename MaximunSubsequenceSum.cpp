#include<stdio.h>
#pragma warning(disable:4996)

int maxSub(int a[], int N,int b[])
{
	int i;
	int thisSum = 0;
	int maxSum=0;
	int first = 0;
	int last=N-1;
	int first_pre;
	int flag = 0;

	for (i = 0; i < N; i++)
	{
		
		thisSum += a[i];
		if (thisSum>maxSum)
		{
			maxSum = thisSum;
			last = i;
			if (flag == 1)
			{
				first = first_pre;
				flag = 0;
			}
		}
		if (thisSum == 0)
		{
			if (flag==1)
			{

			}
		}

		if (thisSum < 0)
		{
			thisSum = 0;
			first_pre = i + 1;
			flag = 1;
		}
	}
	b[0] = a[first];
	b[1] = a[last];

	return maxSum;
}

int maxSubseq(int a[],int N, int b[])
{
	int result=a[0];
	int thisSum = a[0];
	int i;
	int begin=0, last=0, first=0;
	for (i = 1; i < N; i++)
	{
		if (thisSum >= 0)
		{
			thisSum += a[i];
		}			
		else
		{
			thisSum = a[i];
			begin = i;
		}
		if (thisSum > result)
		{
			last = i;
			first = begin;
			result = thisSum;
		}
	}
	if (result < 0)
	{
		result = 0;
		first = 0;
		last = N - 1;
	}
	b[0] = a[first];
	b[1] = a[last];
	return result;
}

int main()
{
	int n,i;
	int res[2];
	scanf("%d",&n);
	int list[10000];
	for ( i = 0; i < n; i++)
	{		
			scanf("%d", &list[i]);
	}
	int max = maxSubseq(list, n,res);
	printf("%d ", max);
	printf("%d ", res[0]);
	printf("%d\n", res[1]);
}
