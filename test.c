/*
========================================================
|  TEST.C - File di test per il progetto Gestione Attività
|  Autore: Daniela Lucia Ruocco
|  Descrizione: Questo file contiene casi di test per verificare
|               tutte le funzioni implementate in attivita.c
========================================================
*/

#include "attivita.h"
#include <stdio.h>
#include <string.h>

int main() {
    ListaAttivita lista = creaLista();

    // Test 1: Inserimento attività
    printf("\n--- Test 1: Inserimento attività ---\n");
    Attivita a1 = {"Studiare C", "Programmazione", "30/05/2025", 10, 2, 0, 0};
    Attivita a2 = {"Esercizi Matematica", "Analisi", "25/05/2025", 5, 1, 0, 0};
    aggiungiAttivita(&lista, a1);
    aggiungiAttivita(&lista, a2);
    visualizzaAttivita(lista);

    // Test 2: Ricerca attività esistente
    printf("\n--- Test 2: Ricerca attività esistente ---\n");
    Nodo* trovata = ricercaAttivita(lista, "Studiare C");
    if (trovata != NULL) {
        printf("Attività trovata: %s\n", trovata->attivita.descrizione);
    } else {
        printf("Attività non trovata.\n");
    }

    // Test 3: Ricerca attività inesistente
    printf("\n--- Test 3: Ricerca attività inesistente ---\n");
    trovata = ricercaAttivita(lista, "Non Esiste");
    if (trovata == NULL) {
        printf("Ricerca corretta: attività non esistente gestita.\n");
    }

    // Test 4: Aggiornamento ore svolte
    printf("\n--- Test 4: Aggiornamento ore ---\n");
    aggiornaAttivita(lista, "Studiare C", 6);
    aggiornaAttivita(lista, "Studiare C", 5); // dovrebbe completarsi

    // Test 5: Monitoraggio progresso
    printf("\n--- Test 5: Monitoraggio Progresso ---\n");
    monitoraggioProgresso(lista);

    // Test 6: Generazione Report Settimanale
    printf("\n--- Test 6: Report Settimanale ---\n");
    generaReportSettimanale(lista);

    // Test 7: Rimozione attività esistente
    printf("\n--- Test 7: Rimozione attività esistente ---\n");
    rimuoviAttivita(&lista, "Esercizi Matematica");
    visualizzaAttivita(lista);

    // Test 8: Rimozione attività inesistente
    printf("\n--- Test 8: Rimozione attività inesistente ---\n");
    rimuoviAttivita(&lista, "Inesistente");

    // Test 9: Libera memoria
    printf("\n--- Test 9: Libera Memoria ---\n");
    liberaMemoria(&lista);
    if (lista == NULL) {
        printf("Memoria liberata correttamente.\n");
    }

    return 0;
}
