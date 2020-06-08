#ifndef Dijkstra
#define Dijkstra
#include "definers.h"
#include "codePriorità.h"
#include "graphlib.h"

//Dijkstra per il percorso minimo basato sul peso economico
void Dijkstra_Economy(Graph G, int s, int padre[], int d[]);

//Dijkstra per il percorso minimo basato sul peso distanza
void Dijkstra_Distanza(Graph G, int s, int padre[], int d[]);


#endif
