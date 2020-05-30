#include <stdio.h>
#include <stdlib.h>
#include "codePriorità.h"
#include "graphlib.h"
#include "Dijkstra.h"

/*Strutture Dati Necessarie all'Algoritmo di Dijkstra*/
/*Vengono usati due vettori di dimensione n, ossia numero di vertici*/
/*Ogni vettore ha come indice, l'indice del vertice */
/*Vettore d[n]: contiene per ogni vertice la distanza minima dalla sorgente s*/
/*Vettore padre[n]: e' l'albero dei cammini mimini a partire da s*/
/*Alla fine dell'algoritmo di Dijkstra, il vettore d fornisce per ogni vertice,
il valore della distanza minima dal vertice sorgente s */
/*Il vettore padre, deve essere letto a ritroso a partire da un vertice destinazione*/
/*Ad esempio supponiamo che ci siano 6 vertici nel grafo e si supponga che
il nodo sorgente s sia il vertice 0. Si supponga poi che il vettore padre sia,
alla fine dell'algoritmo di Dijkstra:

    ?,0,0,1,3,4

il punto ? e' stato messo perche' il vertice 0 e' la sorgente.
Il vettore padre deve essere letto come segue. Si supponga si voglia sapere il
cammino minimo dal vertice 0 al vertice 5. Dall'elemento di indice 5 si
viene a sapere che il padre di 5 e' il 4. Dall'elemento 4, si viene a
sapere che il padre di 4 e' il 3. Dall'elemento di indice 3 si viene a sapere
che il padre di 3 e' 1, e infine dall'elemento di indice 1 si viene a sapere
che il padre e' il vertice sorgente 0. Dunque il cammino minimo e':
    0, 1, 3, 4, 5
*/

/*i vettori padre e d vengono allocati all'esatta dimensione di n, ossia del
numero di vertici nel grafo*/

//int* padre;
//int* d;

/*L'algoritmo riceve in ingresso un grafo G, un vertice sorgente s,
e fornisce i vettori delle distanze e dell'albero dei cammini minimi a partire
dalla sorgente s */

void Dijkstra_Economy(Graph G, int s, int padre[], int d[]) {

    int u, v;
    CP coda;
    edge p;

    if (G && s < G->nv) {
        for (u = 0; u < G->nv; u++) 
            d[u] = INFINITO;
        d[s] = 0;
        initCodaPriorità(&coda, G->nv);
        InsertMinCodaPriorità(&coda, s, d[s]);
        while (EmptyCodaPriorità(coda) == 0) {
            u = DeleteMinCodaPriorità(&coda);
            p = G->adj[u]; 
            if (p) {
                if (d[p->key] == INFINITO) {
                    InsertMinCodaPriorità(&coda, p->key, d[u] + p->pesoEconomy);
                    d[p->key] = d[u] + p->pesoEconomy;
                    padre[p->key] = u;
                }
                else if (d[u] + p->pesoEconomy < d[p->key]) {
                    DecreaseKeyMinCodaPriorità(&coda, p->key, d[u] + p->pesoEconomy);
                    d[p->key] = d[u] + p->pesoEconomy;
                    padre[p->key] = u;
                }
                while (p->next->next != NULL) {
                    if (d[p->next->key] == INFINITO) {
                        InsertMinCodaPriorità(&coda, p->next->key, d[u] + p->next->pesoEconomy);
                        d[p->next->key] = d[u] + p->next->pesoEconomy;
                        padre[p->next->key] = u;
                    }
                    else if (d[u] + p->next->pesoEconomy < d[p->next->key]) {
                        DecreaseKeyMinCodaPriorità(&coda, p->next->key, d[u] + p->next->pesoEconomy);
                        d[p->next->key] = d[u] + p->next->pesoEconomy;
                        padre[p->next->key] = u;
                    }
                    p = p->next;
                }
            }
        }
        cancellaCodaPriorità(coda);
    }
}

void Dijkstra_Distanza(Graph G, int s, int padre[], int d[]) {

    int u, v;
    CP coda;
    edge p;

    if (G && s < G->nv) {
        for (u = 0; u < G->nv; u++)
            d[u] = INFINITO;
        d[s] = 0;
        initCodaPriorità(&coda, G->nv);
        InsertMinCodaPriorità(&coda, s, d[s]);
        while (EmptyCodaPriorità(coda) == 0) {
            u = DeleteMinCodaPriorità(&coda);
            p = G->adj[u];
            if (p) {
                if (d[p->key] == INFINITO) {
                    InsertMinCodaPriorità(&coda, p->key, d[u] + p->pesoDistanza);
                    d[p->key] = d[u] + p->pesoDistanza;
                    padre[p->key] = u;
                }
                else if (d[u] + p->pesoDistanza < d[p->key]) {
                    DecreaseKeyMinCodaPriorità(&coda, p->key, d[u] + p->pesoDistanza);
                    d[p->key] = d[u] + p->pesoDistanza;
                    padre[p->key] = u;
                }
                while (p->next->next != NULL) {
                    if (d[p->next->key] == INFINITO) {
                        InsertMinCodaPriorità(&coda, p->next->key, d[u] + p->next->pesoDistanza);
                        d[p->next->key] = d[u] + p->next->pesoDistanza;
                        padre[p->next->key] = u;
                    }
                    else if (d[u] + p->next->pesoDistanza < d[p->next->key]) {
                        DecreaseKeyMinCodaPriorità(&coda, p->next->key, d[u] + p->next->pesoDistanza);
                        d[p->next->key] = d[u] + p->next->pesoDistanza;
                        padre[p->next->key] = u;
                    }
                    p = p->next;
                }
            }
        }
        cancellaCodaPriorità(coda);
    }
}