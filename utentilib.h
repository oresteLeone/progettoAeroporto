#ifndef utentilib
#define utentilib
#include "prenotazionilib.h"    //libreria delle prenotazioni
#include "definers.h"           //libreria delle costanti definite

//definizione struttura ABR Utenti
typedef struct nodo_utente {
    char nomeUtente[maxstring];         //chiave stringa del nodo utente
    int pswd;            //password dell'utente
    prenotazione* prenotazioniUtente;   //puntatore alla lista prenotazioni 

    //puntatori ai sottoalberi destro e sinistro
    struct nodo_utente* sx;
    struct nodo_utente* dx;
} Utente;


void addNodoUtente(Utente** radUtente, char* nome, int password);

void eliminaNodoUtente(Utente** rad, char* nome);

char* ricercaMinUtente(Utente* radUtente);


#endif