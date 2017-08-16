typedef struct Node *PtrToNode;
struct Node
{
	double data;
	PtrToNode next;
};
typedef PtrToNode position;
struct QNode
{
	position front, rear;
	int Maxsize;
};
typedef struct QNode *Queue;

Queue CreatQueue(int MaxSize)
{

}

bool IsEmpty(Queue q)
{
	return(q->front == NULL);
}

double Delete(Queue q)
{
	position frontCell;
	double frontElem;
	if (IsEmpty(q))
	{
		printf("╤сап©у");
		return ERROR;
	}
	else
	{
		frontCell = q->front;
		if (q->front==q->rear)
		{
			q->front = q->rear = NULL;
		}
		else
		{
			q->front = q->front->next;
		}
		frontElem = frontCell->data;
		free(frontCell);
		return frontElem;
	}
}
