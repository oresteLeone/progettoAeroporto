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
			richiesta = catchRequest();
			
			switch (richiesta) {
				case '0':
					printf("\nLogin...\n");
					break;
				case '1':
					printf("\nRegistrazione...\n");
					break;
				case '2':
					printf("\nChiusura in corso...\n");
					quit = 1;
					break;
				default:
					printf("Richiesta non valida\n");
					break;
			}
	} while (quit != 1);

	return 0;
}

