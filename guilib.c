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

//men¨ dell'admin
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
            indexP = ricercaDestinazionePerCittÓ(destinazioni, partenza);
            if (indexP == -1) {
                printf("La citta non e' presente!\n");
                break;
            }
            printf("inserire citta' di arrivo: ");
            strcpy(arrivo, getString());
            indexA = ricercaDestinazionePerCittÓ(destinazioni, arrivo);
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
            printf("\nRimozione di una destinazione:\n");
            break;
        case '4':
            printf("\nRimozione di una tratta\n");
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

//men¨ dell'utente
void menuUtente() {
    char richiesta;
    int quit = 0;

    clrscr();
    printf("\nMenu' Utente:\n");

    while (1)
    {
        printf("\nInserisca '1' per visualizzare le sue prenotazioni attive\nInserisca '2' per effettuare una prenotazione\n");
        printf("Inserisca '0' per il Logout\n");

        richiesta = catchRequest();

        switch (richiesta)
        {
        case '1':
            printf("\nPrenotazioni attive:\n");
            break;
        case '2':
            printf("\nPrenotazione:\n");
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