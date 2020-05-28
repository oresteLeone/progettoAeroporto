#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listlib.h"

//funzione che inserisce una nuova destinazione nella lista
list* inserisciDestinazione(list* destinazioni, int n, char* citt�) {
    if (!destinazioni) { // se destinazioni � vuoto creo il nuovo elemento e lo imposto come destinazioni
        list* aux = (list*)malloc(sizeof(list));
        aux->n = n;
        strcpy(aux->citt�, citt�);
        aux->next = NULL;
        destinazioni = aux;
    }
    else
        destinazioni->next = inserisciDestinazione(destinazioni->next, n, citt�);

    return destinazioni;
}

//funzione che rimuove una destinazione dalla lista
list* decrementaNodi(list* destinazioni) {
    if (destinazioni != NULL) {
        destinazioni->n--;
        destinazioni->next = decrementaNodi(destinazioni->next);
    }

    return destinazioni;
}

list* eliminaDestinazione(list* destinazioni, char* citt�) {
    if (destinazioni != NULL) {
        if (strcmp(destinazioni->citt�, citt�) == 0) {
            list* tmp = destinazioni->next;
            free(destinazioni);
            tmp = decrementaNodi(tmp);
            return tmp;
        }
        destinazioni = eliminaDestinazione(destinazioni->next, citt�);
    }
    return destinazioni;
}

//funzione che ricerca una destinazione e restituisce il valore numerico associato
int ricercaDestinazione(list* destinazioni, char* citt�) {
    int trovato = -1;
    if (destinazioni != NULL) {
        if (strcmp(destinazioni->citt�, citt�) == 0)
            return destinazioni->n;
        else
            trovato = ricercaDestinazione(destinazioni->next, citt�);
    }
    return trovato;
}

//funzione che stampa gli elementi della lista
void stampaLista(list* destinazioni) {
    if (destinazioni != NULL) {
        printf("\nNodo associato: %d\n", destinazioni->n);
        printf("\nCitta': %s\n", destinazioni->citt�);
        stampaLista(destinazioni->next);
    }
}

//funzione che elimina totalmente la lista
void cancellaLista(list* destinazioni) {
    if (destinazioni != NULL) {
        cancellaLista(destinazioni->next);
        free(destinazioni);
    }
}