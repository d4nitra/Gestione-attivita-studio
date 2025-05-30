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
|  Precondizioni: Nessuna
|  Postcondizioni: Il menu è stampato a schermo per permettere la scelta
--------------------------------------------------------
*/
void menu() {
    printf("\n==== GESTIONE ATTIVITÀ DI STUDIO ====\n");
    printf("1. Aggiungi nuova attività\n");
    printf("2. Visualizza le attività\n");
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
|  Precondizioni: Nessuna
|  Postcondizioni: Il programma viene eseguito fino a scelta dell'utente di terminare
--------------------------------------------------------
*/
int main() {
    TabellaAttivita* archivio = creaTabella(); // inizializza tabella hash
    int scelta;
    char buffer[20];

    // Costringe la prima scelta a essere 1 o 7
    do {
        printf("\n==== GESTIONE ATTIVITÀ DI STUDIO ====\n");
        printf("1. Aggiungi nuova attività\n");
        printf("7. Esci\n");
        printf("Scelta iniziale obbligatoria: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &scelta);
        if (scelta != 1 && scelta != 7) {
            printf(" Puoi solo iniziare aggiungendo un'attività (1) o uscendo (7).\n");
        }
    } while (scelta != 1 && scelta != 7);
    if (scelta == 1) {
                // Inserimento di una nuova attività
                Attivita nuova = creaAttivita();
                int id = inserisciAttivita(archivio, nuova);
                printf("Attività inserita con successo! ID assegnato: %d\n", id);
    }
    if (scelta == 7) {
        liberaTabella(archivio);
        printf("Chiusura del programma...\n");
        return 0;
    }

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
                // Visualizzazione delle attività filtrata
                visualizzaInterattiva(archivio);
                break;

            case 3: {
                   // Rimozione attività con controlli sull'ID
                    char buffer[20];
                    int id;

                     while (1) {
                           printf("Inserisci l'ID dell'attività da rimuovere: ");
                           fgets(buffer, sizeof(buffer), stdin);
                           if (sscanf(buffer, "%d", &id) == 1 && id > 0) {
                           if (cercaAttivita(archivio, id)) {
                               rimuoviAttivita(archivio, id);
                               break;
                            } else {
                              printf(" Nessuna attività trovata con ID %d.\n", id);
                             }
                             } else {
                                printf(" Inserisci un numero intero positivo valido per l'ID.\n");
                            }
                         }
    break;
}


            case 4: {
                     // Aggiornamento ore svolte con controlli
                    char buffer[20];
                    int id, ore;

                    // Controllo su ID
                    while (1) {
                        printf("Inserisci l'ID dell'attività da aggiornare: ");
                        fgets(buffer, sizeof(buffer), stdin);
                        if (sscanf(buffer, "%d", &id) == 1 && id > 0) {
                        if (cercaAttivita(archivio, id)) {
                            break;
                        } else {
                            printf(" Nessuna attività trovata con ID %d.\n", id);
                        }
                        } else {
                                printf("Inserisci un numero intero positivo valido per l'ID.\n");
                        }
                    }

                    // Controllo su ore da aggiungere
                    while (1) {
                        printf("Ore da aggiungere: ");
                        fgets(buffer, sizeof(buffer), stdin);
                        if (sscanf(buffer, "%d", &ore) == 1 && ore > 0) {
                           break;
                       } else {
                             printf(" Inserisci un numero intero positivo valido per le ore.\n");
                         }
    }

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
