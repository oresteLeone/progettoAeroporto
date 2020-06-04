#ifndef codePriorit�
#define codePriorit�
#include "definers.h"

//definizione struttura della coda a priorit�
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

//inizializzazione
void initCodaPriorit�(CP* p, int n);

//eliminazione
void cancellaCodaPriorit�(CP cp);

//controllo sullo stato della coda (vuota)
int EmptyCodaPriorit�(CP cp);

//controllo sullo stato della coda(piena)
int FullCodaPriorit�(CP cp);

//estrazione del primo elemento
int MinCodaPriorit�(CP cp);

//funzione dello scambio di elementi
void scambio(nodoCP v[], int i, int j);

//inserimento del minimo
void InsertMinCodaPriorit�(CP* p, int x, int pr);

void minHeapRestore(nodoCP v[], int i, int n);

int DeleteMinCodaPriorit�(CP* p);

void DecreaseKeyMinCodaPriorit�(CP* p, int x, int pr);

#endif