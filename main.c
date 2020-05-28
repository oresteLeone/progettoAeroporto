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
					do {
						printf("Salve, per registrarsi inserisca un username:\n");
						scanf("%s", user);
						flag = ricercaUtente(radUtente, user);        //mi passo l'user appena inserito per controllare se è disponibile
						if (flag == 1)
							printf("Nome utente non disponibile. Riprovi:\n");
						else
							printf("Ok! Ora inserisca una password:\n");
					} while (flag != 0);
					scanf("%s", passwd);
					printf("Perfetto! Registrazione completata. Sta per essere reindirizzato alla schermata principale...\n");

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

