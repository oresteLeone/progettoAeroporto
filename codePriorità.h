#ifndef codePriorit�
#define codePriorit�
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
}CP;    //Coda Priorit�

void initCodaPriorit�(CP* p, int n);

void cancellaCodaPriorit�(CP cp);

int EmptyCodaPriorit�(CP cp);

int FullCodaPriorit�(CP cp);

int MinCodaPriorit�(CP cp);

void scambio(nodoCP v[], int i, int j);

void InsertMinCodaPriorit�(CP* p, int x, int pr);

void minHeapRestore(nodoCP v[], int i, int n);

int DeleteMinCodaPriorit�(CP* p);

void DecreaseKeyMinCodaPriorit�(CP* p, int x, int pr);

#endif