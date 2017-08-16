typedef int position;
struct SNode
{
	double *data;
	position top;
	int MaxSize;
};
typedef struct SNode *stack;

stack CreatStack(int MaxSize)
{
	stack s = (stack)malloc(sizeof(struct SNode));
	s->data = (double *)malloc(MaxSize*sizeof(double));
	s->top = -1;
	s->MaxSize = MaxSize;
	return s;
}

bool IsFull(stack s)
{
	return(s->MaxSize - 1 == s->top);
}

bool Push(stack s, double x)
{
	if (IsFull(s))
	{
		printf("¶ÑÕ»Âú");
		return false;
	}
	else
	{
		s->data[++(s->top)] = x;
		return true;
	}
}

bool IsEmpty(stack s)
{
	return (s->top == -1);	
}

double Pop(stack s)
{
	if (IsEmpty(s))
	{
		printf("¶ÑÕ»¿Õ");
		return false;
	}
	else
	{
		return (s->data[s->top--]);
	}
}