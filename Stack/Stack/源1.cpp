typedef struct SNode *PtrToSNode;
struct SNode{
	double data;
	PtrToSNode next;
};
typedef PtrToSNode stack;

stack CreatStack()
{
	stack s;

	s = (stack)malloc(sizeof(struct SNode));
	s->next = NULL;
	return s;
}

bool IsEmpty(stack s)
{
	return (s->next == NULL);
}

bool Push(stack s, double x)
{
	PtrToSNode tmpCell;

	tmpCell = (PtrToSNode)malloc(sizeof(struct SNode));
	tmpCell->data = x;
	tmpCell->next = s->next;
	s->next = tmpCell;
	return true;
}

double Pop(stack s)
{
	PtrToSNode firstCell;
	double topEle;

	if (IsEmpty(s))
	{
		printf("¶ÑÕ»¿Õ");
		return false;
	}
	else
	{
		firstCell = s->next;
		topEle = firstCell->data;
		s->next = firstCell->next;
		free(firstCell);
		return true;
	}
}