#ifndef gui
#define gui
#include "definers.h"
#include "utentilib.h"
#include "graphlib.h"

//Pulisce l'output
void clrscr();

//funzione per ottenere le richieste di un singolo carattere in input
char catchRequest();

//funzione per ottenere le stringhe in input
char* getString();

//menù dell'admin
void menuAdmin(Utente* radUtente, Graph G, list* destinazioni);

//menù dell'utente
void menuUtente();

#endif
