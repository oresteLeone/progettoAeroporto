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
	Utente* radUtente = NULL;
	list* destinazioni = NULL;

	addNodoUtente(&radUtente, "_System", "admin");
	
	Graph G = initGraph(20);
	for (i = 0;i < G->nv;i++) {
		if (i == 0)
			destinazioni = inserisciDestinazione(destinazioni, i, "Napoli");
		else if (i == 1)
			destinazioni = inserisciDestinazione(destinazioni, i, "Milano");
		else if (i == 2)
			destinazioni = inserisciDestinazione(destinazioni, i, "Roma");
		else if (i == 3)
			destinazioni = inserisciDestinazione(destinazioni, i, "Firenze");
		else if (i == 4)
			destinazioni = inserisciDestinazione(destinazioni, i, "Bologna");
		else if (i == 5)
			destinazioni = inserisciDestinazione(destinazioni, i, "Genova");
		else if (i == 6)
			destinazioni = inserisciDestinazione(destinazioni, i, "Brindisi");
		else if (i == 7)
			destinazioni = inserisciDestinazione(destinazioni, i, "Bari");
		else if (i == 8)
			destinazioni = inserisciDestinazione(destinazioni, i, "Torino");
		else if (i == 9)
			destinazioni = inserisciDestinazione(destinazioni, i, "Londra");
		else if (i == 10)
			destinazioni = inserisciDestinazione(destinazioni, i, "Venezia");
		else if (i == 11)
			destinazioni = inserisciDestinazione(destinazioni, i, "Bruxelles");
		else if (i == 12)
			destinazioni = inserisciDestinazione(destinazioni, i, "Parigi");
		else if (i == 13)
			destinazioni = inserisciDestinazione(destinazioni, i, "Berlino");
		else if (i == 14)
			destinazioni = inserisciDestinazione(destinazioni, i, "Barcellona");
		else if (i == 15)
			destinazioni = inserisciDestinazione(destinazioni, i, "Valencia");
		else if (i == 16)
			destinazioni = inserisciDestinazione(destinazioni, i, "Lisbona");
		else if (i == 17)
			destinazioni = inserisciDestinazione(destinazioni, i, "Tokyo");
		else if (i == 18)
			destinazioni = inserisciDestinazione(destinazioni, i, "Rio");
		else if (i == 19)
			destinazioni = inserisciDestinazione(destinazioni, i, "Nairobi");

	}
	printf("\nDestinazioni:\n");
	stampaLista(destinazioni);

	printf("\nRicercato parigi Nodo richiesto: %d\n", ricercaDestinazionePerCittà(destinazioni, "Parigi"));
	printf("\nRicercato nodo 7 Citta' richiesta: %s\n", ricercaDestinazionePerNodo(destinazioni, 7));
	
	addEdge(G, 0, 1, 20, 60);
	addEdge(G, 1, 2, 40, 40);
	addEdge(G, 2, 3, 30, 30);
	addEdge(G, 0, 3, 10, 35);
	addEdge(G, 3, 1, 5, 20);

	printf("\nGrafo G:\n");
	printGraph(G,destinazioni);

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
						menuAdmin(radUtente);
					else
						menuUtente();
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

