#ifndef prenotazionilib
#define prenotazionilib
#include "definers.h"       //libreria delle costanti definite
#include "graphlib.h"

//definizione struttura lista prenotazioni
typedef struct lista_prenotazioni {
    char citt‡Partenza[maxstring];      //chiave stringa della citt‡ di partenza
    int economyTot;                        //costo economico totale
    int distanzaTot;                       //costo distanza totale
    struct lista_prenotazioni* next;    //puntatore alla prenotazione successiva
    struct lista_destinazioni* dest;    //puntatore alla destinazione
} prenotazione;

//definizione nodi lista di destinazioni
typedef struct lista_destinazioni {
    char citt‡[maxstring];          //chiave stringa della citt‡ di destinazione
    int ecotratt;                        //costo economico tratta
    int disttratt;                      //distanza tratta
    struct lista_destinazioni* next;    //puntatore ad ulteriore destinazione, in caso di scalo
} destinazione;

typedef struct pathType {
    int node;
    struct pathType* next;
} path;

path* extractPath(int padre[], int partenza, int finale);

path* initPath(int node);

void printPath(path* path, list* destinazioni);

edge trovaArco(edge list, int target);

//funzione per la creazione prenotazione
prenotazione* creaPrenotazioneEconomy(path* patheco, int partenza, int finale, list* destinazioni, int ecoTot, Graph G);

prenotazione* creaPrenotazioneDistance(path* pathdist, int partenza, int finale, list* destinazioni, int distTot, Graph G);

destinazione* initDestinazione(edge arc, list* destinazioni);

destinazione* creaDestinazione(int startnode, path* pathstart, list* destinazioni, Graph G);

int sommaDist(destinazione* list);

int sommaEconomy(destinazione* list);

void addonTail(destinazione* head, edge nodetarget, list* destinazioni);

void printPrenotazioni(prenotazione* listaPrenot);

void printDestinazioni(destinazione* list);



#endif