//DFS
#include <stdio.h>
#include <stdint.h>
#define MAX 100
int n;
int graf[MAX][MAX];
int visited[MAX];
typedef struct {
	int data[MAX];
	int top;
}Stack;

void initStack(Stack* s) {
	s->top = 0;
}

int isEmpty(Stack* s) {
	return s->top == 0;
}

void push(Stack* s, int el) {
	if (s->top == MAX) {
		printf("Full!");
		return;
	}
	s->data[s->top++] = el;
	//printf("S-a adaugat %d\n", el);
}

int pop(Stack* s) {
	if (isEmpty(s)) {
		printf("Emtpy!");
		return -1;
	}
	return s->data[--s->top];
}

void resetVisited() {
	for (int i = 0;i < n;i++) visited[i] = 0;
}

void citireGraf() {
	FILE* f = fopen("in2.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0;i < n;i++)
		for (int j = 0;j < n;j++)
			fscanf(f, "%d", &graf[i][j]);
	resetVisited();
}
void printareGraf() {
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++)
			printf("%d ", graf[i][j]);
		printf("\n");
	}
}
//recursiv
void sa(int start) {
	printf("%d ", start);
	visited[start] = 1;
	for (int i = 0;i < n;i++) {
		if (!visited[i] && graf[start][i] == 1) {
			sa(i);
		}
	}
}

//nerecursiv
void sa2(int start) {
	Stack s;
	initStack(&s);
	push(&s, start);
	while (!isEmpty(&s)) {
		int curent = pop(&s);
		if (!visited[curent]) {
			printf("%d ", curent);
			visited[curent] = 1;
			for (int i = n - 1;i >= 0;i--) {
				if (graf[curent][i] == 1 && !visited[i])
					push(&s, i);
			}
		}
	}

}
//nr elemente conexe
void conexe() {
	int cc = 0;
	for (int i = 0;i < n;i++) {
		if (!visited[i]) {
			sa(i);
			cc++;
		}
	}
	printf("\n%d", cc);
}

int main()
{
	citireGraf();
	//sa(0);
	//printf("\n");
	//resetVisited();
	//sa2(0);
	conexe();



	return 0;
}

