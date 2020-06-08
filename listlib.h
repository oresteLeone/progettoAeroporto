#ifndef listlib
#define listlib
#include "definers.h"

typedef struct listType {
    int n;                  //valore del nodo associato alla città
    char città[maxstring];  //nome della città
    struct listType* next;  //nodo successivo
} list;

//funzione che inserisce una nuova destinazione nella lista
list* inserisciDestinazione(list* destinazioni, int n, char* città);

//funzione che inizializza la lista
list* initDestinazioni(list* destinazioni, int nv);

//funzione che rimuove una destinazione dalla lista
list* decrementaNodi(list* destinazioni);
list* eliminaDestinazione(list* destinazioni, char* città);

//funzione che ricerca una destinazione e restituisce il valore numerico associato
int ricercaDestinazionePerCittà(list* destinazioni, char* città);

//funzione che ricerca una destinazione e restituisce il nome della città associato
char* ricercaDestinazionePerNodo(list* destinazioni, int n);

//funzione che stampa gli elementi della lista
void stampaLista(list* destinazioni);

//funzione che elimina totalmente la lista
void cancellaLista(list* destinazioni);

#endif