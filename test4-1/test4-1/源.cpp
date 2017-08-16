#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct AVLNode *Position;
typedef Position AVLTree;
struct AVLNode
{
	int Data;
	AVLTree Left;
	AVLTree Right;
	int Height;
};

int Max(int a, int b){
	return a > b ? a : b;
}

int GetHight(AVLTree A){
	if (!A)
	{
		return -1;
	}
	else
	{
		if (A->Left == NULL&&A->Right == NULL)
			return 0;
		else
		{
			return 1 + Max(GetHight(A->Left), GetHight(A->Right));
		}
	}
	

}

/*
int GetHight(AVLTree A){
	if (!A)
		return -1;
	if (A->Left || A->Right)
		return 1 + Max(GetHight(A->Left), GetHight(A->Right));
	if (A->Left == NULL&&A->Right == NULL)
		return 0;
}*/

AVLTree SingleLeftRotation(AVLTree A){
	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	A->Height = Max(GetHight(A->Left), GetHight(A->Right)) + 1;
	B->Height = Max(GetHight(B->Left), A->Height) + 1;
	return B;

}

AVLTree SingleRightRotation(AVLTree A){
	AVLTree B = A->Right;
	A->Right = B->Left;
	B->Left = A;
	A->Height = Max(GetHight(A->Left), GetHight(A->Right)) + 1;
	B->Height = Max(GetHight(B->Right), A->Height) + 1;
	return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A){
	A->Left = SingleRightRotation(A->Left);
	return SingleLeftRotation(A);
}

AVLTree DobleRightLeftRotation(AVLTree A){
	A->Right = SingleLeftRotation(A->Right);
	return SingleRightRotation(A);
}



AVLTree Insert(AVLTree T, int X){
	if (!T){
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->Data = X;
		T->Height = 0;
		T->Left = T->Right = NULL;
	}
	else if (X<T->Data)
	{
		T->Left = Insert(T->Left, X);
		if (GetHight(T->Left) - GetHight(T->Right) == 2)
		{
			if (X < T->Left->Data)
				T = SingleLeftRotation(T);
			else
				T = DoubleLeftRightRotation(T);
		}
	}
	else if (X>T->Data)
	{
		T->Right = Insert(T->Right, X);
		if (GetHight(T->Left) - GetHight(T->Right) == -2){
			if (X < T->Right->Data)
				T = DobleRightLeftRotation(T);
			else
				T = SingleRightRotation(T);
		}
	}
	T->Height = Max(GetHight(T->Left), GetHight(T->Right)) + 1;
	return T;
}





/*
bool TestTwoAVLTree(AVLTree tested, AVLTree T)
{
	if (T == NULL&&tested == NULL)
		return true;
	if (T->Data != tested->Data)
		return false;
	else if (T->Left == NULL&&tested->Left == NULL&&T->Right == NULL&&tested->Right == NULL)
		return true;
	else
		return (TestTwoAVLTree(T->Left, tested->Left) && TestTwoAVLTree(T->Right, tested->Right));
}*/


int main()
{
	int N, i, tmp_in;
//	int InsertSque[10];
	AVLTree T = NULL;
	scanf("%d", &N);
	for (i = 0; i < N; i++){
		scanf("%d", &tmp_in);
		T=Insert(T, tmp_in);
	}
	printf("%d", T->Data);

	return 0;

	/*
	while (1)
	{
		scanf("%d", &N);
		if (!N)
			break;
		scanf("%d", &L);
		for (j = 0; j < L+1; j++){
//			free(T);
			T = NULL;
			for (i = 0; i < N; i++){
				scanf("%d", InsertSque + i);
				T = Insert(T, InsertSque[i]);
			}
			if (j == 0)
				tested = T;
			else
			{
				//½øÐÐ²âÊÔtested,T
				flag=TestTwoAVLTree(tested, T);
				if (flag)
					printf("Yes\n");
				else
					printf("No\n");
				

				
			}
		}
		
	}
	


	return 0;*/
}