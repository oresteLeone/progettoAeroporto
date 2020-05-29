#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listlib.h"

//funzione che inserisce una nuova destinazione nella lista
list* inserisciDestinazione(list* destinazioni, int n, char* città) {
    if (!destinazioni) { // se destinazioni è vuoto creo il nuovo elemento e lo imposto come destinazioni
        list* aux = (list*)malloc(sizeof(list));
        aux->n = n;
        strcpy(aux->città, città);
        aux->next = NULL;
        destinazioni = aux;
    }
    else
        destinazioni->next = inserisciDestinazione(destinazioni->next, n, città);

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

list* eliminaDestinazione(list* destinazioni, char* città) {
    if (destinazioni != NULL) {
        if (strcmp(destinazioni->città, città) == 0) {
            list* tmp = destinazioni->next;
            free(destinazioni);
            tmp = decrementaNodi(tmp);
            return tmp;
        }
        destinazioni = eliminaDestinazione(destinazioni->next, città);
    }
    return destinazioni;
}

//funzione che ricerca una destinazione e restituisce il valore numerico associato
int ricercaDestinazionePerCittà(list* destinazioni, char* città) {
    int trovato = -1;
    if (destinazioni != NULL) {
        if (strcmp(destinazioni->città, città) == 0)
            return destinazioni->n;
        else
            trovato = ricercaDestinazionePerCittà(destinazioni->next, città);
    }
    return trovato;
}

//funzione che ricerca una destinazione e restituisce il nome della città associato
char* ricercaDestinazionePerNodo(list* destinazioni, int n) {
    char* città = NULL;
    if (destinazioni != NULL) {
        if (destinazioni->n == n) {
            città = (char*)calloc(maxstring, sizeof(char));
            strcpy(città, destinazioni->città);
            return città;
        }
        else
            città = ricercaDestinazionePerNodo(destinazioni->next, n);
    }

    return città;
}

//funzione che stampa gli elementi della lista
void stampaLista(list* destinazioni) {
    if (destinazioni != NULL) {
        printf("\nNodo associato: %d ", destinazioni->n);
        printf("Citta': %s\n", destinazioni->città);
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