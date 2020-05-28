#ifndef edgelib
#define edgelib
#include "definers.h" //libreria delle costanti definite

//definizione struttura degli archi
typedef struct edgeType {
    int key;                //chiave numerica del nodo
    int pesoEconomy;        //peso arco costo economico
    int pesoDistanza;       //peso arco costo distanza
    struct edgeType* next;  //nodo successivo
} edge;

void addEdge(Graph G, int source, int target, int peso);
void removeEdge(Graph G, int source, int target);
#endif