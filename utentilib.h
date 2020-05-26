#ifndef utentilib
#define utentilib
#include "prenotazionilib.h"    //libreria delle prenotazioni
#include "definers.h"           //libreria delle costanti definite

//definizione struttura ABR Utenti
typedef struct nodo_utente {
    char nomeUtente[maxstring];         //chiave stringa del nodo utente
    // char pswd[maxstring];            //password dell'utente
    prenotazione* prenotazioniUtente;   //puntatore alla lista prenotazioni 

    //puntatori ai sottoalberi destro e sinistro
    struct nodo_utente* sx;
    struct nodo_utente* dx;
} Utente;

#endif