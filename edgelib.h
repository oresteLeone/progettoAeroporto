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

edge initNodeList(int info, int pesoEco, int pesoDis);
edge appendNodeList(List L, int target, int pesoEco, int pesoDis);
edge addNodeHead(edge E, int target, int pesoEco, int pesoDis);
edge addNodeTail(edge E, int target, int pesoEco, int pesoDis);
edge removeNodeList(edge E, int target);
edge removeHead(edge E);
edge removeTail(edge E);
void freeList(edge E);
void printList(edge E);




#endif