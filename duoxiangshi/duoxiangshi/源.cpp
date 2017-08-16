#include<stdio.h>
#include<math.h>
#include<time.h>
#define MAXN 101
#define MAXK 1e7
clock_t start, stop;
double duration;

double f1(int n, double a[], double x)
{
	int i;
	double p = a[0];
	for (i = 1; i <= n; i++)
	{
		p += a[i] * pow(x, i);
	}
	return p;
}

double f2(int n, double a[], double x)
{
	int i;
	double p = a[n];
	for (i = n; i > 0; i--)
	{
		p = a[i - 1] + x*p;
	}
	return p;
}

void timecounter(double(*fun)(int n, double a[], double x), double a[])
{
	int i;
//	double a[MAXN];
//	a[0] = 1;
//	for (i = 1; i < MAXN; i++)
//	{
//		a[i] = (double)(1 / i);
//	}

	start = clock();
	for (i = 0; i < MAXK; i++)
	{
		(*fun)(MAXN - 1, a, 1.1);
	}
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
//	printf("ticks1=%f\n", (double)(stop - start));
//	printf("duration1=%6.2e\n", duration);
}




int main()
{
	int i;
	double a[MAXN];
	a[0] = 1;
	for (i = 1; i < MAXN; i++)
	{
		a[i] = (double)(1/i);
	}

/*	start = clock();
	for (i = 0; i < MAXK; i++)
	{
		f1(MAXN - 1, a, 1.1);
	}	
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;*/
	timecounter(f1, a);
	printf("ticks1=%f\n", (double)(stop - start));
	printf("duration1=%6.2e\n", duration);

/*	start = clock();
	for (i = 0; i < MAXK; i++)
	{
		f2(MAXN - 1, a, 1.1);
	}
//	f2(MAXN - 1, a, 1.1);
	stop = clock();*/
	timecounter(f2, a);
//	duration = ((double)(stop - start)) / CLK_TCK;
	printf("ticks1=%f\n", (double)(stop - start));
	printf("duration1=%6.2e\n", duration);
	return 0;
}