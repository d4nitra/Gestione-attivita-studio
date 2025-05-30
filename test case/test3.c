/*
========================================================
|  TEST3.C - Verifica della generazione del report settimanale
|  Autore: Daniela Lucia Ruocco
|  Data: 21/05/2025
|  Descrizione: Inserisce più attività con scadenze diverse
|               e genera il report settimanale, confrontando
|               il risultato con un oracolo.
========================================================
*/

#include "attivita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
--------------------------------------------------------
|  Funzione: confrontaOutput
|  Scopo: Confronta due file riga per riga per verificare
|         che il comportamento del programma sia corretto.
|  Parametri:
|    - output: percorso file generato
|    - oracolo: percorso file atteso
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
|  Scopo: Inserisce attività da file, genera il report
|         settimanale e confronta l'output con l'atteso.
|  Ritorno: 0 se tutto va a buon fine.
--------------------------------------------------------
*/
int main() {
    FILE *input = fopen("test3.in", "r");
    FILE *output = fopen("test3.actual", "w");
    if (!input || !output) {
        printf("Errore apertura file test3.in o test3.actual.\n");
        return 1;
    }

    TabellaAttivita *tabella = creaTabella();
    char descrizione[100], corso[50], data[11];
    int ore, priorita;

    // Lettura e inserimento multiplo di attività da file
    while (fscanf(input, "%99[^;];%49[^;];%10[^;];%d;%d\n", descrizione, corso, data, &ore, &priorita) == 5) {
        Attivita a;
        a.id = 0;
        strcpy(a.descrizione, descrizione);
        strcpy(a.corso, corso);
        strcpy(a.dataScadenza, data);
        a.tempoStimato = ore;
        a.oreSvolte = 0;
        a.priorita = priorita;
        a.completato = 0;
        inserisciAttivita(tabella, a);
    }
    fclose(input);

    // Redirezione dell'output
    FILE *originale = stdout;
    stdout = output;
    generaReportSettimanale(tabella);
    fflush(stdout);
    stdout = originale;
    fclose(output);

    liberaTabella(tabella);

    // Verifica con oracolo
    if (confrontaOutput("test3.actual", "test3.out")) {
        printf("TEST 3: PASS ✅\n");
    } else {
        printf("TEST 3: FAIL ❌\n");
    }

    return 0;
}
