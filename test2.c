/*
========================================================
|  TEST2.C - Test automatico per aggiornamento progresso attività
|  Autore: Daniela Lucia Ruocco
|  Data: 21/05/2025
|  Descrizione: Questo test verifica che l'aggiornamento delle ore
|               svolte modifichi correttamente lo stato dell'attività
|               e il progresso venga calcolato correttamente.
========================================================
*/

#include "attivita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
--------------------------------------------------------
|  Funzione: confrontaOutput
|  Scopo: Confronta riga per riga due file di testo per verificarne l'uguaglianza.
|  Parametri:
|    - output: percorso del file generato dal programma.
|    - oracolo: percorso del file con il risultato atteso.
|  Ritorno: 1 se i file sono uguali, 0 altrimenti.
--------------------------------------------------------
*/
int confrontaOutput(const char *output, const char *oracolo) {
    FILE *f1 = fopen(output, "r");
    FILE *f2 = fopen(oracolo, "r");
    if (!f1 || !f2) return 0;

    char line1[1024], line2[1024];
    while (fgets(line1, sizeof(line1), f1) && fgets(line2, sizeof(line2), f2)) {
        line1[strcspn(line1, "\r\n")] = 0;
        line2[strcspn(line2, "\r\n")] = 0;
        if (strcmp(line1, line2) != 0) {
            fclose(f1);
            fclose(f2);
            return 0;
        }
    }
    int fine1 = fgets(line1, sizeof(line1), f1) == NULL;
    int fine2 = fgets(line2, sizeof(line2), f2) == NULL;
    fclose(f1);
    fclose(f2);
    return fine1 && fine2;
}

/*
--------------------------------------------------------
|  Funzione: main
|  Scopo: Esegue il test per aggiornare le ore svolte su un'attività
|         e verificarne la corretta modifica del progresso e stato.
|  Parametri: Nessuno.
|  Ritorno: 0 se il test è eseguito correttamente.
--------------------------------------------------------
*/
int main() {
    FILE *input = fopen("test2.in", "r");
    FILE *output = fopen("test2.actual", "w");
    if (!input || !output) {
        printf("Errore apertura file input/output.\n");
        return 1;
    }

    ListaAttivita lista = creaLista();
    char descrizione[100], corso[50], data[11];
    int ore, priorita, oreAggiunte;

    // Caricamento attività da file
    fscanf(input, "%99[^;];%49[^;];%10[^;];%d;%d;%d\n", descrizione, corso, data, &ore, &priorita, &oreAggiunte);
    Attivita a = {"", "", "", 0, 0, 0, 0};
    strcpy(a.descrizione, descrizione);
    strcpy(a.corso, corso);
    strcpy(a.dataScadenza, data);
    a.tempoStimato = ore;
    a.priorita = priorita;
    aggiungiAttivita(&lista, a);

    aggiornaAttivita(lista, descrizione, oreAggiunte); // Aggiornamento ore

    FILE *original_stdout = stdout;
    stdout = output;
    visualizzaAttivita(lista);
    fflush(stdout);
    stdout = original_stdout;
    fclose(output);
    fclose(input);
    liberaMemoria(&lista);

    if (confrontaOutput("test2.actual", "test2.out")) {
        printf("TEST 2: PASS\n");
    } else {
        printf("TEST 2: FAIL\n");
    }

    return 0;
}
