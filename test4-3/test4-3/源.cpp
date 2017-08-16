#include<stdio.h>

int pow(int a, int n){
	//aµÄn´Î·½
	int tmp=a;
	for (int i = 1; i < n; i++){
		tmp = tmp*a;
	}
	return tmp;
}

void get(int a[], int N,int res[]){
	int i,left,right;
	for (i = 1; i < 20; i++){
		left = pow(2, i) - 1;
		right = pow(2, i + 1) - 1;
		if (N >= left&&N < right){
			right = pow(2, i - 1) - 1;
			left = N - right - 1;
			break;
		}
	}
	res[0] = a[left];
	res[1] = left;
	res[2] = right;
//	return a[left];
}

int main()
{
	int N,i,j, min;
	int left, right;
	int a[1000];
	int res[3];
	scanf("%d", &N);
	for (i = 0; i < N; i++){
		scanf("%d", a + i);
	}
	for (i = 0; i < N; i++){
		min = a[i];
		for (j = i+1; j < N-1; j++){
			if (a[j] < min){
				a[i] = a[j];
				a[j] = min;
			}
		}
	}

	while (N>1){
		
	}

	get(a, N,res);
	printf("%d", res[0]);
	left = res[1];
	right = res[2];





	for (i = 1; i < 20; i++){
		left = pow(2, i) - 1;
		right = pow(2, i + 1) - 1;
		if (N >= left&&N < right){
			right = pow(2, i - 1) - 1;
			left = N - right - 1;
			break;
		}
	}
	a[left];
}