#ifndef graphlib
#define graphlib
#include "edgelib.h" //libreria archi

#define num_nodi 

//definizione struttura grafo
typedef struct graphType {
    int num_nodi;         //numero vertici
    edge** adj;     //lista di adiacenza
} Graph;
#endif