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

	addEdge(G, 0, 1, 20, 60);
	addEdge(G, 1, 2, 40, 40);
	addEdge(G, 2, 3, 30, 30);
	addEdge(G, 0, 3, 10, 35);
	addEdge(G, 3, 1, 5, 20);

	addEdge(G, 0, 1, 10, 187);
	addEdge(G, 0, 7, 20, 219);
	addEdge(G, 0, 14, 100, 1016);
	addEdge(G, 0, 19, 500, 5213);

	addEdge(G, 1, 3, 25, 248);
	addEdge(G, 1, 8, 10, 126);
	addEdge(G, 1, 9, 90, 960);
	addEdge(G, 1, 10, 20, 245);
	addEdge(G, 1, 12, 50, 561);
	addEdge(G, 1, 13, 80, 843);
	addEdge(G, 1, 17, 900, 9718);

	addEdge(G, 2, 0, 10, 187);
	addEdge(G, 2, 3, 20, 234);

	addEdge(G, 3, 1, 20, 248);
	addEdge(G, 3, 2, 20, 234);
	addEdge(G, 3, 4, 8, 80);

	addEdge(G, 4, 3, 8, 80);
	addEdge(G, 4, 5, 10, 190);

	addEdge(G, 5, 4, 10, 190);
	addEdge(G, 5, 8, 20, 295);

	addEdge(G, 6, 7, 10, 105);

	addEdge(G, 7, 0, 20, 219);
	addEdge(G, 7, 6, 10, 105);

	addEdge(G, 8, 1, 10, 126);

	addEdge(G, 9, 1, 90, 960);
	addEdge(G, 9, 11, 30, 320);
	addEdge(G, 9, 12, 60, 632);
	addEdge(G, 9, 13, 90, 932);
	addEdge(G, 9, 14, 110, 1139);

	addEdge(G, 10, 1, 20, 245);

	addEdge(G, 11, 9, 30, 320);
	addEdge(G, 11, 13, 60, 652);

	addEdge(G, 12, 1, 50, 561);
	addEdge(G, 12, 9, 60, 632);

	addEdge(G, 13, 1, 80, 843);
	addEdge(G, 13, 9, 90, 932);
	addEdge(G, 13, 11, 60, 652);
	addEdge(G, 13, 17, 890, 8918);

	addEdge(G, 14, 0, 100, 1016);
	addEdge(G, 14, 9, 110, 1139);
	addEdge(G, 14, 15, 30, 302);
	addEdge(G, 14, 16, 100, 1005);
	addEdge(G, 14, 18, 850, 8543);
	addEdge(G, 14, 19, 580, 5892);

	addEdge(G, 15, 14, 30, 302);

	addEdge(G, 16, 14, 100, 1005);

	addEdge(G, 17, 1, 970, 9718);
	addEdge(G, 17, 13, 890, 8918);

	addEdge(G, 18, 14, 850, 8543);
	addEdge(G, 18, 19, 890, 8933);

	addEdge(G, 19, 0, 520, 5213);
	addEdge(G, 19, 14, 580, 5892);
	addEdge(G, 19, 18, 890, 8933);



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
						else
							printf("\nPassword errata! Riprovi!\n");
					}

					if (strcmp(nomeUtente, "_System") == 0)
						menuAdmin(radUtente, G, destinazioni);
					else
						menuUtente(destinazioni);
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
	cancellaLista(destinazioni);
	destinazioni = NULL;
	return 0;
}

