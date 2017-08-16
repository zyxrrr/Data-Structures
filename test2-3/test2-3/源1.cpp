#include<stdio.h>
#define MAX_SIZE 100004
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
struct tagLNode{
	int addr;
	int data;
	int nextAddr;
	struct tagLNode *next;
};
typedef struct tagLNode LNode;

LNode *listReverse(LNode *head, int k);
void printList(LNode *a);

int main()
{
	int firstAddr;
	int n = 0;
	int k = 0;
	int num = 0;
	int data[MAX_SIZE];
	int next[MAX_SIZE];
	int tmp;

	scanf("%d %d %d", &firstAddr, &n, &k);

	LNode *a = (LNode *)malloc(sizeof(struct tagLNode)* (n + 1));
	memset(a, 0x00, sizeof(struct tagLNode)* (n+1));

	//LNode a[7];
	//LNode b[6];
	
	a[0].nextAddr = firstAddr;

	int i = 1;
	for (; i < n + 1; i++)
	{
		scanf("%d", &tmp);
		scanf("%d %d", &data[tmp], &next[tmp]);
	}

	i = 1;
	while (true)
	{
		if (a[i-1].nextAddr==-1)
		{
			a[i - 1].next = NULL;
			num = i - 1;
			break;
		}
		a[i].addr = a[i - 1].nextAddr;
		a[i].data = data[a[i].addr];
		a[i].nextAddr = next[a[i].addr];
		a[i - 1].next = a + i;
		i++;
	}

	LNode *p = a;
	LNode *rp = NULL;
	if (k<=num)
	{
		for (i = 0; i < num / k; i++)
		{
			rp = listReverse(p, k);
			p->next = rp;
			p->nextAddr = rp->addr;

			int j = 0;
			while (j<k)
			{
				p = p->next;
				j++;
			}
		}
	}
	printList(a);
}

LNode *listReverse(LNode *head, int k)
{
	int count = 1;
	LNode *newL = head->next;
	LNode *old = newL->next;
	LNode *tmp = NULL;

	while (count<k)
	{
		tmp = old->next;
		old->next = newL;
		old->nextAddr = newL->addr;
		newL = old;
		old = tmp;
		count++;
	}

	//old->nextAddr=
	head->next->next = old;
	if (old!=NULL)
	{
		head->next->nextAddr = old->addr;
	}
	else
	{
		head->next->nextAddr = -1;
	}
	return newL;
}

void printList(LNode *a)
{
	LNode *p = a;
	while (p->next!=NULL)
	{
		p = p->next;
		if (p->nextAddr!=-1)
		{
			printf("%.5d %d %.5d\n", p->addr, p->data, p->nextAddr);
		}
		else
		{
			printf("%.5d %d %d\n", p->addr, p->data, p->nextAddr);
		}
	}
}