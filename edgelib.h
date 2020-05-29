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


void printList(edge* L);


edge* checkListRemoval(edge* L, int node_to_remove);


edge* initNodeList(int info);


edge* randomList(int index, int mod);


edge* appendNodeList(edge* L, int target, int eco, int dist);


edge* addNodeHead(edge* L, int target);


edge* removeNodeList(edge* L, int target);


void freeList(edge* L);


int DimLista(edge* L);
#endif