#ifndef gui
#define gui
#include "definers.h"
#include "utentilib.h"

//funzione per ottenere le richieste di un singolo carattere in input
char catchRequest();

//funzione per ottenere le stringhe in input
char* getString();

//men� dell'admin
void menuAdmin(Utente* radUtente);

//men� dell'utente
void menuUtente();

#endif
