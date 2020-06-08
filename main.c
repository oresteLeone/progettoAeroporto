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
	int quit = 0, flag = 0, i=0;
	Graph G;
	Utente* radUtente = NULL;
	list* destinazioni = NULL;

	addNodoUtente(&radUtente, "_System", "admin");
	
	G = initGraph(20);
	destinazioni = initDestinazioni(destinazioni, G->nv);

	initEdge(G);

	do 
	{
		printf("\nInserisca '1' per il Login\nInserisca '2' per Registrarsi\nInserisca '0' per Chiudere\n ");
		richiesta = catchRequest();

		switch (richiesta) 
		{
			case '1':
				clrscr();
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
						else
							printf("\nPassword errata! Riprovi!\n");
					}

					if (strcmp(nomeUtente, "_System") == 0)
						menuAdmin(radUtente, G, &destinazioni);
					else
						menuUtente(referenceUtente(radUtente, nomeUtente), G, destinazioni);
				}

				break;
			case '2':
				clrscr();
				printf("\nRegistrazione:\n");
				do 
				{
					printf("\nSalve, per registrarsi inserisca un username: ");
					strcpy(nomeUtente, getString());
					flag = ricercaUtente(radUtente, nomeUtente);
					if (flag == 1)
						printf("\nNome utente non disponibile. Riprovi:\n");
					else
						printf("\nOk! Ora inserisca una password: ");
				} while (flag != 0);
				strcpy(passw, getString());

				addNodoUtente(&radUtente, nomeUtente, passw);
				clrscr();
				printf("\nRegistrazione utente %s completata. \n", nomeUtente);

				break;
			case '0':
				clrscr();
				printf("\nChiusura in corso...\n");
				quit = 1;
				break;
			default:
				clrscr();
				printf("\nRichiesta non valida\n");
				break;
		}
	} while (quit != 1);
	
	eliminaABR(radUtente);
	radUtente = NULL;
	cancellaLista(destinazioni);
	destinazioni = NULL;
	return 0;
}

