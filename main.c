#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definers.h"
#include "graphlib.h"
#include "utentilib.h"
#include "guilib.h"

int main() {
	
	char richiesta;
	int quit = 0;
	
	do {
			printf("\nInserisca '1' per il Login\nInserisca '2' per Registrarsi\nInserisca '0' per Chiudere\n ");
			richiesta = catchRequest();
			
			switch (richiesta) {
				case '1':
					printf("\nLogin...\n");
					break;
				case '2':
					printf("\nRegistrazione...\n");
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

