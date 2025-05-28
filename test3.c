/*
========================================================
|  TEST3.C - Test automatico per la generazione del report settimanale
|  Autore: Daniela Lucia Ruocco
|  Data: 21/05/2025
|  Descrizione: Questo test verifica che la funzione generaReportSettimanale()
|               produca un output corretto, raggruppando le attività per settimana
|               e mostrando lo stato di ogni attività.
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
    int riga = 1;
    while (fgets(line1, sizeof(line1), f1) && fgets(line2, sizeof(line2), f2)) {
        // Rimuove newline finali
        line1[strcspn(line1, "\r\n")] = 0;
        line2[strcspn(line2, "\r\n")] = 0;

        if (strcmp(line1, line2) != 0) {
            fclose(f1);
            fclose(f2);
            return 0;
        }
        riga++;
    }

    // Verifica se entrambi i file sono finiti
    int fine1 = fgets(line1, sizeof(line1), f1) == NULL;
    int fine2 = fgets(line2, sizeof(line2), f2) == NULL;

    fclose(f1);
    fclose(f2);
    return fine1 && fine2;
}

/*
--------------------------------------------------------
|  Funzione: main
|  Scopo: Esegue il test per la funzione generaReportSettimanale()
|         caricando le attività da un file, generando un report,
|         e confrontando il risultato con l'output atteso.
|  Parametri: Nessuno.
|  Ritorno: 0 se il test è eseguito con successo.
--------------------------------------------------------
*/
int main() {
    FILE *input = fopen("test3.in", "r");
    FILE *output = fopen("test3.actual", "w");
    if (!input || !output) {
        printf("Errore apertura file input/output.\n");
        return 1;
    }

    ListaAttivita lista = creaLista();
    char descrizione[100], corso[50], data[11];
    int ore, priorita;

    // Caricamento delle attività da file
    while (fscanf(input, "%99[^;];%49[^;];%10[^;];%d;%d\n", descrizione, corso, data, &ore, &priorita) == 5) {
        Attivita a = {"", "", "", 0, 0, 0, 0};
        strcpy(a.descrizione, descrizione);
        strcpy(a.corso, corso);
        strcpy(a.dataScadenza, data);
        a.tempoStimato = ore;
        a.priorita = priorita;
        aggiungiAttivita(&lista, a);
    }
    fclose(input);

    // Redirezione dello stdout su file per catturare l'output
    FILE *original_stdout = stdout;
    stdout = output;
    generaReportSettimanale(lista);
    fflush(stdout);
    stdout = original_stdout;
    fclose(output);

    liberaMemoria(&lista);

    // Confronto con l'oracolo
    if (confrontaOutput("test3.actual", "test3.out")) {
        printf("TEST 3: PASS\n");
    } else {
        printf("TEST 3: FAIL\n");
    }

    return 0;
}
