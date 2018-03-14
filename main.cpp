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
Node tarjan(Node currNode, int N, int &index);


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
	int count = 0;

	for (int i = 0; i < N; i++) {
		if (-1 == adj[i]->vertix->d) {
			scc[count++] = tarjan(adj[i], N, index);
		}
	}

/*	for(i = 0; i < count; i++) {
        std::cout << "i: "<< i << std::endl;
        Node n = scc[i];
        while(n != NULL) {
            std::cout << n->vertix->vnumber << std::endl;
            n = n->next;
        }
    }*/



	return 0;

}

void addEdge(Node from, Vertix to) {

	Node n = (Node)malloc(sizeof(struct node));
	n->vertix = to;
	n->next = from->next;
	from->next = n;
}

Node tarjan(Node currNode, int N, int &index) {
	std::stack<Vertix> lifo;

	currNode->vertix->d = index;
	currNode->vertix->l = index;
	index++;

	lifo.push(currNode->vertix);
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
			n->vertix = lifo.top();
			lifo.pop();
			if (NULL == n->vertix) {
			    return NULL;
			}
			n->vertix->onStack = false;
		} while (n->vertix != currNode->vertix);

		return n;
	}


}