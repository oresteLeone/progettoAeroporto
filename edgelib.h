#ifndef edgelib
#define edgelib
#include "definers.h" //libreria delle costanti definite
#include "listlib.h"

//definizione struttura degli archi
struct edgeType {
    int key;                //chiave numerica del nodo
    int pesoEconomy;        //peso arco costo economico
    int pesoDistanza;       //peso arco costo distanza
    struct edgeType* next;  //nodo successivo
};
typedef struct edgeType* edge;

//stampa lista di adiacenza
void printList(edge L, list* destinazioni);

//rimuove le occorenze del nodo rimosso dalle liste di adiacenza
edge checkListRemoval(edge L, int node_to_remove);

//inizializza un nodo della lista di adiacenza
edge initNodeList(int info, int eco, int dist);


edge randomList(int index, int mod);

//inserisce un nodo in coda alla lista di adiacenza
edge appendNodeList(edge L, int target, int eco, int dist);

//inserisce un nodo in testa alla lista di adiacenza
edge addNodeHead(edge L, int target, int eco, int dist);

//rimuove la lista di adiacenza di un nodo
edge removeNodeList(edge L, int target);

//dealloca una lista
void freeList(edge L);

//restituisce la dimensione della lista di adiacenza
int DimLista(edge L);

//funzione per la visita di lista di adiacenza che aggiorna i gradi entranti nell array 
void traverselistIN(edge list, int ArrayInDegree[]);
#endif