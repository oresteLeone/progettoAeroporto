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

void initEdge(Graph G) {
	addEdge(G, 0, 1, 20, 60);
	addEdge(G, 1, 2, 40, 40);
	addEdge(G, 2, 3, 30, 30);
	addEdge(G, 0, 3, 10, 35);
	addEdge(G, 3, 1, 5, 20);

	addEdge(G, 0, 1, 10, 187);
	addEdge(G, 0, 7, 20, 219);
	addEdge(G, 0, 14, 100, 1016);
	addEdge(G, 0, 19, 500, 5213);

	addEdge(G, 1, 3, 25, 248);
	addEdge(G, 1, 8, 10, 126);
	addEdge(G, 1, 9, 90, 960);
	addEdge(G, 1, 10, 20, 245);
	addEdge(G, 1, 12, 50, 561);
	addEdge(G, 1, 13, 80, 843);
	addEdge(G, 1, 17, 900, 9718);

	addEdge(G, 2, 0, 10, 187);
	addEdge(G, 2, 3, 20, 234);

	addEdge(G, 3, 1, 20, 248);
	addEdge(G, 3, 2, 20, 234);
	addEdge(G, 3, 4, 8, 80);

	addEdge(G, 4, 3, 8, 80);
	addEdge(G, 4, 5, 10, 190);

	addEdge(G, 5, 4, 10, 190);
	addEdge(G, 5, 8, 20, 295);

	addEdge(G, 6, 7, 10, 105);

	addEdge(G, 7, 0, 20, 219);
	addEdge(G, 7, 6, 10, 105);

	addEdge(G, 8, 1, 10, 126);

	addEdge(G, 9, 1, 90, 960);
	addEdge(G, 9, 11, 30, 320);
	addEdge(G, 9, 12, 60, 632);
	addEdge(G, 9, 13, 90, 932);
	addEdge(G, 9, 14, 110, 1139);

	addEdge(G, 10, 1, 20, 245);

	addEdge(G, 11, 9, 30, 320);
	addEdge(G, 11, 13, 60, 652);

	addEdge(G, 12, 1, 50, 561);
	addEdge(G, 12, 9, 60, 632);

	addEdge(G, 13, 1, 80, 843);
	addEdge(G, 13, 9, 90, 932);
	addEdge(G, 13, 11, 60, 652);
	addEdge(G, 13, 17, 890, 8918);

	addEdge(G, 14, 0, 100, 1016);
	addEdge(G, 14, 9, 110, 1139);
	addEdge(G, 14, 15, 30, 302);
	addEdge(G, 14, 16, 100, 1005);
	addEdge(G, 14, 18, 850, 8543);
	addEdge(G, 14, 19, 580, 5892);

	addEdge(G, 15, 14, 30, 302);

	addEdge(G, 16, 14, 100, 1005);

	addEdge(G, 17, 1, 970, 9718);
	addEdge(G, 17, 13, 890, 8918);

	addEdge(G, 18, 14, 850, 8543);
	addEdge(G, 18, 19, 890, 8933);

	addEdge(G, 19, 0, 520, 5213);
	addEdge(G, 19, 14, 580, 5892);
	addEdge(G, 19, 18, 890, 8933);

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
void printGraph(Graph G, list* destinazioni) {
	if (G != NULL) {
		int i = 0;
		for (i = 0;i < G->nv;i++) {
			printf("%d %s -> ", i, ricercaDestinazionePerNodo(destinazioni, i));
			printList(G->adj[i], destinazioni);
			printf("\n\n");
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
void removeEdge(Graph G, int source, int target) {
	assert(G != NULL);
	assert(source < G->nv);
	assert(target < G->nv);
	if (source != target) {
		G->adj[source] = removeNodeList(G->adj[source], target);
	}
	
}