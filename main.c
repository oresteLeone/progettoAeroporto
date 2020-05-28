#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definers.h"
#include "graphlib.h"
#include "utentilib.h"
#include "guilib.h"

int main() {
	char string[maxstring];
	char richiesta;
	int quit = 0;
	char* user, passwd; 
	int flag = 0;
	
	do {
			printf("\nInserisca '1' per il Login\nInserisca '2' per Registrarsi\nInserisca '0' per Chiudere\n ");
			richiesta = catchRequest();
			user = (char*)malloc(sizeof(char) * 20);
			passwd = (char*)malloc(sizeof(char) * 20);

			switch (richiesta) {
				case '1':
					printf("\nLogin...\n");
					printf("inserisci nome utente: ");
					strcpy(string, getString());
					printf("\nStringa inserita: %s lunghezza:%d ", string, strlen(string));
					break;
				case '2':
					printf("Salve, per registrarsi inserisca un username:\n");
					scanf("%s", user);

					break;
				case '0':
					printf("\nChiusura in corso...\n");
					quit = 1;
					break;
				default:
					printf("\nRichiesta non valida\n");
					break;
			}
	} while (quit != 1);

	return 0;
}

