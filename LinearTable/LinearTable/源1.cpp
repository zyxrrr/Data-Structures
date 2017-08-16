typedef struct LNode *PtrToLNode;
struct LNode{
	double Data;
	PtrToLNode Next;
};
typedef PtrToLNode position;
typedef PtrToLNode list;

position Find(list L, double x)
{
	
	position p = L;
	while (p&&p->Data != x)
	{
		p = p->Next;
	}
	if (p)
	{
		return p;
	}
	else
	{
		return NULL;
	}
}

bool Insert(list L, double x, position p)
{
	position tmp, pre;
	for (pre = L; pre&&pre->Next != p; pre = pre->Next);
	
		if (pre == NULL)
		{
			printf("插入位置不正确");
			return false;
		}
		else
		{
			tmp = (position)malloc(sizeof(struct LNode));
			tmp->Data = x;
			tmp->Next = p;
			pre->Next = tmp;
			return true;
		}
	
}

bool Delete(list L, position p)
{
	position tmp, pre;

	for (pre = L; pre&&pre->Next != p; pre = pre->Next);
	if (pre == NULL || p == NULL)
	{
		printf("参数位置错误");
		return false;
	}
	else
	{
		pre->Next = p->Next;
		free(p);
		return true;
	}
}