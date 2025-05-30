/*
========================================================
|  UTILE.H - Intestazione delle Funzioni di Supporto per le Attività
|  Autore: Daniela Lucia Ruocco
|  Data: 21/05/2025
|  Descrizione: Contiene le dichiarazioni delle funzioni ausiliarie
|               per la gestione delle date e dei calcoli temporali.
========================================================
*/
#include <time.h>

/*
--------------------------------------------------------
|  Funzione: dataValida
|  Scopo: Verifica se una stringa di data è sintatticamente e semanticamente valida.
|  Parametri:
|    - data: stringa nel formato "gg/mm/aaaa".
|  Ritorno: 1 se la data è valida, 0 altrimenti.
--------------------------------------------------------
*/
int dataValida(const char* data);

/*
--------------------------------------------------------
|  Funzione: convertiData
|  Scopo: Converte una stringa di data in una struttura "tm" utilizzabile con funzioni temporali.
|  Parametri:
|    - data: stringa nel formato "gg/mm/aaaa".
|  Ritorno: una struttura "tm" contenente le informazioni temporali.
--------------------------------------------------------
*/
struct tm convertiData(const char* data);

/*
--------------------------------------------------------
|  Funzione: calcolaSettimana
|  Scopo: Restituisce il numero della settimana dell'anno a cui appartiene una certa data.
|  Parametri:
|    - data: struttura "tm" contenente una data valida.
|  Ritorno: numero intero della settimana (da 0 a 52).
--------------------------------------------------------
*/
int calcolaSettimana(struct tm data);

/*
--------------------------------------------------------
|  Funzione: calcolaIntervalloSettimana
|  Scopo: Determina le date di inizio (lunedì) e di fine (domenica) della settimana
|         in cui cade una determinata data.
|  Parametri:
|    - input: data di riferimento (struttura "tm")
|    - inizio: puntatore alla struttura "tm" che conterrà la data di lunedì
|    - fine: puntatore alla struttura "tm" che conterrà la data di domenica
|  Ritorno: Nessuno.
--------------------------------------------------------
*/
void calcolaIntervalloSettimana(struct tm input, struct tm* inizio, struct tm* fine);


