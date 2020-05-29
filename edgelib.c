#include <stdio.h>
#include <stdlib.h>
#include <string.h>
<<<<<< < HEAD
#include "edgelib.h"

    edge initNodeList(int info, int pesoEco, int pesoDis) {
    edge E = malloc(sizeof(struct edgeType));
    E->key = info;
    E->pesoEconomy = pesoEco;
    E->pesoDistanza = pesoDis;
    E->next = NULL;
    return E;
}



edge appendNodeList(List L, int target, int pesoEco, int pesoDis) {
    if (E != NULL) {
        if (E->key != target) {
            E->next = appendNodeList(E->next, target, pesoEco, pesoDis);
        }
    }
    else {
        E = initNodeList(target, pesoEco, pesoDis);
    }
    return E;
}

edge addNodeHead(edge E, int target, int pesoEco, int pesoDis) {
    if (E != NULL) {
        edge G = malloc(sizeof(struct edgeType));
        G->key = target;
        G->pesoEconomy = pesoEco;
        G->pesoDistanza = pesoDis;
        G->next = E;
        return G;
    }
    return initNodeList(target, pesoEso, pesoDis);
}

edge addNodeTail(edge E, int target, int pesoEco, int pesoDis) {
    if (E != NULL) {
        if (E->next == NULL) {
            List G = malloc(sizeof(struct edgeType));
            G->next = NULL;
            G->key = target;
            G->pesoEconomy = pesoEco;
            G->pesoDistanza = pesoDis;
            E->next = G;
            return E;
        }
        addNodeTail(E->next, target, pesoEco, pesoDis);
    }
}

edge removeNodeList(edge E, int target) {
    if (E != NULL) {
        if (E->key == target) {
            edge tmp = E->next;
            free(E);
            return tmp;
        }
        L->next = removeNodeList(L->next, target);
    }
    return E;
}


edge removeHead(edge E) {
    if (E != NULL) {

        edge tmp = E->next;
        free(E);
        return tmp;

    }
}


edge removeTail(edge E) {
    if (E != NULL) {
        if (E->next != NULL) {

            if (E->next->next == NULL) {
                E->next = NULL;
                free(E->next);
                return E;
            }

        }
        else {
            free(E);
            return NULL;
        }
        removeTail(E->next);
    }
}



void freeList(edge E) {
    if (E != NULL) {
        freeList(E->next);
        free(E);