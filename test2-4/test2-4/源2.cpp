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
int Push(Stack S, int x) {  //��xԪ����ջ������������ջʧ�ܷ���0  
	if (S->capacity - S->top <= 1)
		return 0;
	S->data[++S->top] = x;
	return 1;
}
int Top(Stack S) {  //����ջ��Ԫ�أ���ջʱ����-1  
	if (S->top >= 0)
		return S->data[S->top];
	else
		return -1;
}
void Pop(Stack S) { //����ջ��Ԫ��  
	S->top--;
}
void DisposeStack(Stack S) {
	free(S);
}
//ģ���ջ��ջ���̣�������ջ��ͬʱ���ջ���еĵ�һ��Ԫ�ضԱȣ�������򵯳�ջ��Ԫ�أ�����ȥ��ջ���е���Ԫ�أ�  
//ȫ������ջ���ջ�����е�Ԫ��ȫ������ȥ�򷵻�1�����򷵻�0��  
int IsPopSeq(int* popOrder, int capacity, int n) {
	Stack S = CreateStack(capacity);
	int head = 0;       //ά��һ���±ָ꣬���ջ�����л�û����ȥ�ĵ�һ��Ԫ��  
	for (int node = 1; node <= n; node++) {   //��ջ�ڵ��1��k  
		if (!Push(S, node)){     //�����ջʧ�ܱ�ʾջ�����򷵻�0  
			DisposeStack(S);
			return 0;
		}
		while (Top(S) == popOrder[head]) {
			Pop(S);
			head++;
		}
	}
	DisposeStack(S);
	if (head != n)       //��ջ���в�Ϊ�գ��򷵻�0  
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
		if (IsPopSeq(popOrder, m, n))//ģ�⽫1��2��3...Nһ��һ��ѹ���ջ����ջ�����ջ������ͬʱ��ȥ��ȫ����
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