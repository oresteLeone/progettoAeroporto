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

//inizializzazione archi
void initEdge(Graph G);

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
void removeEdge(Graph G, int source, int target);

//funzione che restituisce l'array coi gradi entranti
int* gradiEntranti(Graph G, int ArrayInDegree[] );

//restutuisce il primo nodo con grado entrante maggiore
int nodeMaxInDegree(int ArrayInDegree[], int dim);


#endif