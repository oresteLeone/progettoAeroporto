#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guilib.h"

char catchRequest()
{
    char richiesta, buf[maxstring];

    while(1){
        printf("\nInserisca '0' per il Login\nInserisca '1' per Registrarsi\nInserisca '2' per Chiudere\n ");
        printf("\nCosa vuole fare?: ");
        fgets(buf, maxstring, stdin);

        if (strlen(buf) == 2) {
            richiesta = buf[0];
            break;
        }
        else
            printf("\nRichiesta non valida\n");
    }
    
    
    /*while (scanf("%d", &richiesta) != 1) {
        printf("\nInserisca '0' per il Login\nInserisca '1' per Registrarsi\nInserisca '2' per Chiudere\n ");
        printf("\nCosa vuole fare?: ");
        while (getchar() != '\n');
    }*/

    return richiesta;
}
