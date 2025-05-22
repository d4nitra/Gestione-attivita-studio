/*
========================================================
|  MAIN.C - Programma Principale per la gestione delle attività
|            di studio. Interagisce con l'utente e utilizza
|            le funzionalità definite in attivita.c.
|  Autore: Daniela Lucia Ruocco
|  Data: 17/05/2025
|  Descrizione: Questo file implementa il menu di navigazione
|               e le operazioni principali richieste dall'utente.
========================================================
*/

#include "attivita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
/*
--------------------------------------------------------
|  Funzione: menu
|  Scopo: Visualizza il menu principale di selezione.
|  Parametri: Nessuno.
|  Ritorno: Nessuno.
--------------------------------------------------------
*/
void menu() {
    printf("\n---- Gestione Attività di Studio ----\n Inserisci il numero corrispondente per eseguire un azione: \n");
    printf("1. Aggiungi attività\n");
    printf("2. Visualizza tutte le attività\n");
    printf("3. Rimuovi un'attività inserendo la sua descrizione\n");
    printf("4. Monitoraggio del progresso\n");
    printf("5. Visualizza Report Settimanale\n");
    printf("6. Aggiorna ore svolte di un'attività\n");
    printf("7. Esci\n");
    printf("Scelta: ");
}

/*
--------------------------------------------------------
|  Funzione: main
|  Scopo: Gestisce il flusso principale del programma:
|         - Crea una lista di attività
|         - Interagisce con l'utente
|         - Gestisce le operazioni selezionate
|  Parametri: Nessuno.
|  Ritorno: 0 se l'esecuzione va a buon fine.
--------------------------------------------------------
*/
int main() {
    ListaAttivita lista = creaLista(); // Creo la lista di attività
    int scelta;
    char descrizione[MAX_DESC];
    int ore;

    do {
        menu();
        scanf("%d", &scelta);
        getchar(); // Pulizia del buffer

        switch (scelta) {
            case 1: {
                // Creazione e inserimento di una nuova attività
                Attivita nuova = creaAttivita();
                aggiungiAttivita(&lista, nuova);
                printf("Attività aggiunta con successo!\n");
                break;
            }
            case 2:
                // Visualizzazione delle attività
                visualizzaAttivita(lista);
                break;
            case 3:
                // Rimozione di un'attività tramite descrizione
                printf("Inserisci la descrizione dell'attività da rimuovere: ");
                fgets(descrizione, MAX_DESC, stdin);
                descrizione[strcspn(descrizione, "\n")] = 0;
                rimuoviAttivita(&lista, descrizione);
                break;
            case 4:
                // Monitoraggio del progresso delle attività
                monitoraggioProgresso(lista);
                break;
            case 5:
                // Generazione del report settimanale
                generaReportSettimanale(lista);
                break;
            case 6:
                // Aggiornamento ore svolte
                printf("Inserisci la descrizione dell'attività da aggiornare: ");
                fgets(descrizione, MAX_DESC, stdin);
                descrizione[strcspn(descrizione, "\n")] = 0;
                printf("Inserisci il numero di ore svolte da aggiungere: ");
                scanf("%d", &ore);
                getchar(); // pulizia del buffer
                aggiornaAttivita(lista, descrizione, ore);
                break;
            case 7:
                // Uscita e deallocazione della memoria
                liberaMemoria(&lista);
                printf("Uscita dal programma...\n");
                break;
            default:
                printf("L'input inserito non risulta valido, per favore inserire un numero da 1 a 7\n");
        }
    } while (scelta != 7);

    return 0;
}
