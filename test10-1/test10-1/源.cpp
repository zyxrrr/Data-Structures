#include<stdio.h>

void swap(int *p1, int *p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

int Median3(int A[], int left, int right){
	int center = (left + right) / 2;
	if (A[left] > A[center])
		swap(&A[left], &A[center]);
	if (A[left] > A[right])
		swap(&A[left], &A[right]);
	if (A[center] > A[right])
		swap(&A[center], &A[right]);
	return A[right - 1];
}

void Qsort(int A[], int left, int right){
	int pivot,  low, high;

	//if (cutoff<)
	pivot = Median3(A, left, right);
	low = left;
	high = right - 1;
	while (true)
	{
		while (A[++low] < pivot);
		while (A[--high]>pivot);
		if (low < high)
			swap(&A[low], &A[high]);
		else
			break;

	}
	swap(&A[low], &A[high]);
	Qsort(A, left, low - 1);
	Qsort(A, low + 1, right);
}

void QuickSort(int A[], int N){
	Qsort(A, 0, N - 1);
}

int main(){
	int A[] = { 1, 2, 3, 4 ,732,21,89534,237,348,2,56,342,634,1,4554,23};
	swap(&A[0], &A[2]);
//	QuickSort(A, 6);
	for (int i = 0; i < 10; i++){
		printf("%d\n", A[i]);
	}
}