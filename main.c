#include <stdio.h>

typedef struct node {

	const int vertix;
	int d, l;
	struct node *next;
	
} *Node;

int main() {

	/*
	N - numero de pontos de distribuicao
	M - numero de ligacoes
	*/

	int N, M;
	int from, to, i;

	scanf("%d", &N);
	scanf("%d", &M);

	Node *adj = malloc(sizeof(Node)*N);
	for (i = 0; i < N; i++) {
		adj[i] = malloc(sizeof(struct Node));
		adj[i]->vertix = i;
		adj[i]->d = -1;
		adj[i]->l = -1;
	}

	while(scanf("%d %d", &from, &to) != EOF) {
		add(adj[from], to);
	}





	return 0;

}

void add(Node from, int to) {

	Node new = malloc(sizeof(struct node));
	new->vertix = to;
	new->next = from->next;
	new->d = -1;
	new->l = -1;

	from->next = new;
}

void tarjan(Node *adj, int N) {
	int *lifo;
	Node[N] scc;
	int index = 1;

	for (int i = 0; i < N; i++) {
		if (adj[i]->d == -1) {
			adj[i]->d = index;
			adj[i]->l = index;
			index++;

			if (lifo = NULL) {
				lifo = adj[i];
			} else {
				adj[i]
			}
		}
	}

}