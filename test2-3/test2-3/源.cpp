#include<stdio.h>
#define MAX_SIZE 100004
#pragma warning(disable:4996)
typedef struct tagLNode{
	int addr;      //�ڵ�λ��Address
	int data;      //Dataֵ
	int nextAddr;  //�¸��ڵ�λ��
	struct tagLNode *next;  //ָ���¸��ڵ��ָ��
} LNode;
/*
LNode *listReverse(LNode *head, int k);
��ת��������
����1���������ͷ�ڵ㣬
����2����ת������ĳ��ȣ�
����ֵ����ת�������ĵ�һ���ڵ�(����ͷ���)

*/
LNode *listReverse(LNode *head, int k);
//��������� ����Ϊ�������ͷ���
void printList(LNode *a);

int main()
{
	int firstAddr;
	int n = 0;            //�ڵ��� N
	int k = 0;            //��ת������ĳ���K
	int num = 0;          //������֮�������ڵ���
	int data[MAX_SIZE];   //��dataֵ �ڵ�λ����Ϊ����ֵ
	int next[MAX_SIZE];   //��nextֵ �ڵ�λ��Ϊ����
	int tmp;              //��ʱ�����������ʱ����

	scanf("%d %d %d", &firstAddr, &n, &k);
	LNode a[n + 1];                //�ܴ�n+1����������顣
	
	a[0].nextAddr = firstAddr;   //a[0] ��Ϊͷ�ڵ�
	//������Ľڵ�
	int i = 1;
	for (; i < n + 1; i++){
		scanf("%d", &tmp);
		scanf("%d %d", &data[tmp], &next[tmp]);
	}

	//����������
	i = 1;
	while (1){
		if (a[i - 1].nextAddr == -1){
			a[i - 1].next = NULL;
			num = i - 1;
			break;
		}
		a[i].addr = a[i - 1].nextAddr;
		a[i].data = data[a[i].addr];
		a[i].nextAddr = next[a[i].addr];
		a[i - 1].next = a + i;

		i++;
	}

	LNode *p = a;                    //pָ������ͷ���
	LNode *rp = NULL;                //��ת�������ķ���ֵ
	if (k <= num){

		for (i = 0; i < (num / k); i++){
			rp = listReverse(p, k);  //
			p->next = rp;            // ��һ��ִ�У�a[0]->next ָ���һ��������ת�ĵ�һ���ڵ�
			p->nextAddr = rp->addr;  // ����Nextֵ��ָ����ת��������һ���ڵ��λ��

			int j = 0;
			//ʹpָ����һ����Ҫ��ת���������ͷ��㣨��һ���ڵ��ǰһ���ڵ㣩
			while (j < k){
				p = p->next;
				j++;
			}

		}
	}

	printList(a);
}

LNode *listReverse(LNode *head, int k)
{
	int count = 1;
	LNode *new = head->next;
	LNode *old = new->next;
	LNode *tmp = NULL;

	while (count < k){
		tmp = old->next;
		old->next = new;
		old->nextAddr = new->addr;
		new = old;   //new�����һ���ڵ�
		old = tmp;   //tmp�����һ���ڵ�
		count++;
	}
	//ʹ��ת������һ���ڵ�ָ����һ��������ĵ�һ���ڵ�
	head->next->next = old;
	if (old != NULL){
		//�޸�Nextֵ��ʹ��ָ����һ���ڵ��λ��
		head->next->nextAddr = old->addr;
	}
	else{
		//���oldΪNULL,��û����һ����������ô��ת������һ���ڵ㼴�������������һ���ڵ�
		head->next->nextAddr = -1;
	}
	return new;
}

void printList(LNode *a)
{
	LNode *p = a;

	while (p->next != NULL){
		p = p->next;
		if (p->nextAddr != -1){
			//��ʽ�����%.5��ζ�����һ����������5λ�����ʱǰ�油0 �磺22�������00022
			printf("%.5d %d %.5d\n", p->addr, p->data, p->nextAddr);
		}
		else{
			//-1����Ҫ��%.5��ʽ���
			printf("%.5d %d %d\n", p->addr, p->data, p->nextAddr);
		}
	}

}