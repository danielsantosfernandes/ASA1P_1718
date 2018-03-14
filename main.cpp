#include <stdio.h>
#include <stack>

typedef struct vertix {

	int vnumber;
	int d, l;
	bool onStack;

} *Vertix;

typedef struct node {

	Vertix vertix;
	struct node *next;
	
} *Node;


inline int min(int a, int b) {
	return a < b ? a : b;
}

int main() {

	/*
	N - numero de pontos de distribuicao
	M - numero de ligacoes
	*/

	int N, M;
	int from, to, i;

	scanf("%d", &N);
	scanf("%d", &M);

	Node *adj = (Node*)malloc(sizeof(Node)*N);
	for (i = 0; i < N; i++) {
		adj[i] = (Node)malloc(sizeof(struct node));
		adj[i]->vertix = (Vertix)malloc(sizeof(struct vertix))
		adj[i]->vertix->vnumber = i;
		adj[i]->vertix->d = -1;
		adj[i]->vertix->l = -1;
		adj[i]->vertix->onStack = false;
	}

	while(scanf("%d %d", &from, &to) != EOF) {
		addEdge(adj[from], adj[to]->vertix);
	}

	int index = 1;

	Node scc[N];
	int count = 0;

	for (int i = 0; i < N; i++) {
		if (-1 == adj[i]->d) {
			scc[count++] = tarjan(adj[i], N, index);
		}
	}

	return 0;

}

void addEdge(Node from, Vertix to) {

	Node n = (Node)malloc(sizeof(struct node));
	n->vertix = to;
	n->next = from->next;

	from->next = n;
}

std::Array<> *tarjan(Node currNode, int N, int &index) {
	std::stack<Node> lifo;

	currNode->d = index;
	currNode->l = index;
	index++;

	lifo.push(currNode);
	currNode->vertix->onStack = true;

	for (Node n = currNode->next; n!=NULL; n = n->next) {
		if (-1 == n->vertix->d) {
			tarjan(n, N, index);
			currNode->vertix->l = min(currNode->vertix->l, n->vertix->l);
		} else if (n->vertix->onStack) {
			currNode->vertix->l = min(currNode->vertix->l, n->vertix->d);
		}
	}

	if (currNode->vertix->l == currNode->vertix->d) {
		
		Vertix v;
		Node temp, n = NULL;

		do {
			temp = n;
			n = (Node)malloc(sizeof(struct node));
			n->next = temp;
			n->vertix = lifo.pop();
			n->vertix->onStack = false;
		} while (n->vertix != currNode->vertix);

		return n;
	}


}