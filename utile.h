/*
========================================================
|  UTILE.H - Header delle funzioni di utilità generica
|  Autore: Daniela Lucia Ruocco
|  Descrizione: Prototipi per funzioni ausiliarie di gestione date
========================================================
*/
#include <time.h>

// Converte stringa data "gg/mm/aaaa" in struct tm
struct tm convertiData(const char *data);

// Restituisce il numero della settimana (1-52)
int calcolaSettimana(struct tm data);

// Calcola lunedì e domenica della settimana data
void calcolaIntervalloSettimana(struct tm base, struct tm *inizio, struct tm *fine);
