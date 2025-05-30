/*
========================================================
|  TEST1.C - Test su inserimento e visualizzazione con tabella hash
|  Autore: Daniela Lucia Ruocco
|  Data: 21/05/2025
|  Descrizione: Verifica l'inserimento di attività nella
|               tabella hash e la corretta visualizzazione.
========================================================
*/

#include "attivita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
--------------------------------------------------------
|  Funzione: confrontaOutput
|  Scopo: Confronta due file riga per riga
|         per verificarne l'identità.
|  Parametri:
|    - output: file generato dal programma
|    - oracolo: file con risultato atteso
|  Ritorno: 1 se uguali, 0 altrimenti
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
|  Scopo: Inserisce attività da file e verifica la stampa
|         confrontando l’output con l’oracolo.
|  Ritorno: 0 se esecuzione riuscita
--------------------------------------------------------
*/
int main() {
    FILE *input = fopen("test1.in", "r");
    FILE *output = fopen("test1.actual", "w");
    if (!input || !output) {
        printf("Errore apertura file.\n");
        return 1;
    }

    TabellaAttivita *tabella = creaTabella();

    char descrizione[100], corso[50], data[11];
    int ore, priorita;

    // Lettura da file .in e inserimento in tabella hash
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

    // Redirezione output su file .actual
    FILE *stdout_backup = stdout;
    stdout = output;
    visualizzaAttivita(tabella, 1); // visualizza tutte le attività
    fflush(stdout);
    stdout = stdout_backup;
    fclose(output);

    liberaTabella(tabella);

    // Confronto output effettivo con output atteso
    if (confrontaOutput("test1.actual", "test1.out")) {
        printf("TEST 1: PASS ✅\n");
    } else {
        printf("TEST 1: FAIL ❌\n");
    }

    return 0;
}
