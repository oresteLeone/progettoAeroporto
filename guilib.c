#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guilib.h"

//Pulisce l'output
void clrscr() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif // _WIN32
}

//funzione per ottenere le richieste di un singolo carattere in input
char catchRequest()
{
    char richiesta, buf[maxstring];

    while(1){
        
        printf("\nCosa vuole fare?: ");
        fgets(buf, maxstring, stdin);

        if (strlen(buf) == 2) {
            richiesta = buf[0];
            break;
        }
        else
            printf("\nRichiesta non valida\n");
    }
 
    return richiesta;
}

//funzione per ottenere le stringhe in input
char* getString() {
    char string[maxstring], buf[maxstring];

    while (1) {
        fgets(buf, maxstring, stdin);
        
        if (!strchr(buf, '\n'))     //newline does not exist
            while (fgetc(stdin) != '\n');//discard until newline
        else {
            size_t len = strlen(buf);
            buf[len - 1] = '\0';
        }
        strcpy(string, buf);
        break;   
    }
    return string;
}

//menù dell'admin
void menuAdmin(Utente* radUtente, Graph G, list* destinazioni) {
    char richiesta;
    int quit = 0;

    clrscr();
    printf("\nMenu' Admin:\n");

    while (1)
    {
        printf("\nInserisca '1' per aggiungere una destinazione\nInserisca '2' per aggiungere una tratta\n");
        printf("Inserisca '3' per rimuovere una destinazione\nInserisca '4' per rimuovere una tratta\n");
        printf("Inserisca '5' per visualizzare gli utenti registrati nel sistema\nInserisca '6' per visualizzare i voli disponibili\nInserisca '0' per il Logout\n");

        richiesta = catchRequest();

        switch (richiesta)
        {
        case '1':
            printf("\n-Aggiunta di una destinazione-\n");
            addNode(G);
            printf("Inserisca il nome della destinazione: ");
            char tmpname[maxstring]; 
            strcpy(tmpname, getString());
            destinazioni = inserisciDestinazione(destinazioni, G->nv-1, tmpname);
            break;
        case '2':
            printf("\nAggiunta di una tratta:\n");
            char partenza[maxstring], arrivo[maxstring];
            int indexP, indexA;
            int eco, dist;
            printf("inserire citta' di partenza: ");
            strcpy(partenza, getString());
            indexP = ricercaDestinazionePerCittà(destinazioni, partenza);
            if (indexP == -1) {
                printf("La citta non e' presente!\n");
                break;
            }
            printf("inserire citta' di arrivo: ");
            strcpy(arrivo, getString());
            indexA = ricercaDestinazionePerCittà(destinazioni, arrivo);
            if (indexA == -1) {
                printf("La citta non e' presente!\n");
                break;
            }
            printf("Costo Economico: ");
            scanf("%d", &eco);
            printf("Costo Distanza: ");
            scanf("%d", &dist);
            addEdge(G, indexP, indexA, eco, dist);
            getchar('\n');
            break;
        case '3':
            printf("\n-Rimozione di una destinazione-\n");
            printf("Inserire citta' da rimuovere: ");
            char city[maxstring];
            strcpy(city, getString());
            int result = ricercaDestinazionePerCittà(destinazioni, city);
            if (result == -1) {
                printf("Non è possibile rimuovere la destinazione perche' non esiste.\n");
                break;
            }
            else
                printf("Ok! Destinazione rimossa con successo!\n");

            removeNode(G, result);
            destinazioni = eliminaDestinazione(destinazioni, city);

            break;
        case '4':
            printf("\n-Rimozione di una tratta-\n");
            char partenza2[maxstring], arrivo2[maxstring];
            int indexP2, indexA2;
            printf("Inserire citta' di partenza: ");
            strcpy(partenza2, getString());
            indexP2 = ricercaDestinazionePerCittà(destinazioni, partenza2);
            if (indexP2 == -1) {
                printf("La citta non e' presente!\n");
                break;
            }
            printf("Inserire citta' di arrivo: ");
            strcpy(arrivo2, getString());
            indexA2 = ricercaDestinazionePerCittà(destinazioni, arrivo2);
            if (indexA2 == -1) {
                printf("La citta non e' presente!\n");
                break;
            }
            removeEdge(G, indexP2, indexA2);

            break;
        case '5':
            printf("\nUtenti registrati nel sistema:\n\n");
            visitaInPreOrdineUtenti(radUtente);
            break;
        case '6':
            printf("\nStampa Voli:\n\n");
            printGraph(G, destinazioni);
            break;
        case '0':
            printf("\nLogout in corso...\n");
            quit = 1;
            clrscr();
            printf("Logout effettuato!\n");
            break;
        default:
            printf("\nRichiesta non valida\n");
            break;
        }

        if (quit == 1)
            break;
    }
}

//menù dell'utente
void menuUtente(Utente* User, Graph G, list* destinazioni) {
    char richiesta;
    int quit = 0;

    clrscr();
    printf("\nMenu' Utente:\n");

    while (1)
    {
        printf("\nInserisca '1' per visualizzare le sue prenotazioni attive\nInserisca '2' per effettuare una prenotazione");
        printf("\nInserisca '3' per la stampa delle citta'\nInserisca '0' per il Logout\n");

        richiesta = catchRequest();

        switch (richiesta)
        {
        case '1':
            printf("\nPrenotazioni attive:");
            printPrenotazioni(User->prenotazioniUtente);
            break;
        case '2':
            printf("\nPrenotazione:\n");
            catchPrenotazione(User, G, destinazioni);

            break;
        case '3':
            printf("\nLista citta':\n");
            stampaLista(destinazioni);
            break;
        case '0':
            printf("\nLogout in corso...\n");
            quit = 1;
            clrscr();
            printf("Logout effettuato!\n");
            break;
        default:
            printf("\nRichiesta non valida\n");
            break;
        }

        if (quit == 1)
            break;
    }
}

int metaEconomica(int d[], int dim, int source)
{
    int meta = -1, min = INT_MAX;

    for (int i = 0; i < dim; i++) {
        if(d[i] != 0)
            if (min > d[i]) {
                min = d[i];
                meta = i;
            }
    }

    return meta;
}

void catchPrenotazione(Utente* User, Graph G, list* destinazioni) {
    char mode,confirm, tratt, meta;
    char partenza1[maxstring], arrivo1[maxstring];
    int indexP, indexA;
    int* padre = (int*)malloc(sizeof(int) * G->nv);
    int* d = (int*)malloc(sizeof(int) * G->nv);
    printf("\nInserisca '1' per inserire Partenza e Destinazione\nInserisca '2' per inserire solo Partenza\nInserisca '0' per annullare\n");
    mode = catchRequest();
    switch (mode)
    {
    case '1':
        printf("\nInserire citta' di partenza: ");
        strcpy(partenza1, getString());
        indexP = ricercaDestinazionePerCittà(destinazioni, partenza1);
        if (indexP == -1) {
            printf("\nLa citta non e' presente!\n");
            printf("\nOperazione annullata...\n");
            break;
        }
        printf("\nInserire citta' di arrivo: ");
        strcpy(arrivo1, getString());
        indexA = ricercaDestinazionePerCittà(destinazioni, arrivo1);
        if (indexA == -1) {
            printf("\nLa citta non e' presente!\n");
            printf("\nOperazione annullata...\n");
            break;
        }

        printf("\nInserisca '1' per la tratta piu' economica\nInserisca '2' per la tratta piu' breve\n");
        
        do{
            tratt = catchRequest();
            if (tratt != '1' && tratt != '2')
                printf("\nInput non valido!\n");
        } while (tratt != '1' && tratt != '2');
        if (tratt == '1') {
            printf("\nTRATTA ECONOMICA\n");
            Dijkstra_Economy(G, indexP, padre, d);
            if (padre[indexA]<0 || padre[indexA]>G->nv - 1) {
                printf("\nNon è possibile raggiungere la destinazione richiesta!\n");
                printf("\nOperazione Annullata\n");
                break;
            }
            path* patheco = extractPath(padre, indexP, indexA);
            printf("\nIl percorso prevede le seguenti tratte: ");
            printPath(patheco, destinazioni);
            prenotazione* tmp = creaPrenotazioneEconomy(patheco, indexP, indexA, destinazioni, d[indexA], G);
            printPrenotazioni(tmp);
            printf("\nInserisca '1' per confermare, '0' per annullare\n");
            confirm = catchRequest();
            if (confirm == '1') {
                if (User->puntiUtente != 0) {
                    printf("\nL'utente ha a disposizione uno sconto di %d,desidera utilizzarlo?('1'SI / '0'NO): ", User->puntiUtente);
                    confirm = catchRequest();
                    if (confirm == '1') {
                        tmp->economyTot -= User->puntiUtente;
                        printf("\nLo sconto è stato applicato!\n");
                    }
                }
                User->prenotazioniUtente = addPrenotazione(User->prenotazioniUtente, tmp);
                printf("\nPrenotazione Effettuata!\n");
                User->puntiUtente += ((tmp->economyTot) * 5 / 100);

                if(((tmp->economyTot) * 5 / 100) != 0)
                    printf("\nL'utente ha ottenuto un buono sconto di %d!\n", ((tmp->economyTot) * 5 / 100));
                
            }
            else
                printf("\nOperazione annullata!\n");
            
        }
        else {
            printf("\nTRATTA BREVE \n");
            Dijkstra_Distanza(G, indexP, padre, d);
            if (padre[indexA]<0 || padre[indexA]>G->nv - 1) {
                printf("\nNon è possibile raggiungere la destinazione richiesta!\n");
                printf("\nOperazione Annullata\n");
                break;
            }
            path* pathdist = extractPath(padre, indexP, indexA);
            printf("\nIl percorso prevede le seguenti tratte: ");
            printPath(pathdist, destinazioni);
            prenotazione* tmp = creaPrenotazioneDistance(pathdist, indexP, indexA, destinazioni, d[indexA], G);
            printPrenotazioni(tmp);
            printf("\nInserisca '1' per confermare, '0' per annullare\n");
            confirm = catchRequest();
            if (confirm == '1') {
                if (User->puntiUtente != 0) {
                    printf("\nL'utente ha a disposizione uno sconto di %d,desidera utilizzarlo?\n",User->puntiUtente);
                    confirm = catchRequest();
                    if (confirm == '1') {
                        tmp->economyTot -= User->puntiUtente;
                        printf("\nLo sconto e' stato applicato!\n");
                    }
                }
                User->prenotazioniUtente=addPrenotazione(User->prenotazioniUtente, tmp);
                printf("\nPrenotazione Effettuata!\n");
                User->puntiUtente += ((tmp->economyTot) * 5 / 100);
                printf("\nL'utente ha ottenuto un buono sconto di %d!\n", ((tmp->economyTot) * 5 / 100));
            }
            else
                printf("\nOperazione annullata!\n");
                
        }
        
        break;
    case '2':
        printf("\nInserire citta' di partenza: ");
        strcpy(partenza1, getString());
        indexP = ricercaDestinazionePerCittà(destinazioni, partenza1);
        if (indexP == -1) {
            printf("La citta non e' presente!");
            printf("\nOperazione annullata...\n");
            break;
        }

        printf("\nInserisca '1' per la meta piu' economica\nInserisca '2' per la meta piu' gettonata\n");

        do {
            meta = catchRequest();
            if (meta != '1' && meta != '2')
                printf("\nInput non valido!\n");
        } while (meta != '1' && meta != '2');


        if (meta == '1') {
            printf("\nMETA ECONOMICA\n");
            Dijkstra_Economy(G, indexP, padre, d);
            indexA = metaEconomica(d, G->nv, indexP);

            if (indexA == -1) {
                printf("\nDalla citta' da lei selezionata non sono previsti voli!\n");
                printf("\nOperazione annullata...\n");
                break;
            }

            path* patheco = extractPath(padre, indexP, indexA);
            printf("\nIl percorso prevede le seguenti tratte: ");
            printPath(patheco, destinazioni);
            prenotazione* tmp = creaPrenotazioneEconomy(patheco, indexP, indexA, destinazioni, d[indexA], G);
            printPrenotazioni(tmp);
            printf("\nInserisca '1' per confermare, '0' per annullare\n");
            confirm = catchRequest();
            if (confirm == '1') {
                if (User->puntiUtente != 0) {
                    printf("\nL'utente ha a disposizione uno sconto di %d,desidera utilizzarlo?\n", User->puntiUtente);
                    confirm = catchRequest();
                    if (confirm == '1') {
                        tmp->economyTot -= User->puntiUtente;
                        printf("\nLo sconto e' stato applicato!\n");
                    }
                }
                User->prenotazioniUtente = addPrenotazione(User->prenotazioniUtente, tmp);
                printf("\nPrenotazione Effettuata!\n");
                User->puntiUtente += ((tmp->economyTot) * 5 / 100);
                printf("\nL'utente ha ottenuto un buono sconto di %d!\n", ((tmp->economyTot) * 5 / 100));

            }
            else
                printf("\nOperazione annullata!\n");
        }
        else
            printf("\nMeta piu' gettonata\n");
        
        break;
    case '0':
        printf("\nOperazione annullata...\n");
        break;
    default:
        printf("\nRichiesta non valida\n");
        break;
    }

}