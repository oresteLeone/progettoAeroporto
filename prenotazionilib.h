#ifndef prenotazionilib
#define prenotazionilib
#include "definers.h"       //libreria delle costanti definite

//definizione struttura lista prenotazioni
typedef struct lista_prenotazioni {
    char citt‡Partenza[maxstring];      //chiave stringa della citt‡ di partenza
    struct lista_prenotazioni* next;    //puntatore alla prenotazione successiva
    struct lista_destinazioni* dest;    //puntatore alla destinazione
} prenotazione;

//definizione nodi lista di destinazioni
typedef struct lista_destinazioni {
    char citt‡[maxstring];          //chiave stringa della citt‡ di destinazione
    int economy;                    //costo economico tratta
    int distanza;                   //costo distanza tratta
    struct lista_destinazioni* next;    //puntatore ad ulteriore destinazione, in caso di scalo
} destinazione;

////funzione per la creazione della prenotazione
//prenotazione* createPrenotazione();

#endif