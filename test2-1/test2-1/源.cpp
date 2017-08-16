#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
	ElementType Data;
	PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print(List L); /* 细节在此不表；空链表将输出NULL */
List AddOneElement(List L,ElementType ele);
List Merge(List L1, List L2);


int main()
{
	List L1, L2, L;


	
	L1 = Read();
	L2 = Read();
	L = Merge(L1, L2);
	Print(L);
//	L1 = NULL;

	Print(L1);
	Print(L2);
	return 0;
	
}

/* 你的代码将被嵌在这里 */
List Read()
{
	int n;
	scanf("%d", &n);
	List L1;
	L1 = (PtrToNode)malloc(sizeof(struct Node));
	L1->Next = NULL;
	L1->Data = n;
	for (int i = 0; i < n; i++)
	{
		int ele;
		scanf("%d", &ele);
		L1=AddOneElement(L1, ele);
	}
	return L1;
}

List AddOneElement(List L, ElementType ele)
{
	PtrToNode tempCell;
	tempCell = (PtrToNode)malloc(sizeof(struct Node));
	if (L==NULL)
	{
		tempCell->Data = ele;
		tempCell->Next = NULL;
	}
	else
	{		
		tempCell->Data = ele;
		tempCell->Next = L;
	}
	return tempCell;
}

List Merge(List L1, List L2)
{
	List L;
	L = NULL;
	List point1,point2;
	ElementType temp1, temp2;
	point1 = L1;
	point2 = L2;
	while (point1->Next->Next != NULL)
		point1 = point1->Next;
	int n1 = point1->Next->Data;
	while (point2->Next->Next != NULL)
		point2 = point2->Next;
	int n2 = point2->Next->Data;
	free(point1->Next);
	free(point2->Next);
	point1->Next = NULL;
	point2->Next = NULL;
	PtrToNode p = L1;
	PtrToNode q = L2;
	while (p != NULL && q != NULL)
	{
		temp1 = p->Data;
		temp2 = q->Data;
		if (temp1==temp2)
		{
			L = AddOneElement(L, temp1);
			L = AddOneElement(L, temp2);
//			PtrToNode tmp = L1;
			p = p->Next;
//			free(tmp);
//			tmp = L2;
			q = q->Next;
//			free(tmp);
		}
		else if (temp1 > temp2)
		{
			L = AddOneElement(L, temp1);
//			PtrToNode tmp = L1;
			p = p->Next;
//			free(tmp);
		}
		else
		{
			L = AddOneElement(L, temp2);
//			PtrToNode tmp = L2;
			q = q->Next;
//			free(tmp);
		}
	}
	while (p)
	{
		temp1 = p->Data;
		L = AddOneElement(L, temp1);
		p = p->Next;
	}
	while (q)
	{
		temp2 = q->Data;
		L = AddOneElement(L, temp2);
		q = q->Next;
	}
	L1->Next = NULL;
	L2->Next = NULL;
	return L;
}

void Print(List L)
{
	if (L->Next==NULL)
	{
		printf("NULL\n");
	}
	else
	{
		while (L)
		{
			printf("%d ", L->Data);
			L = L->Next;
		}
		printf("\n");
	}
}