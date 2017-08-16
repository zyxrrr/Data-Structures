#include <stdio.h>  
#include <math.h>  
#include <stdlib.h>  
typedef struct {
	double x, y;
	int pre;                //��¼·���ϸýڵ��ǰһ���ڵ㣬��ʼ��Ϊ-1  
	int escape;             //��¼�ýڵ��ܷ�ֱ�����ϰ�����  
}Vertex;
struct Node {
	int val;
	struct Node *next;
};
int inLake(double x, double y) {                //�ж������Ƿ��ں����棻�ڵ��ϻ��ϵ����㲻���κνڵ�����  
	if (7.5 * 7.5 >= x * x + y * y)
		return 0;
	if (fabs(x) >= 50 || fabs(y) >= 50)
		return 0;
	return 1;
}
void createGraph(struct Node *table, Vertex *vertex, int n, int d) {
	for (int i = 1; i <= n; ++i) {               //����һ���������Ľڵ����ӵ��±�0����������  
		if (inLake(vertex[i].x, vertex[i].y) && (d + 7.5)*(d + 7.5) >= vertex[i].x * vertex[i].x + vertex[i].y * vertex[i].y) {
			struct Node *p = (struct Node *)malloc(sizeof(struct Node));
			p->val = i;
			struct Node *pre = &table[0];       //Ѱ�Ҳ���λ�õ�ǰһ���ڵ�  
			while (pre->next && 
				vertex[i].x * vertex[i].x + vertex[i].y * vertex[i].y > vertex[pre->next->val].x * vertex[pre->next->val].x + vertex[pre->next->val].y * vertex[pre->next->val].y) {
				pre = pre->next;
			}
			p->next = pre->next;
			pre->next = p;
		}
	}
	for (int i = 1; i <= n; ++i) {               //������Ľڵ���������  
		if (!inLake(vertex[i].x, vertex[i].y))
			continue;
		for (int j = 1; j <= n; ++j) {
			if (j != i && inLake(vertex[j].x, vertex[j].y) && 
				d * d >= (vertex[i].x - vertex[j].x)*(vertex[i].x - vertex[j].x) + (vertex[i].y - vertex[j].y) * (vertex[i].y - vertex[j].y)) {
				struct Node *p = (struct Node *)malloc(sizeof(struct Node));
				p->val = j;
				p->next = table[i].next;
				table[i].next = p;
			}
		}
	}
}
int BFS(struct Node *table, Vertex *vertex, int n, int d) {
	struct Node *p = &table[0];
	while (p = p->next) {                //�Ե�һ���������Ľڵ�Ϊ��ʼ������������  
		//      int pace = 0;                   //��ȣ���Ӧ���Ĵ���  
		int v = p->val;                  //��ʼ�ڵ�  
		int queue[101] = {}, head = 0, rear = 0;        //����  
		int visited[101] = {};          //���ڱ�ǽڵ��Ƿ��ѷ���  
		visited[v] = 1;
		queue[rear++] = v;              //��һ���ڵ����  
		vertex[v].pre = 0;              //��ʼ�ڵ��ǰһ���ڵ�Ϊ���ĵ�  
		while (rear - head) {           //���в�Ϊ�գ�ѭ��  
			v = queue[head++];          //����  
			if (vertex[v].escape) {     //�����ǰ�ڵ����������ϣ��������ܳɹ�  
				return v;
			}
			struct Node *q = &table[v]; //���򣬽��ýڵ�����û�б����ʵ��ڽڵ㶼���  
			while (q = q->next) {        //����ÿ���ڽӵ�  
				int u = q->val;
				if (!visited[u]) {      //������ڽڵ�û�б����ʣ����  
					visited[u] = 1;
					queue[rear++] = u;
					vertex[u].pre = v;  //��¼��ǰ��ӽڵ��ǰһ���ڵ�  
				}
			}
		}
	}
	return 0;           //�޷�����  
}
void destroyGraph(struct Node* table, int n) {      //�ͷŶ��ڿռ�  
	for (int i = 0; i <= n; ++i) {
		struct Node* p = table[i].next;
		while (p) {
			struct Node* tmp = p;
			p = p->next;
			free(tmp);
		}
	}
}
int main() {
	//  freopen("test.txt", "r", stdin);  
	int n;
	double d;
	scanf("%d%lf", &n, &d);
	if (d >= 50 - 7.5) {                 //����ֱ�����ϰ�  
		printf("1\n");
		return 0;
	}
	Vertex vertex[101];
	for (int i = 1; i <= n; ++i) {           //��ʼ���ڵ���Ϣ���±�1��ʼ�ֱ��Ӧÿֻ���㣬�±�0��Ӧ����С��  
		scanf("%lf%lf", &vertex[i].x, &vertex[i].y);
		vertex[i].pre = -1;
		if (fabs(50 - fabs(vertex[i].x)) <= d || fabs(50 - fabs(vertex[i].y)) <= d)       //�жϸýڵ��ܷ�ֱ�����ϰ�����  
			vertex[i].escape = 1;
		else
			vertex[i].escape = 0;
	}
	struct Node table[101] = {};            //�ڽӱ���ʽ����ͼ�ṹ  
	createGraph(table, vertex, n, d);       //����ͼ  
	int escape = BFS(table, vertex, n, d);  //�����������ͼ���������ܳɹ������һ���ڵ㣬�������ܷ���0  
	if (escape) {                       //���������������Ѱ��·��  
		int pace = 1;
		int stack[100] = {}, top = 0;   //ջ  
		int v = escape;
		while (v) {                     //����·��������ѹջ  
			++pace;
			stack[top++] = v;
			v = vertex[v].pre;
		}
		printf("%d\n", pace);
		while (top) {                   //���ε���ջ��Ԫ��  
			v = stack[--top];
			printf("%d %d\n", (int)vertex[v].x, (int)vertex[v].y);
		}
	}
	else {
		printf("0\n");
	}
	destroyGraph(table, n);

	return 0;
}