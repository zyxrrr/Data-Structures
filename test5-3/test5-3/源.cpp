#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)
typedef struct TreeNode *HuffmanTree;
struct TreeNode{
	int weight;
	HuffmanTree left, right;
};



typedef int ElementType;
typedef struct HNode *Heap; /* �ѵ����Ͷ��� */
struct HNode {
	ElementType *Data; /* �洢Ԫ�ص����� */
	int Size;          /* ���е�ǰԪ�ظ��� */
	int Capacity;      /* �ѵ�������� */
};
typedef Heap MaxHeap; /* ���� */
typedef Heap MinHeap; /* ��С�� */

#define MAXDATA 1000  /* ��ֵӦ���ݾ����������Ϊ���ڶ������п���Ԫ�ص�ֵ */

MaxHeap CreateHeap(int MaxSize)
{ /* ��������ΪMaxSize�Ŀյ����� */

	MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
	H->Data = (ElementType *)malloc((MaxSize + 1)*sizeof(ElementType));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Data[0] = MAXDATA; /* ����"�ڱ�"Ϊ���ڶ������п���Ԫ�ص�ֵ*/

	return H;
}

bool IsFull(MaxHeap H)
{
	return (H->Size == H->Capacity);
}

bool Insert(MaxHeap H, ElementType X)
{ /* ��Ԫ��X��������H������H->Data[0]�Ѿ�����Ϊ�ڱ� */
	int i;

	if (IsFull(H)) {
		printf("��������");
		return false;
	}
	i = ++H->Size; /* iָ��������е����һ��Ԫ�ص�λ�� */
	for (; H->Data[i / 2] < X; i /= 2)
		H->Data[i] = H->Data[i / 2]; /* ����X */
	H->Data[i] = X; /* ��X���� */
	return true;
}

#define ERROR -1 /* �����ʶӦ���ݾ����������Ϊ���в����ܳ��ֵ�Ԫ��ֵ */

bool IsEmpty(MaxHeap H)
{
	return (H->Size == 0);
}

ElementType DeleteMax(MaxHeap H)
{ /* ������H��ȡ����ֵΪ����Ԫ�أ���ɾ��һ����� */
	int Parent, Child;
	ElementType MaxItem, X;

	if (IsEmpty(H)) {
		printf("������Ϊ��");
		return ERROR;
	}

	MaxItem = H->Data[1]; /* ȡ��������ŵ����ֵ */
	/* �����������һ��Ԫ�شӸ���㿪ʼ���Ϲ����²��� */
	X = H->Data[H->Size--]; /* ע�⵱ǰ�ѵĹ�ģҪ��С */
	for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;
		if ((Child != H->Size) && (H->Data[Child]<H->Data[Child + 1]))
			Child++;  /* Childָ�������ӽ��Ľϴ��� */
		if (X >= H->Data[Child]) break; /* �ҵ��˺���λ�� */
		else  /* ����X */
			H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = X;

	return MaxItem;
}

/*----------- �������� -----------*/
void PercDown(MaxHeap H, int p)
{ /* ���ˣ���H����H->Data[p]Ϊ�����Ӷѵ���Ϊ���� */
	int Parent, Child;
	ElementType X;

	X = H->Data[p]; /* ȡ��������ŵ�ֵ */
	for (Parent = p; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;
		if ((Child != H->Size) && (H->Data[Child]<H->Data[Child + 1]))
			Child++;  /* Childָ�������ӽ��Ľϴ��� */
		if (X >= H->Data[Child]) break; /* �ҵ��˺���λ�� */
		else  /* ����X */
			H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = X;
}

void BuildHeap(MaxHeap H)
{ /* ����H->Data[]�е�Ԫ�أ�ʹ�������ѵ�������  */
	/* �����������H->Size��Ԫ���Ѿ�����H->Data[]�� */

	int i;

	/* �����һ�����ĸ��ڵ㿪ʼ���������1 */
	for (i = H->Size / 2; i>0; i--)
		PercDown(H, i);
}


int computeLength(char code[], int fre[],int n){
	MaxHeap H;
	int i,j1,j2;
	HuffmanTree T;
	H = CreateHeap(n);
	for (i = 0; i < n; i++){
		Insert(H, -fre[i]);
	}
	int sum = 0;
	for (i = 1; i < H->Capacity; i++){
		T = (HuffmanTree)malloc(sizeof(struct TreeNode));
		j1 = DeleteMax(H);
		j2= DeleteMax(H);
		sum = sum + j1 + j2;
		T->weight = j1 + j2;
		Insert(H, T->weight);
	}
	
	return -sum;
}
int IsHuffma(int N,int fre[],int LenGet);
//HuffmanTree BuildT();
int main(){
	int Ncode, Nstu,i,wpl,res;
	int fre[63];//�����Ƶ��
	char code[63];//������ĸ

	scanf("%d", &Ncode);
	for (i = 0; i < Ncode; i++){
		getchar();
		scanf("%c", code + i);
		scanf("%d", fre + i);
	}
	wpl = computeLength(code, fre, Ncode);

	scanf("%d\n", &Nstu);
	for (i = 0; i < Nstu; i++){
		res = IsHuffma(Ncode, fre, wpl);
		if (res)
			printf("Yes\n");
		else
			printf("No\n");
	}


}

int IsHuffma(int N, int fre[], int LenGet){
	char stucode[70];
	int len[63];
	int CodeLen=0;
	int i,j,iii;
	HuffmanTree HTree = (HuffmanTree)malloc(sizeof(struct TreeNode));
	HuffmanTree tmp = NULL;
	HTree->weight = 0;//��ʾ����Ҷ�ӽڵ�
	HTree->left = NULL;
	HTree->right = NULL;
	for (iii = 0; iii < N; iii++){
		for (i = 0; i < 70; i++){
			//		getchar();
			scanf("%c", stucode + i);
			if (stucode[i] == '\n'){
				j = i;
				break;
			}
		}
		if (j>65){
			return 0;
		}
		else
		{
			len[iii] = j - 2;
		}
		CodeLen += len[iii] * fre[iii];
		
		if (iii == 0){
			for (i = 2; i<j; i++){
				if (i == j - 1)
				{
					//���һ��0��1
					if (stucode[i] == 1)
					{
						HuffmanTree H = (HuffmanTree)malloc(sizeof(struct TreeNode));
						H->left = NULL;
						H->right = NULL;
						H->weight = 1;
						tmp = HTree;
						while (tmp->right)
						{
							tmp = tmp->right;
						}
						tmp->right = H;
					}
					else
					{
						HuffmanTree H = (HuffmanTree)malloc(sizeof(struct TreeNode));
						H->left = NULL;
						H->right = NULL;
						H->weight = 1;
						tmp = HTree;
						while (tmp->left)
						{
							tmp = tmp->left;
						}
						tmp->left = H;
					}
				}
				else
				{
					if (stucode[i] == 1)
					{
						HuffmanTree H = (HuffmanTree)malloc(sizeof(struct TreeNode));
						H->left = NULL;
						H->right = NULL;

						H->weight = 0;
						tmp = HTree;
						while (tmp->right)
						{
							tmp = tmp->right;
						}
						tmp->right = H;
					}
					else
					{
						HuffmanTree H = (HuffmanTree)malloc(sizeof(struct TreeNode));
						H->left = NULL;
						H->right = NULL;
						H->weight = 0;
						tmp = HTree;
						while (tmp->left)
						{
							tmp = tmp->left;
						}
						tmp->left = H;
					}
				}
				
			}
		}
		else
		{
			tmp = HTree;
			for (i = 2; i < j; i++)
			{
				
				if (stucode[i] == 1)
				{
					if (tmp->right)
					{
						tmp = tmp->right;
						if (tmp->weight == 1)
							return 0;
						if (i == j - 1)
						{
							if (tmp->left || tmp->right)
								return 0;
						}
					}
					else
					{
						HuffmanTree Htmp = (HuffmanTree)malloc(sizeof(struct TreeNode));
						Htmp->left = NULL;
						Htmp->right = NULL;
						if (i == j - 1)
						{
							Htmp->weight = 1;
						}
						else
						{
							Htmp->weight = 0;
							tmp->right = Htmp;
							tmp = Htmp;
						}

					}
				}
				else
				{
					if (tmp->left)
					{
						tmp = tmp->left;
						if (tmp->weight == 1)
							return 0;
						if (i == j - 1)
						{
							if (tmp->left  || tmp->right )
								return 0;
						}
					}
					else
					{
						HuffmanTree Htmp = (HuffmanTree)malloc(sizeof(struct TreeNode));
						Htmp->left = NULL;
						Htmp->right = NULL;
						if (i == j - 1)
						{
							Htmp->weight = 1;
						}
						else
						{
							Htmp->weight = 0;
							tmp->left = Htmp;
							tmp = Htmp;
						}

					}
				}
			}
			
		}

	}
	if (CodeLen != LenGet){
		return 0;
	}
	
	return 1;
}
