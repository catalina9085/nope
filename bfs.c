//graf de acoperire minima Kruskal
#include <stdio.h>
#include <stdint.h>
#define MAX 100
int arbore[100][100];
int n;
int visited[MAX];
int predecesor[MAX];
typedef struct {
	int data[MAX];
	int front, rear;
}Q;

void initQueue(Q* q) {
	q->rear = q->front = -1;
}
int isEmpty(Q* q) {
	return q->front == -1;
}

int isFull(Q* q) {
	return q->rear == MAX - 1;
}

void enqueue(Q* q, int val) {
	if (isFull(q))
		return;
	if (isEmpty(q))
		q->front = q->rear = 0;
	else q->rear++;
	q->data[q->rear] = val;
}

int dequeue(Q* q) {
	if (isEmpty(q))
		return -1;
	int val = q->data[q->front];
	if (q->front == q->rear)
		q->front = q->rear = -1;
	else
		q->front++;
	return val;
}

void citireArbore() {
	FILE* f = fopen("in4.txt", "r");
	if (!f) exit(-1);

	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			fscanf(f, "%d", &arbore[i][j]);
	for (int i = 0;i < n;i++) visited[i] = 0;
}

void afisareArbore() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%d ", arbore[i][j]);
		printf("\n");
	}
}
//nerecursiv
void bfs(int start) {
	for (int i = 0;i < n;i++) {
		visited[i] = 0;
	}
	Q q;
	initQueue(&q);
	enqueue(&q, start);
	visited[start] = 1;
	while (!isEmpty(&q)) {
		int curent = dequeue(&q);
		printf("%d ", curent);
		for (int i = 0;i < n;i++) {
			if (!visited[i] && arbore[curent][i] == 1) {
				visited[i] = 1;
				enqueue(&q, i);
			}
		}
	}
}

int main()
{
	citireArbore();
	bfs(0);
	return 0;
}

