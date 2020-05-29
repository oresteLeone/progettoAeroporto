#ifndef graphlib
#define graphlib
#include "edgelib.h" //libreria archi



//definizione struttura grafo
struct graphType {
    int nv;         //numero vertici
    edge* adj;     //lista di adiacenza
};
typedef struct graphType* Graph;


//inizializzazione grafo
Graph initGraph(int n);

//Free del grafo
void freeGraph(Graph G);

//stampa del grafo
void printGraph(Graph G, list* destinazioni);

//aggiungi nodo al grafo
void addNode(Graph G);

//rimozione di un nodo dal grafo
void removeNode(Graph G, int node_to_remove);

//aggiunge arco da source a target
void addEdge(Graph G, int source, int target, int eco, int dist);

//rimuove arco da source a target
edge removeEdge(Graph G, int source, int target);


#endif