#ifndef codePriorità
#define codePriorità
#include "definers.h"

//definizione struttura della coda a priorità
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

//inizializzazione
void initCodaPriorità(CP* p, int n);

//eliminazione
void cancellaCodaPriorità(CP cp);

//controllo sullo stato della coda (vuota)
int EmptyCodaPriorità(CP cp);

//controllo sullo stato della coda(piena)
int FullCodaPriorità(CP cp);

//estrazione del primo elemento
int MinCodaPriorità(CP cp);

//funzione dello scambio di elementi
void scambio(nodoCP v[], int i, int j);

//inserimento del minimo
void InsertMinCodaPriorità(CP* p, int x, int pr);

void minHeapRestore(nodoCP v[], int i, int n);

int DeleteMinCodaPriorità(CP* p);

void DecreaseKeyMinCodaPriorità(CP* p, int x, int pr);

#endif