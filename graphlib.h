#ifndef graphlib
#define graphlib
#include "edgelib.h" //libreria archi

#define num_nodi 20

//definizione struttura grafo
struct graphType {
    int num_nodi;         //numero vertici
    edge* adj;     //lista di adiacenza
};

typedef struct graphType* Graph;
<<<<<<< HEAD
=======

//inizializzazione grafo
Graph initGraph(int n);

//Free del grafo
void freeGraph(Graph G);

//stampa del grafo
void printGraph(Graph G);

//aggiungi nodo al grafo
void addNode(Graph G);

//rimozione di un nodo dal grafo
void removeNode(Graph G, int node_to_remove);

//aggiunge arco da source a target
void addEdge(Graph G, int source, int target, int eco, int dist);

//rimuove arco da source a target
edge removeEdge(Graph G, int source, int target);


>>>>>>> ef74905c835344d6bfefcb48bdd0668245ce1aa9
#endif