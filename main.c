#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definers.h"
#include "graphlib.h"
#include "utentilib.h"
#include "guilib.h"
#include "listlib.h"

int main() {
	char nomeUtente[maxstring], passw[maxstring];
	char richiesta;
<<<<<<< HEAD
	int quit = 0;
	char* user, passwd; 
	int flag = 0;
	edge E = NULL; 
	
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
=======
	int quit = 0, flag = 0;
	Utente* radUtente = NULL;
	
	addNodoUtente(&radUtente, "_System", "admin");

	do 
	{
		printf("\nInserisca '1' per il Login\nInserisca '2' per Registrarsi\nInserisca '0' per Chiudere\n ");
		richiesta = catchRequest();

		switch (richiesta) 
		{
			case '1':
				printf("\nLogin:\n");

				printf("\nNome utente: ");
				strcpy(nomeUtente, getString());

				if (ricercaUtente(radUtente, nomeUtente) != 1)
					printf("\nIl suo nome utente non e' presente tra gli utenti registrati!\n");
				else
				{
					while (1)
					{
						printf("\nPassw: ");
						strcpy(passw, getString());
						if (controlloPassw(radUtente, nomeUtente, passw) == 1)
							break;
>>>>>>> c6968a508f2372a676959358157f71d081cffaf9
						else
							printf("\nPassword errata! Riprovi!\n");
					}

					if (strcmp(nomeUtente, "_System") == 0)
						menùAdmin(radUtente);
					else
						menùUtente();
				}

				break;
			case '2':
				do 
				{
					printf("\nSalve, per registrarsi inserisca un username: ");
					strcpy(nomeUtente, getString());
					flag = ricercaUtente(radUtente, nomeUtente);
					if (flag == 1)
						printf("Nome utente non disponibile. Riprovi:\n");
					else
						printf("\nOk! Ora inserisca una password: ");
				} while (flag != 0);
				strcpy(passw, getString());

				addNodoUtente(&radUtente, nomeUtente, passw);

				printf("\nPerfetto! Registrazione completata. Sta per essere reindirizzato alla schermata principale...\n");

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
	
	eliminaABR(radUtente);
	radUtente = NULL;
	return 0;
}
