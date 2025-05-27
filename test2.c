#include "attivita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int main() {
    FILE *input = fopen("test2.in", "r");
    FILE *output = fopen("test2.actual", "w");
    if (!input || !output) {
        printf("Errore apertura file input/output.\n");
        return 1;
    }

    ListaAttivita lista = creaLista();
    char descrizione[100], corso[50], data[11];
    int ore, priorita;

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

    Nodo *n = ricercaAttivita(lista, "Studiare C");
    if (n) {
        aggiornaAttivita(lista, "Studiare C", 6);
        aggiornaAttivita(lista, "Studiare C", 4);
    }

    FILE *original_stdout = stdout;
    stdout = output;
    monitoraggioProgresso(lista);
    stdout = original_stdout;
    fclose(output);
    liberaMemoria(&lista);

    if (confrontaOutput("test2.actual", "test2.out")) {
        printf("TEST 2: PASS\n");
    } else {
        printf("TEST 2: FAIL\n");
    }

    return 0;
}
