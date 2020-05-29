#ifndef edgelib
#define edgelib
#include "definers.h" //libreria delle costanti definite

//definizione struttura degli archi
struct edgeType {
    int key;                //chiave numerica del nodo
    int pesoEconomy;        //peso arco costo economico
    int pesoDistanza;       //peso arco costo distanza
    struct edgeType* next;  //nodo successivo
};
typedef struct edgeType* edge;


void printList(edge L);


edge checkListRemoval(edge L, int node_to_remove);


edge initNodeList(int info, int eco, int dist);


edge randomList(int index, int mod);


edge appendNodeList(edge L, int target, int eco, int dist);


edge addNodeHead(edge L, int target, int eco, int dist);


edge removeNodeList(edge L, int target);


void freeList(edge L);


int DimLista(edge L);
#endif