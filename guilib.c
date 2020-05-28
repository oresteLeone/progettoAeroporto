#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guilib.h"

char catchRequest()
{
    char richiesta, buf[maxstring];

    while(1){
        printf("\nInserisca '1' per il Login\nInserisca '2' per Registrarsi\nInserisca '0' per Chiudere\n ");
        printf("\nCosa vuole fare?: ");
        fgets(buf, maxstring, stdin);

        if (strlen(buf) == 0) {
            richiesta = buf[0];
            break;
        }
        else
            printf("\nRichiesta non valida\n");
    }
 
    return richiesta;
}
