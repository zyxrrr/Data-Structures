typedef int Position;
typedef struct LNode *List;
#define MAXSIZE 1000
struct LNode
{
	double Data[MAXSIZE];
	Position Last;
};

List MakeEmpty()
{
	List L;
	L = (List)malloc(sizeof(struct LNode));
	L->Last = -1;
	return L;
}

Position Find(List L, double X)
{
	
	Position i = 0;
	while (i<=L->Last&&L->Data[i]!=X)
	{
		i++;
	}
	if (i>L->Last)
	{
		return -1;
	}
	else
	{
		return i;
	}
}

bool Insert(List L, double X, Position P)
{
	Position i;
	
	if (L->Last==MAXSIZE-1)
	{
		printf("����");
		return false;
	}
	if (P<0||P>L->Last)
	{
		printf("λ�ò��Ϸ�");
		return false;
	}
	for (i = L->Last; i >= P; i--)
	{
		L->Data[i + 1] = L->Data[i];
	}
	L->Data[P] = X;
	L->Last++;
	return true;
}

bool Delete(List L, Position P)
{
	Position i;
	if (P<0||P>L->Last)
	{
		printf("λ��%d������Ԫ��", P);
		return false;
	}
	for (i = P + 1; i <= L->Last; i++)
	{
		L->Data[i - 1] = L->Data[i];
	}
	L->Last--;
	return true;
}