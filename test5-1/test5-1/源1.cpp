#include<stdio.h>
#define MAXN 1001
#define MINH -10001

int H[MAXN], size;

void Creat(){
	size = 0;
	H[0] = MINH;
}

void Insert(int x){
	int i;
	for (i = ++size; H[i / 2] > x; i = i / 2){
		H[i] = H[i / 2];//将大的值移动到子节点
	}
	H[i] = x;
}

int main(){
	int n, m, x, i, j;
	scanf("%d %d", &n, &m);
	Creat();
	for ( i = 0; i < n; i++)
	{
		scanf("%d", &x);
		Insert(x);
	}
	for (i = 0; i < m; i++){
		scanf("%d", &j);
		printf("%d", H[j]);
		while (j>1)
		{
			j = j / 2;
			printf(" %d", H[j]);
		}
		printf("\n");
	}
	return 0;
}