#ifndef graphlib
#define graphlib
#include "edgelib.h" //libreria archi

//definizione struttura grafo
typedef struct graphType {
    int nv;         //numero vertici
    edge** adj;     //lista di adiacenza
} Graph;

#endif