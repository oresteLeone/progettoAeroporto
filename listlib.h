#ifndef listlib
#define listlib
#include "definers.h"

typedef struct listType {
    int n;                  //valore del nodo associato alla citt�
    char citt�[maxstring];  //nome della citt�
    struct listType* next;  //nodo successivo
} list;

//funzione che inserisce una nuova destinazione nella lista
list* inserisciDestinazione(list* destinazioni, int n, char* citt�);

//funzione che rimuove una destinazione dalla lista
list* decrementaNodi(list* destinazioni);
list* eliminaDestinazione(list* destinazioni, char* citt�);

//funzione che ricerca una destinazione e restituisce il valore numerico associato
int ricercaDestinazione(list* destinazioni, char* citt�);

//funzione che stampa gli elementi della lista
void stampaLista(list* destinazioni);

//funzione che elimina totalmente la lista
void cancellaLista(list* destinazioni);

#endif
