#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utentilib.h"

//funzione aggiunta nodo utente nell'ABR utenti
void addNodoUtente(Utente** radUtente, char* nome, char* password) {
    if (!(*radUtente)) { // se radUtente è vuoto creo il nodo e lo imposto come radUtente
        Utente* aux = (Utente*)malloc(sizeof(Utente));
        strcpy(aux->nomeUtente, nome);
        strcpy(aux->pswd, password);
        aux->dx = NULL;
        aux->sx = NULL;
        aux->prenotazioniUtente = NULL;
        *radUtente = aux;
        return;
    }
    else if (strcmp((*radUtente)->nomeUtente, nome) < 0) {     // se il nome in radice è più piccolo di "nome"
        addNodoUtente(&(*radUtente)->dx, nome, password);
    }          // vado nel sottoalbero destro
    else if (strcmp((*radUtente)->nomeUtente, nome) > 0) {       // se il nome in radice è più grande di "nome"
        addNodoUtente(&(*radUtente)->sx, nome, password);
    }          // vado nel sottoalbero sinistro
}

//funzione di rimozione nodo utente nell'ABR utenti
void eliminaNodoUtente(Utente** radUtente, char* nome) {
    Utente* aux;
    aux = *radUtente;
    if (*radUtente) {
        if (strcmp((*radUtente)->nomeUtente, nome) > 0) {
            eliminaNodoUtente(&(*radUtente)->sx, nome);
        } // CERCA A SINISTRA
        else if (strcmp((*radUtente)->nomeUtente, nome) < 0) {
            eliminaNodoUtente(&(*radUtente)->dx, nome);
        } // CERCA A DESTRA
        else { // ELEMENTO TROVATO
            if (!((*radUtente)->sx) && !((*radUtente)->dx)) {
                free(*radUtente);
                *radUtente = NULL;
            }
            else if (((*radUtente)->sx) && (!((*radUtente)->dx))) { //se dx è vuoto
                *radUtente = aux->sx;
            }
            else if ((!((*radUtente)->sx)) && ((*radUtente)->dx)) { // se sx è vuoto
                *radUtente = aux->dx;
            }
            else if ((aux->dx == NULL) || (aux->sx == NULL)) {
                free(aux);
                return;
            }
            else if (((*radUtente)->sx) && ((*radUtente)->dx)) { // se sx e dx non vuoti
                strcpy((*radUtente)->nomeUtente, ricercaMinUtente((*radUtente)->dx));
                eliminaNodoUtente(&(*radUtente)->dx, (*radUtente)->nomeUtente);
            }
        }
    }
}

//funzione di ricerca del minimo nodo dell'ABR utenti (ordinamento alfanumerico ASCII)
char* ricercaMinUtente(Utente* radUtente) {
    char min[maxstring];
    if (radUtente) {
        if (radUtente->sx == NULL)
            strcpy(min, radUtente->nomeUtente);
        else
            strcpy(min, ricercaMinUtente(radUtente->sx));
    }
    return min;
}

//funzione di ricerca utente, restituzione booleano
int ricercaUtente(Utente* radUtente, char* nome) {
    int trovato = 0;
    if (radUtente) {
        if (strcmp(radUtente->nomeUtente, nome) == 0)
            return 1;
        else if (strcmp(radUtente->nomeUtente, nome) < 0)
            trovato = ricercaUtente(radUtente->dx, nome);
        else if (strcmp(radUtente->nomeUtente, nome) > 0)
            trovato = ricercaUtente(radUtente->sx, nome);
    }
    return trovato;
}

//funzione di controllo correttezza della password, restituzione booleano
int controlloPassw(Utente* radUtente, char* nome, char* password) {
    int corretto = 0;
    if (radUtente) {
        if (strcmp(radUtente->nomeUtente, nome) == 0)
            if (strcmp(radUtente->pswd, password) == 0)
                return 1;
            else if (strcmp(radUtente->nomeUtente, nome) < 0)
                corretto = ricercaUtente(radUtente->dx, nome);
            else if (strcmp(radUtente->nomeUtente, nome) > 0)
                corretto = ricercaUtente(radUtente->sx, nome);
    }
    return corretto;
}

//funzione di ricerca utente, con riferimento all'utente
Utente* referenceUtente(Utente* radUtente, char* nome) {
    Utente* ref = NULL;
    if (radUtente) {
        if (strcmp(radUtente->nomeUtente, nome) == 0) {
            ref = radUtente;
            return ref;
        }
        else if (strcmp(radUtente->nomeUtente, nome) < 0)
            ref = referenceUtente(radUtente->dx, nome);
        else if (strcmp(radUtente->nomeUtente, nome) > 0)
            ref = referenceUtente(radUtente->sx, nome);
    }
    return ref;
}

//funzione visita in Preordine ABR utenti
void visitaInPreOrdineUtenti(Utente* radUtente) {
    if (radUtente) {
        printf("|%s| ", radUtente->nomeUtente);
        visitaInPreOrdineUtenti(radUtente->sx);
        visitaInPreOrdineUtenti(radUtente->dx);
    }
}

//funzione che cancella totalmente l'ABR utenti
void eliminaABR(Utente* radUtente)  {
    if (radUtente != NULL)
        {
            eliminaABR(radUtente->sx);
            eliminaABR(radUtente->dx);
            free(radUtente);
        }
}
//
////funzione per l'aggiunta di un nodo Prenotazione
//prenotazione* AddNodoPrenotazioneToUser(prenotazione *head/*, dati da inserire*/) {
//    if (head == NULL) {
//        head=createPrenotazione();
//    }
//    else {
//
//        head = AddNodoPrenotazioneToUser(head->next);
//    }
//} 