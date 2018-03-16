#include <stdio.h>
#include <stdlib.h>
#include <iostream>
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

void addEdge(Node from, Vertix to);
void tarjan(Node*, int, int, int&, std::stack<Vertix>*, Node*, int&);


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
		adj[i]->vertix = (Vertix)malloc(sizeof(struct vertix));
		adj[i]->vertix->vnumber = i+1;
		adj[i]->vertix->d = -1;
		adj[i]->vertix->l = -1;
		adj[i]->vertix->onStack = false;
		adj[i]->next = NULL;
	}

	while(scanf("%d %d", &from, &to) != EOF) {
		addEdge(adj[from - 1], adj[to - 1]->vertix);
	}

	int index = 1;

    /*for(i = 0; i < N; i++) {
	    std::cout << "de: " << adj[i]->vertix->vnumber << "\npara: "<< std::endl;
	    Node n = adj[i]->next;
	    while(n != NULL) {
	        std::cout << n->vertix->vnumber << std::endl;
	        n = n->next;
	    }
    }*/

	Node scc[N];
	int sccCount = 0;
	std::stack<Vertix> lifo;

	for (i = 0; i < N; i++) {
		if (-1 == adj[i]->vertix->d) {
			tarjan(adj, i, N, index, &lifo, scc, sccCount);
		}
	}

	for(i = 0; i < sccCount; i++) {
        std::cout << "i: "<< i << std::endl;
        Node n = scc[i];
        while(n != NULL) {
            std::cout << n->vertix->vnumber << std::endl;
            n = n->next;
        }
    }

    for (i = 0; i < sccCount; i++) {
    	Node n = scc[i];
        while(n != NULL) {
            
            n = n->next;
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
//          grafo,     node orig,    N V,   stack index,                 stack,   array de scc,   numero de scc
void tarjan(Node* adj, int currNode, int N, int &index, std::stack<Vertix> *lifo, Node *scc, int &sccCount) {

	adj[currNode]->vertix->d = index;
	adj[currNode]->vertix->l = index;
	index++;

	lifo->push(adj[currNode]->vertix); std::cout << "push " << currNode + 1 << std::endl;
	adj[currNode]->vertix->onStack = true;

	for (Node n = adj[currNode]->next; n!=NULL; n = n->next) {
		if (-1 == n->vertix->d) {
			tarjan(adj, n->vertix->vnumber - 1, N, index, lifo, scc, sccCount);
			adj[currNode]->vertix->l = min(adj[currNode]->vertix->l, n->vertix->l);
		} else if (n->vertix->onStack) {
			adj[currNode]->vertix->l = min(adj[currNode]->vertix->l, n->vertix->d);
		}
	}

	if (adj[currNode]->vertix->l == adj[currNode]->vertix->d) {

		Node aux, n = NULL;

		do {
			if (NULL == n || lifo->top()->vnumber < n->vertix->vnumber) {
				aux = n;
				n = (Node)malloc(sizeof(struct node));
				n->next = aux;
				n->vertix = lifo->top();      std::cout << "pop " << lifo->top()->vnumber << std::endl;
				n->vertix->onStack = false;
				aux = n;
			} else {
				aux = n->next;
				n->next = (Node)malloc(sizeof(struct node));
				n->next->next = aux;
				n->next->vertix = lifo->top();   std::cout << "pop " << lifo->top()->vnumber << std::endl;
				n->next->vertix->onStack = false;
				aux = n->next;
			}
			lifo->pop();
			//std::cout << n->vertix->vnumber << adj[currNode]->vertix->vnumber << std::endl; NOT UTIL bc of else
		} while (aux->vertix != adj[currNode]->vertix);

		scc[sccCount++] = n;
	}


}