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

//funzione che inizializza la lista
list* initDestinazioni(list* destinazioni, int nv) {
    for (int i = 0; i < nv; i++) {
        if (i == 0)
            destinazioni = inserisciDestinazione(destinazioni, i, "Napoli");
        else if (i == 1)
            destinazioni = inserisciDestinazione(destinazioni, i, "Milano");
        else if (i == 2)
            destinazioni = inserisciDestinazione(destinazioni, i, "Roma");
        else if (i == 3)
            destinazioni = inserisciDestinazione(destinazioni, i, "Firenze");
        else if (i == 4)
            destinazioni = inserisciDestinazione(destinazioni, i, "Bologna");
        else if (i == 5)
            destinazioni = inserisciDestinazione(destinazioni, i, "Genova");
        else if (i == 6)
            destinazioni = inserisciDestinazione(destinazioni, i, "Brindisi");
        else if (i == 7)
            destinazioni = inserisciDestinazione(destinazioni, i, "Bari");
        else if (i == 8)
            destinazioni = inserisciDestinazione(destinazioni, i, "Torino");
        else if (i == 9)
            destinazioni = inserisciDestinazione(destinazioni, i, "Londra");
        else if (i == 10)
            destinazioni = inserisciDestinazione(destinazioni, i, "Venezia");
        else if (i == 11)
            destinazioni = inserisciDestinazione(destinazioni, i, "Bruxelles");
        else if (i == 12)
            destinazioni = inserisciDestinazione(destinazioni, i, "Parigi");
        else if (i == 13)
            destinazioni = inserisciDestinazione(destinazioni, i, "Berlino");
        else if (i == 14)
            destinazioni = inserisciDestinazione(destinazioni, i, "Barcellona");
        else if (i == 15)
            destinazioni = inserisciDestinazione(destinazioni, i, "Valencia");
        else if (i == 16)
            destinazioni = inserisciDestinazione(destinazioni, i, "Lisbona");
        else if (i == 17)
            destinazioni = inserisciDestinazione(destinazioni, i, "Tokyo");
        else if (i == 18)
            destinazioni = inserisciDestinazione(destinazioni, i, "Rio");
        else if (i == 19)
            destinazioni = inserisciDestinazione(destinazioni, i, "Nairobi");
    }

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
        destinazioni->next = eliminaDestinazione(destinazioni->next, citt�);
    }
    return destinazioni;
}

//funzione che ricerca una destinazione e restituisce il valore numerico associato
int ricercaDestinazionePerCitt�(list* destinazioni, char* citt�) {
    int trovato = -1;
    if (destinazioni != NULL) {
        if (strcmp(destinazioni->citt�, citt�) == 0)
            return destinazioni->n;
        else
            trovato = ricercaDestinazionePerCitt�(destinazioni->next, citt�);
    }
    return trovato;
}

//funzione che ricerca una destinazione e restituisce il nome della citt� associato
char* ricercaDestinazionePerNodo(list* destinazioni, int n) {
    char* citt� = NULL;
    if (destinazioni != NULL) {
        if (destinazioni->n == n) {
            citt� = (char*)calloc(maxstring, sizeof(char));
            strcpy(citt�, destinazioni->citt�);
            return citt�;
        }
        else
            citt� = ricercaDestinazionePerNodo(destinazioni->next, n);
    }

    return citt�;
}

//funzione che stampa gli elementi della lista
void stampaLista(list* destinazioni) {
    if (destinazioni != NULL) {
        printf("%s\n", destinazioni->citt�);
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