#include <stdio.h>  
#include <math.h>  
#include <stdlib.h>  
typedef struct {
	double x, y;
	int pre;                //记录路径上该节点的前一个节点，初始化为-1  
	int escape;             //记录该节点能否直接跳上岸逃生  
}Vertex;
struct Node {
	int val;
	struct Node *next;
};
int inLake(double x, double y) {                //判断鳄鱼是否在湖里面；在岛上或岸上的鳄鱼不与任何节点相连  
	if (7.5 * 7.5 >= x * x + y * y)
		return 0;
	if (fabs(x) >= 50 || fabs(y) >= 50)
		return 0;
	return 1;
}
void createGraph(struct Node *table, Vertex *vertex, int n, int d) {
	for (int i = 1; i <= n; ++i) {               //将第一跳能跳到的节点链接到下标0，升序排序  
		if (inLake(vertex[i].x, vertex[i].y) && (d + 7.5)*(d + 7.5) >= vertex[i].x * vertex[i].x + vertex[i].y * vertex[i].y) {
			struct Node *p = (struct Node *)malloc(sizeof(struct Node));
			p->val = i;
			struct Node *pre = &table[0];       //寻找插入位置的前一个节点  
			while (pre->next && 
				vertex[i].x * vertex[i].x + vertex[i].y * vertex[i].y > vertex[pre->next->val].x * vertex[pre->next->val].x + vertex[pre->next->val].y * vertex[pre->next->val].y) {
				pre = pre->next;
			}
			p->next = pre->next;
			pre->next = p;
		}
	}
	for (int i = 1; i <= n; ++i) {               //将鳄鱼的节点连成网络  
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
	while (p = p->next) {                //以第一跳能跳到的节点为起始点广度优先搜索  
		//      int pace = 0;                   //深度，对应跳的次数  
		int v = p->val;                  //起始节点  
		int queue[101] = {}, head = 0, rear = 0;        //队列  
		int visited[101] = {};          //用于标记节点是否已访问  
		visited[v] = 1;
		queue[rear++] = v;              //第一个节点入队  
		vertex[v].pre = 0;              //起始节点的前一个节点为中心岛  
		while (rear - head) {           //队列不为空，循环  
			v = queue[head++];          //出队  
			if (vertex[v].escape) {     //如果当前节点能跳到岸上，返回逃跑成功  
				return v;
			}
			struct Node *q = &table[v]; //否则，将该节点所有没有被访问的邻节点都入队  
			while (q = q->next) {        //遍历每个邻接点  
				int u = q->val;
				if (!visited[u]) {      //如果该邻节点没有被访问，入队  
					visited[u] = 1;
					queue[rear++] = u;
					vertex[u].pre = v;  //记录当前入队节点的前一个节点  
				}
			}
		}
	}
	return 0;           //无法逃离  
}
void destroyGraph(struct Node* table, int n) {      //释放堆内空间  
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
	if (d >= 50 - 7.5) {                 //可以直接跳上岸  
		printf("1\n");
		return 0;
	}
	Vertex vertex[101];
	for (int i = 1; i <= n; ++i) {           //初始化节点信息，下标1开始分别对应每只鳄鱼，下标0对应中心小岛  
		scanf("%lf%lf", &vertex[i].x, &vertex[i].y);
		vertex[i].pre = -1;
		if (fabs(50 - fabs(vertex[i].x)) <= d || fabs(50 - fabs(vertex[i].y)) <= d)       //判断该节点能否直接跳上岸逃生  
			vertex[i].escape = 1;
		else
			vertex[i].escape = 0;
	}
	struct Node table[101] = {};            //邻接表形式储存图结构  
	createGraph(table, vertex, n, d);       //构造图  
	int escape = BFS(table, vertex, n, d);  //广度优先搜索图，返回逃跑成功的最后一个节点，不能逃跑返回0  
	if (escape) {                       //如果能逃生，回溯寻找路径  
		int pace = 1;
		int stack[100] = {}, top = 0;   //栈  
		int v = escape;
		while (v) {                     //回溯路径，依次压栈  
			++pace;
			stack[top++] = v;
			v = vertex[v].pre;
		}
		printf("%d\n", pace);
		while (top) {                   //依次弹出栈内元素  
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