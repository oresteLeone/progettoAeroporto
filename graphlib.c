#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "graphlib.h"


//inizializzazione grafo
Graph initGraph(int n) {
	Graph G;
	int i;
	G = (Graph)malloc(sizeof(struct graphType));
	if (G) {
		G->adj = (edge*)malloc(n * sizeof(struct edgeType));
		if (G->adj) {
			G->nv = n;
			for (i = 0;i < n;i++) {
				G->adj[i] = NULL;
			}
		}
	}
	return G;
}

//Free del grafo
void freeGraph(Graph G) {
	if (G != NULL) {
		if (G->nv > 0) {
			int i = 0;
			for (i = 0; i < G->nv; i++) {
				freeList(G->adj[i]);
			}
		}
		free(G);
	}
}

//stampa del grafo
void printGraph(Graph G) {
	if (G != NULL) {
		int i = 0;
		for (i = 0;i < G->nv;i++) {
			printf("%d -> ", i);
			printList(G->adj[i]);
			printf("\n");
		}
	}
}

//aggiungi nodo al grafo
void addNode(Graph G) {
	if (G != NULL) {
		edge* old = G->adj;
		int i = 0;
		G->adj = (edge*)malloc((G->nv + 1) * sizeof(struct edgeType));
		for (i = 0;i < G->nv;i++)
			G->adj[i] = old[i];
		G->nv += 1;
		G->adj[G->nv - 1] = NULL;
	}
}

//rimozione di un nodo dal grafo
void removeNode(Graph G, int node_to_remove) {
	if (G != NULL) {
		int i = 0;
		int x = 0;
		edge* tmp = G->adj;
		G->adj = (edge*)calloc(G->nv - 1, sizeof(struct edgeType));
		for (i = 0; i < G->nv; i++) {
			if (i != node_to_remove) {
				G->adj[x] = checkListRemoval(tmp[i], node_to_remove);
				x++;
			}
			else {
				freeList(tmp[i]);
			}
		}
		free(tmp);
		G->nv -= 1;
	}
}

//aggiunge arco da source a target
void addEdge(Graph G, int source, int target, int eco, int dist) {
	assert(G != NULL);
	assert(source < G->nv);
	assert(target < G->nv);
	if (source != target) {
		G->adj[source] = appendNodeList(G->adj[source], target, eco, dist);
	}

}

//rimuove arco da source a target
edge removeEdge(Graph G, int source, int target) {
	assert(G != NULL);
	assert(source < G->nv);
	assert(target < G->nv);
	if (source != target) {
		G->adj[source] = removeNodeList(G->adj[source], target);
	}
	return G->adj[source];
}