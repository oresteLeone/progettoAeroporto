#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

//funzione per ottenere interi in input
int getInteger() {
    char buf[maxstring];
    int res = 0, test;

    do
    {
        test = 0;

        scanf("%s", buf);

        if (!strchr(buf, '\n'))     //newline does not exist
            while (fgetc(stdin) != '\n');//discard until newline
        else {
            size_t len = strlen(buf);
            buf[len - 1] = '\0';
        }

        for (int i = 0; i < strlen(buf); i++) {
            if (isdigit(buf[i]) != 0)
                test++;
        }

        if (test != strlen(buf))
            printf("\nInput non valido, riprova: ");
        else
            res = atoi(buf);

    } while (test != strlen(buf));

    return res;
}

//menù dell'admin
void menuAdmin(Utente* radUtente, Graph G, list** destinazioni) {
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
            clrscr();
            printf("\nAggiunta di una destinazione:\n");
            addNode(G);
            printf("\nInserisca il nome della destinazione: ");
            char tmpname[maxstring]; 
            strcpy(tmpname, getString());
            *destinazioni = inserisciDestinazione(*destinazioni, G->nv-1, tmpname);
            clrscr();
            printf("\nDestinazione %s aggiunta!\n",tmpname);
            break;
        case '2':
            clrscr();
            printf("\nAggiunta di una tratta:\n");
            char partenza[maxstring], arrivo[maxstring];
            int indexP, indexA;
            int eco, dist;
            printf("\nInserire citta' di partenza: ");
            strcpy(partenza, getString());
            indexP = ricercaDestinazionePerCittà(*destinazioni, partenza);
            if (indexP == -1) {
                clrscr();
                printf("\nLa citta non e' presente!\n");
                printf("\nOperazione annullata!\n");
                break;
            }
            printf("\nInserire citta' di arrivo: ");
            strcpy(arrivo, getString());
            indexA = ricercaDestinazionePerCittà(*destinazioni, arrivo);
            if (indexA == -1) {
                clrscr();
                printf("\nLa citta non e' presente!\n");
                printf("\nOperazione annullata!\n");
                break;
            }
            printf("\nCosto Economico: ");
            eco = getInteger();
            //scanf("%d", &eco);
            printf("\nCosto Distanza: ");
            dist = getInteger();
            //scanf("%d", &dist);
            addEdge(G, indexP, indexA, eco, dist);
            //getchar('\n');
            clrscr();
            printf("\nAggiunta tratta %s -> %s costo %d distanza %d\n", partenza, arrivo, eco, dist);
            break;
        case '3':
            clrscr();
            printf("\nRimozione di una destinazione:\n");
            printf("\nInserire citta' da rimuovere: ");
            char city[maxstring];
            strcpy(city, getString());
            int result = ricercaDestinazionePerCittà(*destinazioni, city);
            if (result == -1) {
                clrscr();
                printf("\nNon e' possibile rimuovere la destinazione perche' non presente nell'elenco.\n");
                break;
            }
            clrscr();
            printf("\nDestinazione %s rimossa con successo!\n", city);

            removeNode(G, result);
            radUtente = rimozionePrenotazioneCittà(radUtente, "Rimozione citta'", city);
            *destinazioni = eliminaDestinazione(*destinazioni, city);

            break;
        case '4':
            clrscr();
            printf("\nRimozione di una tratta:\n");
            char partenza2[maxstring], arrivo2[maxstring];
            int indexP2, indexA2;
            printf("\nInserire citta' di partenza: ");
            strcpy(partenza2, getString());
            indexP2 = ricercaDestinazionePerCittà(*destinazioni, partenza2);
            if (indexP2 == -1) {
                clrscr();
                printf("\nLa citta non e' presente!\n");
                break;
            }
            printf("\nInserire citta' di arrivo: ");
            strcpy(arrivo2, getString());
            indexA2 = ricercaDestinazionePerCittà(*destinazioni, arrivo2);
            if (indexA2 == -1) {
                clrscr();
                printf("\nLa citta non e' presente!\n");
                break;
            }
            removeEdge(G, indexP2, indexA2);
            clrscr();
            printf("\nSe la tratta %s -> %s era presente, allora e' stata rimossa.\n", partenza2, arrivo2);
            radUtente = rimozionePrenotazioneTratta(radUtente, "Rimozione tratta", partenza2, arrivo2);

            break;
        case '5':
            clrscr();
            printf("\nUtenti registrati nel sistema:\n\n");
            visitaInPreOrdineUtenti(radUtente);
            break;
        case '6':
            clrscr();
            printf("\nStampa Voli:\n\n");
            printGraph(G, *destinazioni);
            break;
        case '0':
            printf("\nLogout in corso...\n");
            quit = 1;
            clrscr();
            printf("Logout effettuato!\n");
            break;
        default:
            clrscr();
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
    

    while (1)
    {
        printf("\nMenu' Utente %s:\n",User->nomeUtente);
        printf("\nInserisca '1' per visualizzare le sue prenotazioni attive\nInserisca '2' per effettuare una prenotazione");
        printf("\nInserisca '3' per la stampa delle citta'\nInserisca '0' per il Logout\n");

        richiesta = catchRequest();

        switch (richiesta)
        {
        case '1':
            clrscr();
            if (User->disdette == NULL) {
                if (User->prenotazioniUtente != NULL) {
                    printf("\nPrenotazioni attive:");
                    printPrenotazioni(User->prenotazioniUtente);
                }
                else
                    printf("\nNon vi sono prenotazioni attive\n");

            }
            else {
                printf("\nLe seguenti prenotazioni sono state disdette causa la rimozione di una citta'/tratta:\n");
                stampaConflitto(User->disdette);
                cancellaConflitti(User->disdette);
                User->disdette = NULL;

                if (User->prenotazioniUtente != NULL) {
                    printf("\nPrenotazioni attive:");
                    printPrenotazioni(User->prenotazioniUtente);
                }
                else
                    printf("\nNon vi sono prenotazioni attive\n");
            }

            break;
        case '2':
            clrscr();
            printf("\nPrenotazione:\n");
            catchPrenotazione(User, G, destinazioni);

            break;
        case '3':
            clrscr();
            printf("\nLista citta':\n\n");
            stampaLista(destinazioni);
            break;
        case '0':
            printf("\nLogout in corso...\n");
            quit = 1;
            clrscr();
            printf("\nLogout effettuato!\n");
            break;
        default:
            clrscr();
            printf("\nRichiesta non valida\n");
            break;
        }

        if (quit == 1)
            break;
    }
}

//restituisce il nodo con distanza minore
int metaEconomica(edge L)
{
    int meta = -1, min = INT_MAX;

    while (L != NULL) {
        if (min > L->pesoEconomy) {
            min = L->pesoEconomy;
            meta = L->key;
        }

        L = L->next;
    }

    return meta;

    /*for (int i = 0; i < dim; i++) {
        if(d[i] != 0)
            if (min > d[i]) {
                min = d[i];
                meta = i;
            }
    }

    return meta;*/
}

//funzione per la creazione di una prenotazione
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
            clrscr();
            printf("\nLa citta non e' presente!\n");
            printf("\nOperazione annullata...\n");
            break;
        }
        printf("\nInserire citta' di arrivo: ");
        strcpy(arrivo1, getString());
        indexA = ricercaDestinazionePerCittà(destinazioni, arrivo1);
        if (indexA == -1) {
            clrscr();
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
            
            Dijkstra_Economy(G, indexP, padre, d);
            if (padre[indexA]<0 || padre[indexA]>G->nv - 1) {
                clrscr();
                printf("\nNon e' possibile raggiungere la destinazione richiesta!\n");
                printf("\nOperazione Annullata\n");
                break;
            }
            path* patheco = extractPath(padre, indexP, indexA);
            printf("\nIl percorso piu' economico prevede le seguenti tratte: ");
            printPath(patheco, destinazioni);
            prenotazione* tmp = creaPrenotazioneEconomy(patheco, indexP, indexA, destinazioni, d[indexA], G);
            printPrenotazioni(tmp);
            printf("\nInserisca '1' per confermare, '0' per annullare\n");
            confirm = catchRequest();
            if (confirm == '1') {
                if (User->puntiUtente != 0) {
                    printf("\nL'utente ha a disposizione uno sconto di %d,desidera utilizzarlo? ('1'SI / '0'NO)\n", User->puntiUtente);
                    confirm = catchRequest();
                    if (confirm == '1') {
                        if (User->puntiUtente >= tmp->economyTot) {
                            User->puntiUtente -= tmp->economyTot;
                            tmp->economyTot = 0;
                        }
                        else {
                            tmp->economyTot -= User->puntiUtente;
                            User->puntiUtente = 0;
                        }
                            
                        printf("\nLo sconto e' stato applicato!\n");
                    }
                }
                User->prenotazioniUtente = addPrenotazione(User->prenotazioniUtente, tmp);
                clrscr();
                printf("\nPrenotazione Effettuata!\n");
                User->puntiUtente += ((tmp->economyTot) * 5 / 100);

                if(((tmp->economyTot) * 5 / 100) != 0)
                    printf("\nL'utente ha ottenuto un buono sconto di %d!\n", ((tmp->economyTot) * 5 / 100));
                
            }
            else {
                clrscr();
                printf("\nOperazione annullata!\n");
            }
            
        }
        else {
            
            Dijkstra_Distanza(G, indexP, padre, d);
            if (padre[indexA]<0 || padre[indexA]>G->nv - 1) {
                clrscr();
                printf("\nNon e' possibile raggiungere la destinazione richiesta!\n");
                printf("\nOperazione Annullata\n");
                break;
            }
            path* pathdist = extractPath(padre, indexP, indexA);
            printf("\nIl percorso piu' breve prevede le seguenti tratte: ");
            printPath(pathdist, destinazioni);
            prenotazione* tmp = creaPrenotazioneDistance(pathdist, indexP, indexA, destinazioni, d[indexA], G);
            printPrenotazioni(tmp);
            printf("\nInserisca '1' per confermare, '0' per annullare\n");
            confirm = catchRequest();
            if (confirm == '1') {
                if (User->puntiUtente != 0) {
                    printf("\nL'utente ha a disposizione uno sconto di %d,desidera utilizzarlo? ('1'SI / '0'NO)\n",User->puntiUtente);
                    confirm = catchRequest();
                    if (confirm == '1') {
                        if (User->puntiUtente >= tmp->economyTot) {
                            User->puntiUtente -= tmp->economyTot;
                            tmp->economyTot = 0;
                        }
                        else {
                            tmp->economyTot -= User->puntiUtente;
                            User->puntiUtente = 0;
                        }
                        printf("\nLo sconto e' stato applicato!\n");
                    }
                }
                User->prenotazioniUtente=addPrenotazione(User->prenotazioniUtente, tmp);
                clrscr();
                printf("\nPrenotazione Effettuata!\n");
                User->puntiUtente += ((tmp->economyTot) * 5 / 100);

                if (((tmp->economyTot) * 5 / 100) != 0)
                    printf("\nL'utente ha ottenuto un buono sconto di %d!\n", ((tmp->economyTot) * 5 / 100));
                
            }
            else {
                clrscr();
                printf("\nOperazione annullata!\n");
            }
                
        }
        
        break;
    case '2':
        printf("\nInserire citta' di partenza: ");
        strcpy(partenza1, getString());
        indexP = ricercaDestinazionePerCittà(destinazioni, partenza1);
        if (indexP == -1) {
            clrscr();
            printf("\nLa citta non e' presente!");
            printf("\nOperazione annullata!\n");
            break;
        }

        printf("\nInserisca '1' per la meta piu' economica\nInserisca '2' per la meta piu' gettonata\n");

        do {
            meta = catchRequest();
            if (meta != '1' && meta != '2')
                printf("\nInput non valido!\n");
        } while (meta != '1' && meta != '2');


        if (meta == '1') {
            
            Dijkstra_Economy(G, indexP, padre, d);
            
            indexA = metaEconomica(G->adj[indexP]);

            if (indexA == -1) {
                clrscr();
                printf("\nDalla citta' da lei selezionata non sono previsti voli!\n");
                printf("\nOperazione annullata!\n");
                break;
            }

            path* patheco = extractPath(padre, indexP, indexA);
            printf("\nLa meta piu' economica prevede le seguenti tratte: ");
            printPath(patheco, destinazioni);
            prenotazione* tmp = creaPrenotazioneEconomy(patheco, indexP, indexA, destinazioni, d[indexA], G);
            printPrenotazioni(tmp);
            printf("\nInserisca '1' per confermare, '0' per annullare\n");
            confirm = catchRequest();
            if (confirm == '1') {
                if (User->puntiUtente != 0) {
                    printf("\nL'utente ha a disposizione uno sconto di %d,desidera utilizzarlo? ('1'SI / '0'NO)\n", User->puntiUtente);
                    confirm = catchRequest();
                    if (confirm == '1') {
                        if (User->puntiUtente >= tmp->economyTot) {
                            User->puntiUtente -= tmp->economyTot;
                            tmp->economyTot = 0;
                        }
                        else {
                            tmp->economyTot -= User->puntiUtente;
                            User->puntiUtente = 0;
                        }
                        printf("\nLo sconto e' stato applicato!\n");
                    }
                }
                User->prenotazioniUtente = addPrenotazione(User->prenotazioniUtente, tmp);
                clrscr();
                printf("\nPrenotazione Effettuata!\n");
                User->puntiUtente += ((tmp->economyTot) * 5 / 100);
                
                if (((tmp->economyTot) * 5 / 100) != 0)
                    printf("\nL'utente ha ottenuto un buono sconto di %d!\n", ((tmp->economyTot) * 5 / 100));

            }
            else {
                clrscr();
                printf("\nOperazione annullata!\n");
            }
        }
        else {
            
            int* ArrayInDegree = (int*)malloc(sizeof(int) * G->nv);
            ArrayInDegree = gradiEntranti(G, ArrayInDegree);
            indexA = nodeMaxInDegree(ArrayInDegree, G->nv);
            if (indexA == indexP) {
                clrscr();
                printf("\nLa citta' di partenza risulta essere la meta più gettonata! Operazione annullata!\n");
                break;
            }
            Dijkstra_Distanza(G, indexP, padre, d);
            if (padre[indexA]<0 || padre[indexA]>G->nv - 1) {
                clrscr();
                printf("\nDalla citta' di partenza non e' possibile raggiungere la meta gettonata!\n");
                printf("\nOperazione annullata!\n");
                break;
            }
            path* pathdist = extractPath(padre, indexP, indexA);
            printf("\nIl percorso piu' breve per la meta gettonata prevede le seguenti tratte: ");
            printPath(pathdist, destinazioni);
            prenotazione* tmp = creaPrenotazioneDistance(pathdist, indexP, indexA, destinazioni, d[indexA], G);
            printPrenotazioni(tmp);
            printf("\nInserisca '1' per confermare, '0' per annullare\n");
            confirm = catchRequest();
            if (confirm == '1') {
                if (User->puntiUtente != 0) {
                    printf("\nL'utente ha a disposizione uno sconto di %d,desidera utilizzarlo? ('1'SI / '0'NO)\n", User->puntiUtente);
                    confirm = catchRequest();
                    if (confirm == '1') {
                        if (User->puntiUtente >= tmp->economyTot) {
                            User->puntiUtente -= tmp->economyTot;
                            tmp->economyTot = 0;
                        }
                        else {
                            tmp->economyTot -= User->puntiUtente;
                            User->puntiUtente = 0;
                        }
                        printf("\nLo sconto e' stato applicato!\n");
                    }
                }
                User->prenotazioniUtente = addPrenotazione(User->prenotazioniUtente, tmp);
                clrscr();
                printf("\nPrenotazione Effettuata!\n");
                User->puntiUtente += ((tmp->economyTot) * 5 / 100);
                
                if (((tmp->economyTot) * 5 / 100) != 0)
                    printf("\nL'utente ha ottenuto un buono sconto di %d!\n", ((tmp->economyTot) * 5 / 100));
            }
            else {
                clrscr();
                printf("\nOperazione annullata!\n");
            }

        }
        
        break;
    case '0':
        clrscr();
        printf("\nOperazione annullata!\n");
        break;
    default:
        clrscr();
        printf("\nRichiesta non valida\n");
        break;
    }

}

