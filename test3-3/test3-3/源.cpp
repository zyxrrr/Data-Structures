#include<stdio.h>
#include<stdlib.h>
#define MaxSize 30
#pragma warning(disable:4996)
typedef struct TNode *position;
typedef position BinTree;
struct TNode{
	int Data;
	BinTree Left;
	BinTree Right;
};



typedef struct SNode *PtrToSNode;
struct SNode {
	int Data;
	PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreateStack()
{ /* ����һ����ջ��ͷ��㣬���ظý��ָ�� */
	Stack S;

	S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL;
	return S;
}

bool IsEmpty(Stack S)
{ /* �ж϶�ջS�Ƿ�Ϊ�գ����Ƿ���true�����򷵻�false */
	return (S->Next == NULL);
}

bool Push(Stack S, int X)
{ /* ��Ԫ��Xѹ���ջS */
	PtrToSNode TmpCell;

	TmpCell = (PtrToSNode)malloc(sizeof(struct SNode));
	TmpCell->Data = X;
	TmpCell->Next = S->Next;
	S->Next = TmpCell;
	return true;
}

int Pop(Stack S)
{ /* ɾ�������ض�ջS��ջ��Ԫ�� */
	PtrToSNode FirstCell;
	int TopElem;

	if (IsEmpty(S)) {
//		printf("��ջ��");
		return -1;
	}
	else {
		FirstCell = S->Next;
		TopElem = FirstCell->Data;
		S->Next = FirstCell->Next;
		free(FirstCell);
		return TopElem;
	}
}


void PostorderTraversal(BinTree BT)
{
	if (BT) {
		PostorderTraversal(BT->Left);
		PostorderTraversal(BT->Right);
		printf("%d ", BT->Data);
	}
}

void BuildTree(int PreOrder[],int InOrder[],Stack S,int N){
//	int N;
	int indexPush,indexPop,i,j;
	bool pushflag;
	indexPush = 1;
//	scanf("%d", &N);
	char buffer[MaxSize];
	for (i = 0; i < 2*N; i++){
		j = i / 2;
		scanf("\n%c%c", buffer, buffer + 1);
//		scanf("\n%c%c%c%c%c%c%c%c", buffer, buffer + 1, buffer + 2, buffer + 3, buffer + 4, buffer + 5,buffer+6,buffer+7);
		if (buffer[1] == 'u'){
//			indexPush = buffer[5] - '0';
			PreOrder[j] = indexPush;
			pushflag=Push(S, indexPush);
			indexPush++;
		}
		if (buffer[1]=='o')
		{
			indexPop = Pop(S);
			InOrder[j] = indexPop;
		}
	}
}

int main(){
	int Pre[MaxSize];
	int In[MaxSize];
	int N;
	Stack S = CreateStack();
	scanf("%d", &N);
	BuildTree(Pre, In,S,N);
	
	
	for (int i = 0; i < 6; i++){
		printf("%d", Pre[i]);
	}
}