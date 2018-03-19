#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stack>

typedef struct vertix {

	int vnumber;
	int d, l;
	bool onStack;
	int sccn;

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
		adj[i]->vertix->vnumber = i + 1;
		adj[i]->vertix->d = -1;
		adj[i]->vertix->l = -1;
		adj[i]->vertix->onStack = false;
		adj[i]->vertix->sccn = -1;
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

	for(i = 0; i < sccCount; i++) {  //para controlo apenas
    std::cout << "i: "<< i << std::endl;
    Node n = scc[i];
    while(n != NULL) {
      std::cout << n->vertix->vnumber << std::endl;
      n = n->next;
    }
  }

  Node *connections = (Node*)malloc(sizeof(Node)*sccCount);
	for (i = 0; i < sccCount; i++) {
		connections[i] = (Node)malloc(sizeof(struct node));
		connections[i]->vertix = scc[i]->vertix;
		connections[i]->next = NULL;
	}


  for (i = 0; i < sccCount; i++) {  //percorro lista de scc
  	Node n = scc[i];
    while(n != NULL) {              //percorro nodes da scc
    	Node curr = adj[n->vertix->vnumber - 1];
      for (Node m = curr->next; m != NULL; m = m->next) { //percorro ligacoes de cada vertix da scc
      	if (curr->vertix->vnumber != m->vertix->vnumber) {
      		//aqui tenho de adicionar o m->vertix `a lista ligada com inicio em connections[i], preferencialmente ordenada/m
					if (NULL == connections[i]->next) { printf("oii 100\n");
						connections[i]->next = (Node)malloc(sizeof(struct node));
						connections[i]->next->vertix = m->vertix;
						connections[i]->next->next = NULL;
					// } else if (connections[i]->vertix->vnumber > m->vertix->vnumber) { printf("oii 102\n");
					// 	Node p = (Node)malloc(sizeof(struct node));
					// 	p->next = connections[i]->next;
					//   connections[i]->next = p;
					// 	p->vertix = connections[i]->vertix;
					// 	connections[i]->vertix = m->vertix;
					} else { printf("oii 108\n");
						Node r;
						Node p = (Node)malloc(sizeof(struct node)); //printf("115\n");
						for (r = connections[i]->next; r->next != NULL && r->next->vertix->vnumber < m->vertix->vnumber; r = r->next);  //printf("116\n");//insiro ligacao [...]
						p->next = r->next; //printf("117\n");
						r->next = p; //printf("118\n");
						p->vertix = m->vertix; //printf("119\n");
					}
      	}
      }
        n = n->next;
    }
  }

	for (i = 0; i < sccCount; i++) {
		Node n;
		for (n = connections[i]->next; n != NULL; n = n->next) {
			printf("%d %d\n", connections[i]->vertix->vnumber, n->vertix->vnumber);
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
			aux->vertix->sccn = sccCount;
			lifo->pop();
			//std::cout << n->vertix->vnumber << adj[currNode]->vertix->vnumber << std::endl; NOT UTIL bc of else
		} while (aux->vertix != adj[currNode]->vertix);

		scc[sccCount++] = n;
	}


}
