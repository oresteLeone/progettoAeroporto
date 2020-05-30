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

//men� dell'admin
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
            printf("\nAggiunta di una destinazione:\n");
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
            indexP = ricercaDestinazionePerCitt�(destinazioni, partenza);
            if (indexP == -1) {
                printf("La citta non e' presente!\n");
                break;
            }
            printf("inserire citta' di arrivo: ");
            strcpy(arrivo, getString());
            indexA = ricercaDestinazionePerCitt�(destinazioni, arrivo);
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
            int result = ricercaDestinazionePerCitt�(destinazioni, city);
            if (result == -1) {
                printf("Non � possibile rimuovere la destinazione perche' non esiste.\n");
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
            indexP2 = ricercaDestinazionePerCitt�(destinazioni, partenza2);
            if (indexP2 == -1) {
                printf("La citta non e' presente!\n");
                break;
            }
            printf("Inserire citta' di arrivo: ");
            strcpy(arrivo2, getString());
            indexA2 = ricercaDestinazionePerCitt�(destinazioni, arrivo2);
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

//men� dell'utente
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
            printf("\nPrenotazioni attive:\n");
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

void catchPrenotazione(Utente* User, Graph G, list* destinazioni) {
    unsigned int mode,tratt;
    char partenza1[maxstring], arrivo1[maxstring];
    int indexP, indexA;
    int* padre = (int*)malloc(sizeof(int) * G->nv);
    int* d = (int*)malloc(sizeof(int) * G->nv);
    printf("\nInserisca '1' per inserire Partenza e Destinazione\nInserisca '2' per inserire solo Partenza\nInserisca '0' per annullare\n");
    mode = catchRequest();
    switch (mode)
    {
    case '1':
        printf("inserire citta' di partenza: ");
        strcpy(partenza1, getString());
        indexP = ricercaDestinazionePerCitt�(destinazioni, partenza1);
        if (indexP == -1) {
            printf("La citta non e' presente!");
            printf("\nOperazione annullata...\n");
            break;
        }
        printf("inserire citta' di arrivo: ");
        strcpy(arrivo1, getString());
        indexA = ricercaDestinazionePerCitt�(destinazioni, arrivo1);
        if (indexA == -1) {
            printf("La citta non e' presente!");
            printf("\nOperazione annullata...\n");
            break;
        }

        printf("\nInserisca '1' per la tratta piu' economica\nInserisca '2' per la tratta pi� breve\n");
        do{ 
            tratt = catchRequest();
            if (tratt != 1 || tratt != 2)
                printf("input non valido!");
        } while (tratt != 1 || tratt != 2);
        if (tratt == 1) {
            Dijkstra_Economy(G, indexP, padre, d);
            prenotazione* tmp = creaPrenotazioneEconomy(padre, indexP, indexA, destinazioni, d[indexA], G);
            //DA CONTINUARE
        }
        else {

        }
            


        break;
    case '2':
        break;
    case '0':
        printf("\nOperazione annullata...\n");
        break;
    default:
        printf("\nRichiesta non valida\n");
        break;
    }

}