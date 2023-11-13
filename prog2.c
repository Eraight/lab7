#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

int* CreateGraph(int vertexes) {
	int* Mtrx = (int*)malloc(sizeof(int) * vertexes * vertexes);
	if (!Mtrx) return 0;
	for (int i = 0; i != vertexes; i++) {
		*(Mtrx + i * vertexes + i) = 0;
		for (int j = 0; j < i; j++) {
			*(Mtrx + i * vertexes + j) = rand() % 2;
			*(Mtrx + j * vertexes + i) = *(Mtrx + i * vertexes + j);
		}
	}
	return Mtrx;
}

void ShowGraph(int* graph, int vertexes) {
	if (!graph) return;
	for (int i = 0; i != vertexes; i++) {
		for (int j = 0; j != vertexes; j++) {
			printf("%i ", *(graph + i * vertexes + j));
		}
		printf("|%i", i + 1);
		printf("\n");
	}
}

void DepthSearch(int* graph, int vertexes) {
	int* pureStack = (int*)malloc(sizeof(int) * 1000), * visited = (int*)malloc(sizeof(int) * vertexes), temp = -1;
	if (!pureStack || !visited) return;
	for (int i = 0; i != vertexes; i++) {
		*(pureStack + i) = -1;
		*(visited + i) = 0;
	}

	for (int i = 0; i != vertexes; i++) {
		if (!visited[i]) {
			visited[i] = 1;
			printf("%i ", i + 1);
		}

		for (int j = vertexes - 1; j >= 0; j--) {
			if (*(graph + i * vertexes + j) && !visited[j]) {
				temp++; pureStack[temp] = j;
			}
		}
		if (temp == -1) {
			return;
		}
		if (pureStack[0] != -1) {
			i = pureStack[temp] - 1;
			pureStack[temp] = -1; temp--;
		}
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	srand(time(NULL));
	int vertexNum = 10;
	struct node* listGraph = 0;
	printf("Введите кол-во вершин для графа: ");
	(void)scanf("%i", &vertexNum);
	if (!vertexNum) return 1;
	int* smej = CreateGraph(vertexNum);
	ShowGraph(smej, vertexNum);
	DepthSearch(smej, vertexNum);
	free(smej);
	return 0;
}
