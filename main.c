#include <stdio.h>

typedef struct node {

	const int vertix;
	struct node *next;
	
};

int main() {

	/*
	N - numero de pontos de distribuicao
	M - numero de ligacoes
	*/

	int N, M;
	int from, to;

	scanf("%d", &N);
	scanf("%d", &M);

	struct node *adj = malloc(sizeof(struct node)*N);

	while(scanf("%d %d", &from, &to) != EOF) {
		add(adj[from];
	}



	return 0;

}