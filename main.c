/*
========================================================
|  MAIN.C - Programma Principale per la gestione delle attività
|           di studio. Interagisce con l'utente e utilizza
|           le funzionalità definite in attivita.c
|  Autore: Daniela Lucia Ruocco
|  Data: 21/05/2025
|  Descrizione: Gestisce il menu utente e le principali operazioni
|               per inserire, aggiornare, cercare e rimuovere
|               attività tramite una tabella hash.
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
    printf("\n==== GESTIONE ATTIVITÀ DI STUDIO ====\n");
    printf("1. Aggiungi nuova attività\n");
    printf("2. Visualizza tutte le attività\n");
    printf("3. Rimuovi attività tramite ID\n");
    printf("4. Aggiorna ore svolte di un'attività\n");
    printf("5. Monitoraggio del progresso\n");
    printf("6. Genera report settimanale\n");
    printf("7. Esci\n");
    printf("Scelta: ");
}

/*
--------------------------------------------------------
|  Funzione: main
|  Scopo: Punto di ingresso del programma. Gestisce:
|         - Inizializzazione tabella
|         - Acquisizione input utente
|         - Invocazione delle operazioni core
|  Parametri: Nessuno.
|  Ritorno: 0 se terminato correttamente.
--------------------------------------------------------
*/
int main() {
    TabellaAttivita* archivio = creaTabella(); // inizializza tabella hash
    int scelta;

    do {
        menu();
        scanf("%d", &scelta);
        getchar();  // pulizia buffer input

        switch (scelta) {
            case 1: {
                // Inserimento di una nuova attività
                Attivita nuova = creaAttivita();
                int id = inserisciAttivita(archivio, nuova);
                printf("Attività inserita con successo! ID assegnato: %d\n", id);
                break;
            }

            case 2:
                // Visualizzazione delle attività presenti
                visualizzaAttivita(archivio);
                break;

            case 3: {
                // Rimozione attività tramite ID
                int id;
                printf("Inserisci l'ID dell'attività da rimuovere: ");
                scanf("%d", &id);
                getchar();
                rimuoviAttivita(archivio, id);
                break;
            }

            case 4: {
                // Aggiornamento ore svolte
                int id, ore;
                printf("Inserisci l'ID dell'attività da aggiornare: ");
                scanf("%d", &id);
                printf("Ore da aggiungere: ");
                scanf("%d", &ore);
                getchar();
                aggiornaAttivita(archivio, id, ore);
                break;
            }

            case 5:
                // Stampa stato attività
                monitoraggioProgresso(archivio);
                break;

            case 6:
                // Stampa report settimanale
                generaReportSettimanale(archivio);
                break;

            case 7:
                // Chiusura e deallocazione memoria
                liberaTabella(archivio);
                printf("Chiusura del programma...\n");
                break;

            default:
                printf("Scelta non valida. Inserisci un numero tra 1 e 7.\n");
        }

    } while (scelta != 7);

    return 0;
}
