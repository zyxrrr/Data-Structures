#include <stdio.h>  
#include <stdlib.h>  
#define MaxSize 1000  
#pragma warning(disable:4996)
typedef struct StackRecord{
	int capacity;
	int top;
	int data[MaxSize];
}*Stack;
Stack CreateStack(int capacity) {
	Stack S = (Stack)malloc(sizeof(struct StackRecord));
	S->top = -1;
	S->capacity = capacity;
	return S;
}
int Push(Stack S, int x) {  //将x元素入栈，如果溢出则入栈失败返回0  
	if (S->capacity - S->top <= 1)
		return 0;
	S->data[++S->top] = x;
	return 1;
}
int Top(Stack S) {  //返回栈顶元素，空栈时返回-1  
	if (S->top >= 0)
		return S->data[S->top];
	else
		return -1;
}
void Pop(Stack S) { //弹出栈顶元素  
	S->top--;
}
void DisposeStack(Stack S) {
	free(S);
}
//模拟进栈出栈过程：依次入栈并同时与出栈序列的第一个元素对比；若相等则弹出栈顶元素，并消去出栈序列的首元素；  
//全部已入栈后出栈序列中的元素全部被消去则返回1，否则返回0；  
int IsPopSeq(int* popOrder, int capacity, int n) {
	Stack S = CreateStack(capacity);
	int head = 0;       //维护一个下标，指向出栈序列中还没被消去的第一个元素  
	for (int node = 1; node <= n; node++) {   //入栈节点从1到k  
		if (!Push(S, node)){     //如果入栈失败表示栈满，则返回0  
			DisposeStack(S);
			return 0;
		}
		while (Top(S) == popOrder[head]) {
			Pop(S);
			head++;
		}
	}
	DisposeStack(S);
	if (head != n)       //出栈序列不为空，则返回0  
		return 0;
	return 1;
}
int main() {
	int m, n, k;
	scanf("%d%d%d", &m, &n, &k);
	int popOrder[1000];
	int res[1000];
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++)
			scanf("%d", &popOrder[j]);
		if (IsPopSeq(popOrder, m, n))//模拟将1，2，3...N一个一个压入堆栈，当栈顶与出栈序列相同时消去（全部）
			res[i] = 1;
		//			printf("YES\n");
		else
			res[i] = 0;
//			printf("NO\n");
	}

	for (int i = 0; i < k; i++)
	{
		if (res[i]==1)
			printf("YES\n");
		else
			printf("NO\n");
	}

	return 0;
}