/*
========================================================
|  UTILE.C - Funzioni di utilità generica (gestione date)
|  Autore: Daniela Lucia Ruocco
|  Descrizione: Funzioni di supporto per parsing e calcolo
|               di settimane e intervalli temporali.
========================================================
*/

#include "utile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
--------------------------------------------------------
|  Funzione: convertiData
|  Scopo: Converte una stringa data (gg/mm/aaaa) in struct tm.
|  Parametri:
|    - data: stringa nel formato gg/mm/aaaa
|  Ritorno: struttura tm corrispondente
--------------------------------------------------------
*/
struct tm convertiData(const char *data) {
    struct tm risultato = {0};
    int g, m, a;
    sscanf(data, "%d/%d/%d", &g, &m, &a);
    risultato.tm_mday = g;
    risultato.tm_mon = m - 1;
    risultato.tm_year = a - 1900;
    mktime(&risultato);
    return risultato;
}

/*
--------------------------------------------------------
|  Funzione: calcolaSettimana
|  Scopo: Restituisce il numero della settimana dell'anno.
|  Parametri:
|    - data: struttura tm della data da analizzare
|  Ritorno: intero tra 1 e 52
--------------------------------------------------------
*/
int calcolaSettimana(struct tm data) {
    char buffer[3];
    strftime(buffer, sizeof(buffer), "%V", &data);
    return atoi(buffer);
}

/*
--------------------------------------------------------
|  Funzione: calcolaIntervalloSettimana
|  Scopo: Calcola lunedì e domenica della settimana di riferimento.
|  Parametri:
|    - base: struct tm base (data appartenente alla settimana)
|    - inizio: puntatore a struct tm da riempire con lunedì
|    - fine: puntatore a struct tm da riempire con domenica
|  Ritorno: Nessuno
--------------------------------------------------------
*/
void calcolaIntervalloSettimana(struct tm base, struct tm *inizio, struct tm *fine) {
    *inizio = base;
    while (inizio->tm_wday != 1) { // 1 = lunedì
        inizio->tm_mday--;
        mktime(inizio);
    }
    *fine = *inizio;
    fine->tm_mday += 6;
    mktime(fine);
}
