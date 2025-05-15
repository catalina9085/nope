//graf de acoperire minima Kruskal
#include <stdio.h>
#include <stdint.h>
#define MAX 100
int n;
int graf[MAX][MAX];
int s[MAX];
void citireGraf() {
	FILE* f = fopen("in3.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0;i < n;i++)
		for (int j = 0;j < n;j++)
			fscanf(f, "%d", &graf[i][j]);
	for (int i = 0;i < n;i++)
		s[i] = i;

}
void printareGraf() {
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++)
			printf("%d ", graf[i][j]);
		printf("\n");
	}
}

void kruskal() {
	for (int k = 0;k < n - 1;k++) {
		int min = 999, mini = -1, minj = -1;
		for (int i = 0;i < n;i++) {
			for (int j = 0;j < n;j++) {
				if (graf[i][j] != 0 && s[i] != s[j] && graf[i][j] < min) {
					min = graf[i][j];
					mini = i;
					minj = j;
				}
			}
		}
		for (int i = 0;i < n;i++)
			if (s[i] == s[minj])
				s[i] = s[mini];
		printf("%d %d %d\n", mini, minj, graf[mini][minj]);

	}
}


int main()
{
	citireGraf();
	kruskal();



	return 0;
}

