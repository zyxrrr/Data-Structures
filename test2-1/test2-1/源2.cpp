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

List Read(); /* ϸ���ڴ˲���     ��Ҳ����˵�ύ��ʱ����Բ����ǣ���������Ҫд�ģ���    */
void Print(List L); /* ϸ���ڴ˲������������NULL   ��ͬ�ϣ�*/

List Merge(List L1, List L2);

int main()
{
	List L1, L2, L;
	L1 = Read();
	L2 = Read();
	L = Merge(L1, L2);
	Print(L);
	Print(L1);
	Print(L2);
	return 0;
}

/* ��Ĵ��뽫��Ƕ������ */
List Read()
{
	int n;
	scanf("%d", &n);
	List L = (List)malloc(sizeof(PtrToNode));   ///����һ��ͷ���  
	L->Next = NULL;        ///ͷָ��Ϊ��  
	if (n)    ///��n����0ʱ  
	{
		List r = L;     ///r��һ���м�����Ľڵ�  
		for (int i = 0; i<n; i++)
		{
			List p = (List)malloc(sizeof(struct Node));
			scanf("%d", &(p->Data));    ///β�巨  
			r->Next = p;
			r = p;
		}
		r->Next = NULL;
	}
	return L;
}

void Print(List L)
{
	List p = L->Next;
	if (p)
	{
		List r;
		r = L;
		while (r->Next)
		{
			r = r->Next;
			printf("%d ", r->Data);
		}
	}
	else
	{
		printf("NULL");
	}
	printf("\n");
}

List Merge(List L1, List L2)   ///�ϲ�����  �ص�Ҫд�ĺ�����  
{
	List pa, pb, pc, L;
	L = (List)malloc(sizeof(struct Node));
	pa = L1->Next;
	pb = L2->Next;
	pc = L;
	while (pa && pb)
	{
		if (pa->Data <= pb->Data)
		{
			pc->Next = pa;
			pc = pa;
			pa = pa->Next;
		}
		else
		{
			pc->Next = pb;
			pc = pb;
			pb = pb->Next;
		}
	}
	pc->Next = pa ? pa : pb;
	L1->Next = NULL;
	L2->Next = NULL;
	return L;
}