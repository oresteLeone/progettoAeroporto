#include <stdio.h>
#include <stdlib.h>
#include "codePriorit�.h"

void initCodaPriorit�(CP* p, int n) {
    p->capacita = n;
    p->dim = CPVUOTA;
    p->H = (nodoCP*)malloc(n * sizeof(nodoCP));
}

void cancellaCodaPriorit�(CP cp) {
    free(cp.H);
}

int EmptyCodaPriorit�(CP cp) {
    int res = 0;

    if (cp.dim == CPVUOTA)
        res = 1;

    return res;
}

int FullCodaPriorit�(CP cp) {
    int res = 0;

    if (cp.dim == cp.capacita)
        res = 1;

    return res;
}

int MinCodaPriorit�(CP cp) {
    if (EmptyCodaPriorit�(cp) == 0)
        return(cp.H[0].valore);
}

void scambio(nodoCP v[], int i, int j) {
    nodoCP tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
    v[i].posizione = i;
    v[j].posizione = j;
}

void InsertMinCodaPriorit�(CP* p, int x, int pr) {
    nodoCP tmp;
    int i;

    if (FullCodaPriorit�(*p) == 0) {
        i = p->dim;
        p->dim = p->dim + 1;

        tmp.valore = x;
        tmp.priorita = pr;
        tmp.posizione = i;

        p->H[i] = tmp;

        while (i > 0 && p->H[i].priorita < p->H[(i - 1) / 2].priorita) {
            scambio(p->H, i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }
}


void minHeapRestore(nodoCP v[], int i, int n) {
    int min = i;

    if (2 * i + 1 < n && v[2 * i + 1].priorita < v[min].priorita) min = 2 * i + 1;
    if (2 * i + 2 < n && v[2 * i + 2].priorita < v[min].priorita) min = 2 * i + 2;
    if (i != min) {
        scambio(v, i, min);
        minHeapRestore(v, min, n);
    }
}


int DeleteMinCodaPriorit�(CP* p) {

    if (EmptyCodaPriorit�(*p) == 0) {
        p->dim = p->dim - 1;
        scambio(p->H, 0, p->dim);
        minHeapRestore(p->H, 0, p->dim);
        return p->H[p->dim].valore;
    }
}

void DecreaseKeyMinCodaPriorit�(CP* p, int x, int pr) {

    int i;

    if (EmptyCodaPriorit�(*p) == 0)
        for (i = 0; i < p->dim; i++)
            if (p->H[i].valore == x) {
                if (p->H[i].priorita > pr) {
                    p->H[i].priorita = pr;
                    while (i > 0 && p->H[i].priorita < p->H[(i - 1) / 2].priorita) {
                        scambio(p->H, i, (i - 1) / 2);
                        i = (i - 1) / 2;
                    }
                }
                break;
            }
}
