#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
typedef struct PolyNode *Polynomial;
struct PolyNode{
	int coef;
	int expon;
	Polynomial link;
};

void Attach(int c, int e, Polynomial *pRear)
{
	Polynomial P;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->coef = c;
	P->expon = e;
	P->link = NULL;
	(*pRear)->link = P;
	*pRear = P;
}

Polynomial ReadPoly()
{
	Polynomial P, Rear, t;
	int c, e, N;
	scanf("%d", &N);
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;
	Rear = P;
	while (N--)
	{
		scanf("%d%d", &c, &e);
		Attach(c, e, &Rear);
	}
	t = P;
	P = P->link;
	free(t);
	return P;
}



Polynomial Add(Polynomial P1, Polynomial P2)
{
	int tmpcoef, tmpexpon;
	Polynomial t1, t2,P,Rear,tmp;
	t1 = P1;
	t2 = P2;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;
	Rear = P;
	while (t1&&t2)
	{
		if (t1->expon==t2->expon)
		{
			tmpcoef = t1->coef + t2->coef;
			tmpexpon = t1->expon;
			if (tmpcoef==0)
			{

			}
			else
			{
				Attach(tmpcoef, tmpexpon, &Rear);
			}
			
			t1 = t1->link;
			t2 = t2->link;
		}
		else if (t1->expon > t2->expon)
		{
			tmpcoef = t1->coef;
			tmpexpon = t1->expon;
			if (tmpcoef!=0)
			{
				Attach(tmpcoef, tmpexpon, &Rear);
			}
			
			t1 = t1->link;
		}
		else
		{
			tmpcoef = t2->coef;
			tmpexpon = t2->expon;
			if (tmpcoef!=0)
			{
				Attach(tmpcoef, tmpexpon, &Rear);
			}
			
			t2 = t2->link;
		}
	}
	if (t1)
	{
		Rear->link = t1;
	}
	if (t2)
	{
		Rear->link = t2;
	}
	tmp = P;
	P = P->link;
	free(tmp);
	return P;
}

void PrintPoly(Polynomial P)
{
	int flag = 0;
	if (!P)
	{
		printf("0 0\n");
		return;
	}
	while (P)
	{
		if (P->link)
		{
			printf("%d %d ", P->coef, P->expon);
			P = P->link;
		}
		else
		{
			printf("%d %d", P->coef, P->expon);
			P = P->link;
		}
		
	}
	printf("\n");
}

Polynomial Mult(Polynomial P1, Polynomial P2)
{
	Polynomial t1, t2, P, Rear,Sum,tmp;
	Sum = NULL;
	t1 = P1;
	t2 = P2;
	
	while (t1)
	{
			P = (Polynomial)malloc(sizeof(struct PolyNode));
			P->link = NULL;
			Rear = P;
			t2 = P2;
		while (t2)
		{	
			if (t1->coef*t2->coef)
			{
				Attach(t1->coef*t2->coef, t1->expon + t2->expon, &Rear);
			}
			
			t2 = t2->link;
		}
			tmp = P;
			P = P->link;			
			free(tmp);
			Sum = Add(Sum, P);
		t1 = t1->link;
	}
	return Sum;
}

int main()
{
	Polynomial P1, P2, PP, PS;
	P1 = ReadPoly();
	P2 = ReadPoly();
	PP = Mult(P1, P2);
	PrintPoly(PP);
	PS = Add(P1, P2);
	PrintPoly(PS);
	return 0;
}