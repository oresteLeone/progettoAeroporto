#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazionilib.h"


//estrazione del percorso dal vettore padre
path* extractPath(int padre[], int partenza, int finale) {
	int cur;
	path* head = NULL;

	for (cur = finale;cur != partenza;cur = padre[cur]) {
		path* tmp = initPath(cur);
		if (head == NULL)
			head = tmp;
		else {
			tmp->next = head;
			head = tmp;
		}
	}

	return head;
}

//crezione del nodo del percorso minimo
path* initPath(int node) {
	path* tmp = (path*)malloc(sizeof(path));
	tmp->node = node;
	tmp->next = NULL;
	return tmp;
}

//stampa dei nodi del percorso minimo
void printPath(path* path, list* destinazioni) {
	if (path != NULL) {
		printf(" -> %s", ricercaDestinazionePerNodo(destinazioni, path->node));
		printPath(path->next, destinazioni);
	}
}

//funzione per la creazione prenotazione sulla base economica
prenotazione* creaPrenotazioneEconomy(path* patheco, int partenza, int finale, list* destinazioni, int ecoTot, Graph G) {
	prenotazione* tmp = (prenotazione*)malloc(sizeof(prenotazione));
	strcpy(tmp->cittąPartenza, ricercaDestinazionePerNodo(destinazioni, partenza));
	tmp->economyTot = ecoTot;
	tmp->dest = creaDestinazione(partenza, patheco, destinazioni, G);
	tmp->next = NULL;
	tmp->distanzaTot = sommaDist(tmp->dest);

	return tmp;
}

//funzione per la creazione prenotazione sulla base distanza
prenotazione* creaPrenotazioneDistance(path* pathdist, int partenza, int finale, list* destinazioni, int distTot, Graph G) {
	prenotazione* tmp = (prenotazione*)malloc(sizeof(prenotazione));
	strcpy(tmp->cittąPartenza, ricercaDestinazionePerNodo(destinazioni, partenza));
	tmp->dest = creaDestinazione(partenza, pathdist, destinazioni, G);
	tmp->next = NULL;
	tmp->distanzaTot = distTot;
	tmp->economyTot = sommaEconomy(tmp->dest);

	return tmp;
}

//funzione per la creazione delle destinazioni nella prenotazione
destinazione* creaDestinazione(int startnode, path* pathstart, list* destinazioni, Graph G) {
	path* cursorpath = pathstart;
	int prevnode = startnode;
	destinazione* head = NULL;

	for (cursorpath;cursorpath != NULL;cursorpath = cursorpath->next) {
		edge arclist = (edge)malloc(sizeof(struct edgeType));
		arclist = G->adj[prevnode];
		edge nodetarget = trovaArco(arclist, cursorpath->node);
		prevnode = nodetarget->key;


		if (head == NULL)
			head = initDestinazione(nodetarget, destinazioni);
		else {
			addonTail(head, nodetarget, destinazioni);
		}

	}
	return head;

}

//crezione del nodo destinazione della prenotazione
destinazione* initDestinazione(edge arc, list* destinazioni) {
	destinazione* tmp = (destinazione*)malloc(sizeof(destinazione));
	strcpy(tmp->cittą, ricercaDestinazionePerNodo(destinazioni, arc->key));
	tmp->disttratt = arc->pesoDistanza;
	tmp->ecotratt = arc->pesoEconomy;
	tmp->next = NULL;

	return tmp;

}

//utility per la ricerca nella crezione del nodo destinazione
edge trovaArco(edge list, int target) {
	edge tmp = list;
	if (tmp->key == target) {
		return tmp;
	}
	else {
		tmp = trovaArco(tmp->next, target);
	}
	return tmp;
}

//aggiunge in coda alla lista delle destinazioni
void addonTail(destinazione* head, edge nodetarget, list* destinazioni) {
	destinazione* p, * q;
	p =initDestinazione(nodetarget,destinazioni);
	q = head;
	while (q->next != NULL)
	{
		q = q->next;
	}
	q->next = p;

	
}

//calcola la distanza totale nel caso di una prenotazione su base economica
int sommaDist(destinazione* list) {
	int tot=0;
	if (list) {
		tot = list->disttratt + sommaDist(list->next);
	}
	return tot;
}

//calcola il costo totale nel caso di una prenotazione su base distanza
int sommaEconomy(destinazione* list) {
	int tot = 0;
	if (list) {
		tot = list->ecotratt + sommaEconomy(list->next);
	}
	return tot;
}

//stampa delle prenotazioni di un utente
void printPrenotazioni(prenotazione* listaPrenot) {
	if (listaPrenot) {
		printf("\n\nPrenotazione:\n\nPartenza %s -> ",listaPrenot->cittąPartenza);
		printDestinazioni(listaPrenot->dest);
		printf("Costo: %d Distanza: %d\n", listaPrenot->economyTot,listaPrenot->distanzaTot);
		if (listaPrenot->next) {
			printPrenotazioni(listaPrenot->next);
		}

	}

}

//stampa delle destinazioni di una prenotazione
void printDestinazioni(destinazione* list) {
	if (list) {
		if (list->next) {
			printf("scalo %s -> ", list->cittą);
			printDestinazioni(list->next);
		}
		else
		{
			printf("Destinazione: %s\n", list->cittą);
		}
	}
}

//funzione che aggiunge una prenotazione alla lista prenotazioni dell utente
prenotazione* addPrenotazione(prenotazione* UserList, prenotazione* new) {
	
	if (UserList) {
		UserList->next=addPrenotazione(UserList->next, new);
	}
	else {
		UserList = new;
	}
	return UserList;
}

//funzione che controlla se la cittą rimossa facesse parte di una prenotazione
int ricercaPerRemovePrenotazioneCittą(destinazione* dest, char* city) {
	int res = -1;

	if (dest != NULL) {
		if (strcmp(dest->cittą, city) == 0)
			return 1;
		else
			res = ricercaPerRemovePrenotazioneCittą(dest->next, city);
	}

	return res;
}

//rimozione della prenotazione a seguito di una cittą rimossa
prenotazione* removePrenotazioneCittą(prenotazione* UserList, char* city) {
	if (UserList) {
		UserList->next = removePrenotazioneCittą(UserList->next, city);
		if (strcmp(UserList->cittąPartenza, city) == 0 || ricercaPerRemovePrenotazioneCittą(UserList->dest, city) != -1) {
			prenotazione* tmp = UserList->next;
			free(UserList);
			return tmp;
		}
	}
	
	return UserList;

}

//creazione nodo dei conflitti
conflitto* initConflitto(char* motivo, char* city, destinazione* dest) {

	conflitto* tmp = (conflitto*)malloc(sizeof(conflitto));

	strcpy(tmp->motivo, motivo);
	strcpy(tmp->cittąPartenza, city);
	tmp->dest = dest;
	tmp->next = NULL;

	return tmp;
}


//funzione che crea la lista dei conflitti per utente in seguito a rimozione cittą
conflitto* ConflittiCittą(prenotazione* UserList, char* motivo, char* city) {
	conflitto* tmp = (conflitto*)malloc(sizeof(conflitto));
	if (UserList) {
		tmp = ConflittiCittą(UserList->next, motivo, city);
		if (strcmp(UserList->cittąPartenza, city) == 0 || ricercaPerRemovePrenotazioneCittą(UserList->dest, city) != -1) {
			conflitto* new = initConflitto(motivo, UserList->cittąPartenza, UserList->dest);
			new->next = tmp;
			return new;
		}
	}
	else{
		tmp = NULL;	
	}
	return tmp;
	
}

//funzione che controlla se la tratta rimossa facesse parte di una prenotazione
int ricercaPerRemovePrenotazioneTratta(destinazione* dest, char* cittą1, char* cittą2) {
	int res = -1;

	if (dest != NULL && dest->next != NULL) { 
		if (strcmp(dest->cittą, cittą1) == 0 && strcmp(dest->next->cittą, cittą2) == 0)
			return 1;
		else
			res = ricercaPerRemovePrenotazioneTratta(dest->next, cittą1, cittą2);
	}

	return res; 
}

//rimozione della prenotazione a seguito di una tratta rimossa
prenotazione* removePrenotazioneTratta(prenotazione* UserList, char* cittą1, char* cittą2) {
	if (UserList) { 
		UserList->next = removePrenotazioneTratta(UserList->next, cittą1, cittą2);
		if ((strcmp(UserList->cittąPartenza, cittą1) == 0 && strcmp(UserList->dest->cittą, cittą2) == 0) || ricercaPerRemovePrenotazioneTratta(UserList->dest, cittą1, cittą2) != -1) {
			prenotazione* tmp = UserList->next;
			free(UserList);
			return tmp;
		}
	}

	return UserList;
}

//funzione che crea la lista dei conflitti per utente in seguito a rimozione tratta
conflitto* ConflittiTratta(prenotazione* UserList, char* motivo, char* cittą1, char* cittą2) {
	conflitto* tmp = (conflitto*)malloc(sizeof(conflitto));
	if (UserList) {
		tmp = ConflittiTratta(UserList->next, motivo, cittą1, cittą2);
		if ((strcmp(UserList->cittąPartenza, cittą1) == 0 && strcmp(UserList->dest->cittą, cittą2) == 0) || ricercaPerRemovePrenotazioneTratta(UserList->dest, cittą1, cittą2) != -1) {
			conflitto* new = initConflitto(motivo, UserList->cittąPartenza, UserList->dest);
			new->next = tmp;
			return new;
		}
	}
	else {
		tmp = NULL;
	}
	return tmp;
}

//funzione che stampa la lista dei conflitti per utente
void stampaConflitto(conflitto* disdette)
{
	if (disdette) {
		printf("\nMotivo: %s", disdette->motivo);
		printf("\nPartenza: %s -> ", disdette->cittąPartenza);
		printDestinazioni(disdette->dest);
		stampaConflitto(disdette->next);
	}
}

//funzione che elimina totalmente la lista conflitti
void cancellaConflitti(conflitto* list ) {
	if (list != NULL) {
		cancellaConflitti(list->next);
		free(list);
	}
}