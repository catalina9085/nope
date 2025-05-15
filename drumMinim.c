
//in graf neorientat,neponderat,se foloseste de bfs
#include <stdio.h>
#include <stdint.h>

#define MAX 100
int arbore[100][100];
int visited[MAX];
int predecesor[MAX];
int n;

typedef struct {
    int data[MAX];
    int front;
    int rear;
} Queue;

void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}


int isEmpty(Queue* q) {
    return q->front == -1;
}


int isFull(Queue* q) {
    return q->rear == MAX - 1;
}


void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Coada este plina!\n");
        return;
    }

    if (isEmpty(q)) {
        q->front = q->rear = 0;
    }
    else {
        q->rear++;
    }

    q->data[q->rear] = value;
    //printf("Elementul %d a fost adaugat in coada.\n", value);
}


int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Coada este goala!\n");
        return -1;
    }

    int value = q->data[q->front];

    if (q->front == q->rear) {
        q->front = q->rear = -1;
    }
    else {
        q->front++;
    }

    return value;
}


void citireArbore() {
    FILE* f = fopen("in.txt", "r");
    if (!f) exit(-1);

    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(f, "%d", &arbore[i][j]);
}

void afisareArbore() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", arbore[i][j]);
        printf("\n");
    }
}

void pc(int start,int dest) {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        predecesor[i] = -1;
    }
    Queue q;
    initQueue(&q);
    enqueue(&q, start);
    visited[start] = 1;
    while (!isEmpty(&q)) {
        int nod = dequeue(&q);
        if (nod == dest) break;
        for (int i = 0; i < n; i++) {
            //printf("suntem la %d,avem legatura %d\n", i, arbore[nod][i]);
            if (!visited[i] && arbore[nod][i] == 1) {
                visited[i] = 1;
                enqueue(&q, i);
                predecesor[i] = nod;
            }
        }
    }
    if (!visited[dest]) {
        printf("nu avem drum");
        return;
    }
    int curent = dest;
    while (curent != -1) {
        printf("%d ", curent);
        curent = predecesor[curent];
    }
}
int main() {
    citireArbore();
    afisareArbore();
    pc(3, 4);
	return 0;
}