#include<stdio.h>
#pragma warning(disable:4996)
//test---branch----------------------------
/*
The Maximum Subsequence is the continuous subsequence which has the largest sum of its elements. For example, given sequence { -2, 11, -4, 13, -5, -2 }, its maximum subsequence is { 11, -4, 13 } with the largest sum being 20.

Now you are supposed to find the largest sum, together with the first and the last numbers of the maximum subsequence.

Input Specification:

Each input file contains one test case. Each case occupies two lines. The first line contains a positive integer KK (\le 10000≤10000). The second line contains KK numbers, separated by a space.

Output Specification:

For each test case, output in one line the largest sum, together with the first and the last numbers of the maximum subsequence. The numbers must be separated by one space, but there must be no extra space at the end of a line. In case that the maximum subsequence is not unique, output the one with the smallest indices ii and jj (as shown by the sample case). If all the KK numbers are negative, then its maximum sum is defined to be 0, and you are supposed to output the first and the last numbers of the whole sequence.
*/

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
