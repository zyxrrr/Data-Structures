void Swap(int *p1, int *p2){
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void Bubble_Sort(int A[], int N){
	int flag;
	for (int i = N-1; i > 0; i--){
		flag = 0;
		for (int j = 0; j < i; j++){
			if (A[j]>A[j + 1]){
				Swap(&A[j], &A[j + 1]);
				flag = 1;
			}
				
		}
		if (!flag)
		{
			break;
		}
	}
}
/*
void Insertion_Sort(int A[], int N){
	for (int i = 1; i < N; i++)
	{
		for (int j = 0; j < i; j++){
			if (A[i] < A[j]){

			}
		}
	}
}
*/

void Insertion_Sort(int A[], int N){
	int i;
	for (int P = 1; P < N; P++){
		int tmp = A[P];
		for (i = P; i>0 && A[i - 1] > tmp; i--){
			A[i] = A[i - 1];
		}
		A[i] = tmp;
	}
}

void Shell_Sort(int A[], int N){
	int D, P,i;
	for (D = N / 2; D > 0; D = D / 2){
		for (P = D; P < N; P = P++){
			int tmp = A[P];
			for (i = P; i >= D&&A[i - D]>tmp; i = i - D){
				A[i] = A[i - D];
			}
			A[i] = tmp;
		}
	}
}

void PercDown(int A[], int p, int N){
	int parent, child, X;

	X = A[p];
	for (parent = p; (p * 2 + 1) < N; parent = child){
		child = parent * 2 + 1;
		if ((child != N - 1) && (A[child] < A[child + 1]))
			child++;

		if (X>A[child])
			break;
		else
			A[parent] = A[child];
	}
	A[parent] = X;
}

void Heap_Sort(int A[], int N){
	for (int i = N / 2 - 1; i >= 0; i--){
		PercDown(A, i, N);
	}

	for (int i = N - 1; i > 0; i--){
		Swap(&A[0], &A[i]);
		PercDown(A, 0, i);
	}
}

