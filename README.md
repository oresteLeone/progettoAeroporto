# Progetto II: Compagnia Aerea 
## Traccia 
Si sviluppi un programma per la gestione delle prenotazioni di voli. 

Si richiede che un utente possa registrarsi all’avvio del sistema, o entrare come utente già registrato. In ogni caso, solo gli utenti registrati possono prenotare un nuovo viaggio. 

Dopo l’accesso, l’utente può visualizzare le sue prenotazioni attive, ed effettuarne una nuova specificando: 

- 1. La città di partenza e la città di destinazione, e il sistema gli propone: 

  - • La tratta più economica 
  - • La tratta più breve 
  
- 2. Solo la città di partenza, e il sistema gli propone: 

  - • La meta più economica 
  - • La meta più gettonata
  
Tutte le tratte proposte dalla compagnia possono prevedere scali. Nel caso non ci siano voli disponibili per la tratta selezionata, la compagnia avviserà opportunamente l’utente.

Ad ogni acquisto, l’utente accumula dei punti, proporzionalmente al costo della tratta prenotata. Accumulare punti consente di maturare degli sconti per viaggi successivi. Prima di procedere con la prenotazione, quindi, il sistema controlla opportunamente se l’utente possieda degli sconti, ed eventualmente li applica, se l’utente lo desidera.

Prima dell’accesso da parte dell’utente, il sistema può permettere alla compagnia di aggiungere nuove tratte (sia nuove destinazioni che nuovi voli) e di rimuoverle.

Realizzare la mappatura dei voli tramite un grafo e popolarlo inizialmente con 20 destinazioni e tratte arbitrarie. 
Per semplicità, si assuma che la disponibilità dei voli non sia vincolata a date nè al numero dei posti disponibili sul volo stesso. 

## Regole per la consegna 

Scrivere un Report di massimo 6 pagine, in cui si riporta: 
- • Un disegno del grafo iniziale delle tratte, in cui si espliciti anche il costo e la durata di ciascun volo singolo. 
- • Motivazione per le scelte implementative. 
- • Suddivisione del lavoro tra i componenti del gruppo. 
- • Un esempio di esecuzione.

Consegnare il report (in formato PDF) insieme al codice e all’eseguibile del progetto in una cartella compressa IdGruppo.zip. 
