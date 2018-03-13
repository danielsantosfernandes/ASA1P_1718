#include <stdio.h>
#include <stack>

#define min(a, b) a < b ? a : b

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
		addEdge(adj[from], to);
	}

	int index = 1;
	// TODO SCC's storage

	for (int i = 0; i < N; i++) {
		if (-1 == adj[i]->d) {
			tarjan(adj[i], N, index); //SCC
		}
	}




	return 0;

}

void addEdge(Node from, int to) {

	Node new = malloc(sizeof(struct node));
	new->vertix = to;
	new->next = from->next;
	new->d = -1;
	new->l = -1;

	from->next = new;
}

void tarjan(Node currNode, int N, int &index) {
	std::stack<Node> lifo;

	currNode->d = index;
	currNode->l = index;
	index++;

	lifo.push(currNode);
	//curr->onStack = True

	for (Node n = currNode->next; n!=NULL; n = n->next) {
		if (-1 == n->d) {
			tarjan(n, N, index);
			currNode->l = min(currNode->l, n->l);
		} else if (/*n->onStack*/) {
			currNode->l = min(currNode->l, n->d);
		}
	}

	if (currNode->l == currNode->d) {
		//criar SCC
		//pop e add a SCC até currNode (onStack=false)
	}


}