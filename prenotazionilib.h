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

//definizione struttura conflitti prenotazioni attive causa rimozione tratta/destinazione
typedef struct conflictType {
    char motivo[maxstring];
    char citt‡Partenza[maxstring];
    destinazione* dest;
    struct conflictType* next;
} conflitto;

//definizione nodi del percorso minimo
typedef struct pathType {
    int node;
    struct pathType* next;
} path;

//creazione nodo dei conflitti
conflitto* initConflitto(char* motivo, char* city, prenotazione* dest);

//funzione che crea la lista dei conflitti per utente in seguito a rimozione citt‡
conflitto* ConflittiCitt‡(prenotazione* UserList, char* motivo, char* city);

//funzione che crea la lista dei conflitti per utente in seguito a rimozione tratta
conflitto* ConflittiTratta(prenotazione* UserList, char* motivo, char* citt‡1, char* citt‡2);

//funzione che stampa la lista dei conflitti per utente
void stampaConflitto(conflitto* disdette);

//funzione che elimina totalmente la lista conflitti
void cancellaConflitti(conflitto* list);

//estrazione del percorso dal vettore padre
path* extractPath(int padre[], int partenza, int finale);

//crezione del nodo del percorso minimo
path* initPath(int node);

//stampa dei nodi del percorso minimo
void printPath(path* path, list* destinazioni);

//funzione per la creazione prenotazione sulla base economica
prenotazione* creaPrenotazioneEconomy(path* patheco, int partenza, int finale, list* destinazioni, int ecoTot, Graph G);

//funzione per la creazione prenotazione sulla base distanza
prenotazione* creaPrenotazioneDistance(path* pathdist, int partenza, int finale, list* destinazioni, int distTot, Graph G);

//funzione per la creazione delle destinazioni nella prenotazione
destinazione* creaDestinazione(int startnode, path* pathstart, list* destinazioni, Graph G);

//crezione del nodo destinazione della prenotazione
destinazione* initDestinazione(edge arc, list* destinazioni);

//utility per la ricerca nella crezione del nodo destinazione
edge trovaArco(edge list, int target);

//aggiunge in coda alla lista delle destinazioni
void addonTail(destinazione* head, edge nodetarget, list* destinazioni);

//calcola la distanza totale nel caso di una prenotazione su base economica
int sommaDist(destinazione* list);

//calcola il costo totale nel caso di una prenotazione su base distanza
int sommaEconomy(destinazione* list);

//stampa delle prenotazioni di un utente
void printPrenotazioni(prenotazione* listaPrenot);

//stampa delle destinazioni di una prenotazione
void printDestinazioni(destinazione* list);

//funzione che aggiunge una prenotazione alla lista prenotazioni dell utente
prenotazione* addPrenotazione(prenotazione* UserList, prenotazione* new);

//funzione che controlla se la citt‡ rimossa facesse parte di una prenotazione
int ricercaPerRemovePrenotazioneCitt‡(prenotazione* dest, char* city);

//rimozione della prenotazione a seguito di una citt‡ rimossa
prenotazione* removePrenotazioneCitt‡(prenotazione* UserList, char* city);

//funzione che controlla se la tratta rimossa facesse parte di una prenotazione
int ricercaPerRemovePrenotazioneTratta(prenotazione* dest, char* citt‡1, char* citt‡2);

//rimozione della prenotazione a seguito di una tratta rimossa
prenotazione* removePrenotazioneTratta(prenotazione* UserList, char* citt‡1, char* citt‡2);

#endif