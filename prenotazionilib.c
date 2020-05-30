#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazionilib.h"


prenotazione* creaPrenotazioneEconomy(int padre[], int partenza, int finale, list* destinazioni, int ecoTot, Graph G) {
	prenotazione* tmp = (prenotazione*)malloc(sizeof(prenotazione));
	strcpy(tmp->cittàPartenza, ricercaDestinazionePerNodo(destinazioni, partenza));
	tmp->economyTot = ecoTot;
	tmp->dest;//DA RIFARE
	tmp->next = NULL;
	tmp->distanzaTot = sommaDist();

	return tmp;
}

