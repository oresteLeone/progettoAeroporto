#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utentilib.h"

void addNodoUtente(Utente** radUtente, char* nome, int password) {
    if (!(*radUtente)) { // se radUtente è vuoto creo il nodo e lo imposto come radUtente
        Utente* aux = (Utente*)malloc(sizeof(Utente));
        strcpy(aux->nomeUtente, nome);
        aux->pswd = password;
        aux->dx = NULL;
        aux->sx = NULL;
        aux->prenotazioniUtente = NULL;
        *radUtente = aux;
        return;
    }
    else if (strcmp((*radUtente)->nomeUtente, nome) < 0) {     // se il nome in radice è più piccolo di "nome"
        addNodoLibro(&(*radUtente)->dx, nome);
    }          // vado nel sottoalbero destro
    else if (strcmp((*radUtente)->nomeUtente, nome) > 0) {       // se il nome in radice è più grande di "nome"
        addNodoLibro(&(*radUtente)->sx, nome);
    }          // vado nel sottoalbero sinistro
}

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
                eliminaNodoABRStudente(&(*radUtente)->dx, (*radUtente)->nomeUtente);
            }
        }
    }
}

char* ricercaMinUtente(Utente* radUtente) {

}