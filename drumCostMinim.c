//drum de cost minim,algoritm dijkstra,atat grafuri orientate cat si neorientate
#include <stdio.h>
#include <stdint.h>

#define MAX 100
int graf[100][100];
int n;
int visited[MAX];
int dist[MAX];

int minDist() {
	int min = 999;
	int mini = 0;

	for (int i = 0;i < n;i++)
		if (!visited[i] && dist[i] <= min) {
			//visited[i] = 1;
			min = dist[i];
			mini = i;
		}
	return mini;
}

void dijkstra(int start) {
	for (int i = 0; i < n; i++) {
		dist[i] = 999;
		visited[i] = 0;
	}
	dist[start] = 0;

	for (int pas = 0;pas < n - 1;pas++) {
		int dmin = minDist();
		visited[dmin] = 1;

		for (int i = 0;i < n;i++)
			if (!visited[i] && graf[dmin][i] != 0 && dist[dmin] != 999 && dist[dmin] + graf[dmin][i] < dist[i]) {
				dist[i] = dist[dmin] + graf[dmin][i];
			}
	}

	printf("Distantele minime de la nodul %d:\n", start);
	for (int i = 0; i < n; i++) {
		if (dist[i] == 999)
			printf("Nodul %d nu este accesibil\n", i);
		else
			printf("Nodul %d: %d\n", i, dist[i]);
	}
}

void citireArbore(char* path) {
	FILE* f = fopen(path, "r");
	if (!f) exit(-1);

	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			fscanf(f, "%d", &graf[i][j]);
	for (int i = 0;i < n;i++)
		visited[i] = 0;


}

void afisareArbore() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%d ", graf[i][j]);
		printf("\n");
	}
}




int main(int argc, char** argv)
{
	if (argc < 2)
		printf("not enough arguments");
	else {
		char* path = argv[1];
		citireArbore(path);
		dijkstra(0);

	}
	return 0;
}

