/*
========================================================
|  UTILE.C - Funzioni di supporto per la gestione delle attività
|  Autore: Daniela Lucia Ruocco
|  Data: 21/05/2025
|  Descrizione: Questo file contiene funzioni ausiliarie come il controllo
|               della validità delle date e la gestione temporale delle scadenze.
========================================================
*/

#include "utile.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/*
--------------------------------------------------------
|  Funzione: dataValida
|  Scopo: Verifica se una data è valida (giorno, mese, anno).
|  Parametri:
|    - giorno: intero
|    - mese: intero
|    - anno: intero
|  Ritorno: 1 se la data è valida, 0 altrimenti
|  Precondizioni: giorno, mese, anno devono essere valori interi
|  Postcondizioni: restituisce 1 se la data rappresenta un giorno esistente
--------------------------------------------------------
*/
int dataValida(const char* data) {
    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/') return 0;
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(data[i])) return 0;
    }

    int giorno, mese, anno;
    sscanf(data, "%d/%d/%d", &giorno, &mese, &anno);
    if (giorno < 1 || mese < 1 || mese > 12 || anno < 1900 || anno > 2100) return 0;

    int giorniMese[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if ((anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0)) giorniMese[2] = 29;
    return giorno <= giorniMese[mese];
}

/*
--------------------------------------------------------
|  Funzione: convertiData
|  Scopo: Converte una stringa di data in una struttura tm.
|  Parametri:
|    - data: stringa della data nel formato gg/mm/aaaa.
|  Ritorno: struttura tm corrispondente.
|  Precondizioni: data != NULL e nel formato valido
|  Postcondizioni: restituisce una struct tm con giorno, mese e anno impostati
--------------------------------------------------------
*/
struct tm convertiData(const char* data) {
    struct tm risultato = {0};
    sscanf(data, "%d/%d/%d", &risultato.tm_mday, &risultato.tm_mon, &risultato.tm_year);
    risultato.tm_mon -= 1;
    risultato.tm_year -= 1900;
    return risultato;
}

/*
--------------------------------------------------------
|  Funzione: calcolaSettimana
|  Scopo: Calcola il numero della settimana dell'anno per una certa data.
|  Parametri:
|    - data: struttura tm della data da analizzare.
|  Ritorno: Numero della settimana (0-52).
|  Precondizioni: data valida
|  Postcondizioni: restituisce il numero della settimana secondo convenzione ISO
--------------------------------------------------------
*/
int calcolaSettimana(struct tm data) {
    char buffer[3];
    strftime(buffer, sizeof(buffer), "%W", &data);
    return atoi(buffer);
}

/*
--------------------------------------------------------
|  Funzione: calcolaIntervalloSettimana
|  Scopo: Calcola le date di inizio (lunedì) e fine (domenica) della settimana
|         in cui cade una data.
|  Parametri:
|    - input: data di riferimento
|    - inizio: puntatore alla data del lunedì
|    - fine: puntatore alla data della domenica
|  Ritorno: Nessuno
|  Precondizioni: input valido, inizio e fine != NULL
|  Postcondizioni: inizio e fine vengono riempiti con le date corrispondenti al lunedì e alla domenica
--------------------------------------------------------
*/
void calcolaIntervalloSettimana(struct tm input, struct tm* inizio, struct tm* fine) {
    *inizio = input;
    *fine = input;
    mktime(inizio); mktime(fine);
    int giornoSettimana = inizio->tm_wday;
    if (giornoSettimana == 0) giornoSettimana = 7; 
    inizio->tm_mday -= (giornoSettimana - 1);
    fine->tm_mday += (7 - giornoSettimana);
    mktime(inizio);
    mktime(fine);
}
