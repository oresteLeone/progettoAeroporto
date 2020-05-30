#ifndef codePriorità
#define codePriorità
#include "definers.h"

typedef struct {
    int valore;
    int priorita;
    int posizione;
} nodoCP;

typedef struct {
    int capacita;
    int dim;
    nodoCP* H;
}CP;    //Coda Priorità

void initCodaPriorità(CP* p, int n);

void cancellaCodaPriorità(CP cp);

int EmptyCodaPriorità(CP cp);

int FullCodaPriorità(CP cp);

int MinCodaPriorità(CP cp);

void scambio(nodoCP v[], int i, int j);

void InsertMinCodaPriorità(CP* p, int x, int pr);

void minHeapRestore(nodoCP v[], int i, int n);

int DeleteMinCodaPriorità(CP* p);

void DecreaseKeyMinCodaPriorità(CP* p, int x, int pr);

#endif