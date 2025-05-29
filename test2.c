/*
========================================================
|  TEST2.C - Test aggiornamento del progresso attività
|  Autore: Daniela Lucia Ruocco
|  Data: 21/05/2025
|  Descrizione: Verifica che l'aggiornamento delle ore svolte
|               modifichi correttamente lo stato di completamento
|               e il progresso di un'attività nella tabella hash.
========================================================
*/

#include "attivita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
--------------------------------------------------------
|  Funzione: confrontaOutput
|  Scopo: Confronta due file riga per riga per verificarne
|         l'identità, utile per confronti automatici.
|  Parametri:
|    - output: file generato dal programma
|    - oracolo: file di output atteso
|  Ritorno: 1 se uguali, 0 se diversi
--------------------------------------------------------
*/
int confrontaOutput(const char *output, const char *oracolo) {
    FILE *f1 = fopen(output, "r");
    FILE *f2 = fopen(oracolo, "r");
    if (!f1 || !f2) return 0;

    char linea1[1024], linea2[1024];
    while (fgets(linea1, sizeof(linea1), f1) && fgets(linea2, sizeof(linea2), f2)) {
        linea1[strcspn(linea1, "\r\n")] = 0;
        linea2[strcspn(linea2, "\r\n")] = 0;
        if (strcmp(linea1, linea2) != 0) {
            fclose(f1);
            fclose(f2);
            return 0;
        }
    }

    int fine1 = fgets(linea1, sizeof(linea1), f1) == NULL;
    int fine2 = fgets(linea2, sizeof(linea2), f2) == NULL;
    fclose(f1);
    fclose(f2);
    return fine1 && fine2;
}

/*
--------------------------------------------------------
|  Funzione: main
|  Scopo: Inserisce un'attività da file, ne aggiorna il
|         progresso e verifica il risultato con l'oracolo.
|  Ritorno: 0 se il test è completato correttamente
--------------------------------------------------------
*/
int main() {
    FILE *input = fopen("test2.in", "r");
    FILE *output = fopen("test2.actual", "w");
    if (!input || !output) {
        printf("Errore apertura file input/output.\n");
        return 1;
    }

    // Creazione della tabella hash
    TabellaAttivita *tabella = creaTabella();
    char descrizione[100], corso[50], data[11];
    int ore, priorita, oreAggiunte;

    // Lettura singola attività dal file di input
    fscanf(input, "%99[^;];%49[^;];%10[^;];%d;%d;%d\n",
           descrizione, corso, data, &ore, &priorita, &oreAggiunte);

    Attivita nuova;
    nuova.id = 0;
    strcpy(nuova.descrizione, descrizione);
    strcpy(nuova.corso, corso);
    strcpy(nuova.dataScadenza, data);
    nuova.tempoStimato = ore;
    nuova.oreSvolte = 0;
    nuova.priorita = priorita;
    nuova.completato = 0;

    // Inserimento nella tabella e ottenimento ID
    int idGenerato = inserisciAttivita(tabella, nuova);

    // Aggiornamento del progresso tramite ID
    aggiornaAttivita(tabella, idGenerato, oreAggiunte);

    // Redirezione dell'output su file .actual
    FILE *originale = stdout;
    stdout = output;
    visualizzaAttivita(tabella);
    fflush(stdout);
    stdout = originale;

    fclose(input);
    fclose(output);
    liberaTabella(tabella);

    // Verifica automatica del risultato
    if (confrontaOutput("test2.actual", "test2.out")) {
        printf("TEST 2: PASS ✅\n");
    } else {
        printf("TEST 2: FAIL ❌\n");
    }

    return 0;
}
