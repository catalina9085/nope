//graf de acoperire minima algoritm 1
#include <stdio.h>
#include <stdint.h>
#define MAX 100
int n;
int graf[MAX][MAX];
int U[MAX];
int N[MAX];
void citireGraf() {
	FILE* f = fopen("in3.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0;i < n;i++)
		for (int j = 0;j < n;j++)
			fscanf(f, "%d", &graf[i][j]);
	U[0] = 1;
	for (int i = 1;i < MAX;i++)
		U[i] = 0;

}
void printareGraf() {
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++)
			printf("%d ", graf[i][j]);
		printf("\n");
	}
}

void alg1() {
	for (int k = 0;k < n - 1;k++) {
		int min = 999, mini = -1, minj = -1;
		for (int i = 0;i < n;i++) {
			for (int j = 0;j < n;j++) {
				if (graf[i][j] != 0 && U[i] != U[j] && graf[i][j] < min) {
					min = graf[i][j];
					mini = i;
					minj = j;
				}
			}
		}
		U[mini] = U[minj] = 1;
		printf("%d %d %d\n", mini, minj, graf[mini][minj]);

	}
}


int main()
{
	citireGraf();
	alg1();
	return 0;
}

