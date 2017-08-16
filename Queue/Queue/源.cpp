typedef int position;
struct QNode{
	double *data;
	position front, rear;
	int MaxSize;
};
typedef struct QNode *Queue;

Queue CreateQueue(int MaxSize){
	Queue q = (Queue)malloc(sizeof(struct QNode));
	q->data = (double *)malloc(MaxSize*sizeof(double));
	q->front = q->rear = 0;
	q->MaxSize = MaxSize;
	return q;
}

bool IsFull(Queue q)
{
	return(q->front == (q->rear+1)%q->MaxSize);
}

bool IsEmpty(Queue q)
{
	return(q->front == q->rear);
}

bool addQ(Queue q, double x)
{
	if (IsFull)
	{
		printf("队列满");
		return false;
	}
	else
	{
		q->rear = (q->rear + 1) % q->MaxSize;
		q->data[q->rear] = x;
		return true;
	}
}

double Delete(Queue q)
{
	if (IsEmpty(q))
	{
		printf("队列空");
		return false;
	}
	else
	{
		q->front = (q->front + 1) % q->MaxSize;
		return q->data[q->front];
	}
}