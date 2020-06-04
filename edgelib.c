#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "edgelib.h"

//stampa lista di adiacenza
void printList(edge L, list* destinazioni) {
    if (L != NULL) {
        printf("%s Costo: %d Distanza: %d -> ", ricercaDestinazionePerNodo(destinazioni, L->key),L->pesoEconomy, L->pesoDistanza);
        printList(L->next,destinazioni);
    }
}

//rimuove le occorenze del nodo rimosso dalle liste di adiacenza
edge checkListRemoval(edge L, int node_to_remove) {
    if (L != NULL) {
        L->next = checkListRemoval(L->next, node_to_remove);
        if (L->key == node_to_remove) {
            edge tmp = L->next;
            free(L);
            return tmp;
        }
        else if (L->key > node_to_remove) {
            L->key -= 1;
        }
    }
    return L;
}

//inizializza un nodo della lista di adiacenza
edge initNodeList(int info, int eco, int dist) {
    edge L = (edge)malloc(sizeof(struct edgeType));
    L->key = info;
    L->pesoEconomy = eco;
    L->pesoDistanza = dist;
    L->next = NULL;
    return L;
}


edge randomList(int index, int mod) {
    edge L = NULL;
    int i = 0;
    for (i = 0; i < index; i++) {
        L = appendNodeList(L, rand() % mod, rand() % mod, rand() % mod);
    }
    return L;
}

//inserisce un nodo in coda alla lista di adiacenza
edge appendNodeList(edge L, int target, int eco, int dist) {
    if (L != NULL) {
        if (L->key != target) {
            L->next = appendNodeList(L->next, target, eco, dist);
        }
    }
    else {
        L = initNodeList(target, eco, dist);
    }
    return L;
}

//inserisce un nodo in testa alla lista di adiacenza
edge addNodeHead(edge L, int target, int eco, int dist) {
    if (L != NULL) {
        edge G = (edge)malloc(sizeof(struct edgeType));
        G->key = target;
        L->pesoEconomy = eco;
        L->pesoDistanza = dist;
        G->next = L;
        return G;
    }
    return initNodeList(target, eco, dist);
}

//rimuove la lista di adiacenza di un nodo
edge removeNodeList(edge L, int target) {
    if (L != NULL) {
        if (L->key == target) {
            edge tmp = L->next;
            free(L);
            return tmp;
        }
        L->next = removeNodeList(L->next, target);
    }
    return L;
}

//dealloca una lista
void freeList(edge L) {
    if (L != NULL) {
        freeList(L->next);
        free(L);
    }
}

//restituisce la dimensione della lista di adiacenza
int DimLista(edge L) {
    if (L == NULL)
        return 0;
    return 1 + DimLista(L->next);
}