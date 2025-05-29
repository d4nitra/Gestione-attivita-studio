/*
========================================================
|  ATTIVITA.H - Header per la gestione della tabella hash
|  Autore: Daniela Lucia Ruocco
|  Data: 21/05/2025
|  Descrizione: Interfaccia delle funzioni e strutture
|               utilizzate per gestire le attività
|               tramite tabella hash.
========================================================
*/

#include <stdio.h>

#define MAX_DESC 100
#define MAX_CORSO 50
#define MAX_DATA 11
#define TABELLA_DIM 101

/*
--------------------------------------------------------
|  Struttura: Attivita
|  Descrizione: Modello che rappresenta un'attività
|               inserita dallo studente
--------------------------------------------------------
*/
typedef struct {
    int id;                         // Identificativo univoco
    char descrizione[MAX_DESC];     // Descrizione sintetica
    char corso[MAX_CORSO];          // Corso di appartenenza
    char dataScadenza[MAX_DATA];    // Scadenza nel formato gg/mm/aaaa
    int tempoStimato;               // Tempo previsto in ore
    int oreSvolte;                  // Ore effettivamente svolte
    int priorita;                   // 0=bassa, 1=media, 2=alta
    int completato;                 // 1=completato, 0=incompleto
} Attivita;

/*
--------------------------------------------------------
|  Struttura: Nodo
|  Descrizione: Nodo per la lista concatenata in ogni
|               slot della tabella hash
--------------------------------------------------------
*/
typedef struct Nodo {
    Attivita attivita;
    struct Nodo* successivo;
} Nodo;

/*
--------------------------------------------------------
|  Struttura: TabellaAttivita
|  Descrizione: Contenitore hash per gestire le attività
--------------------------------------------------------
*/
typedef struct {
    Nodo* contenitori[TABELLA_DIM];
    int ultimoID;
} TabellaAttivita;

/*
========================================================
|                   PROTOTIPI FUNZIONI                |
========================================================
*/

// Crea e inizializza una nuova tabella
TabellaAttivita* creaTabella();

// Inserisce una nuova attività, restituendo il suo ID
int inserisciAttivita(TabellaAttivita* tabella, Attivita nuova);

// Mostra tutte le attività salvate
void visualizzaAttivita(TabellaAttivita* tabella);

// Cerca un'attività tramite ID
Attivita* cercaAttivita(TabellaAttivita* tabella, int identificativo);

// Aggiorna le ore svolte di un'attività
void aggiornaAttivita(TabellaAttivita* tabella, int identificativo, int ore);

// Rimuove un'attività in base all'ID
void rimuoviAttivita(TabellaAttivita* tabella, int identificativo);

// Dealloca la memoria della tabella
void liberaTabella(TabellaAttivita* tabella);

// Crea una nuova attività acquisendo dati dall'utente
Attivita creaAttivita();

// Stampa stato temporale delle attività
void monitoraggioProgresso(TabellaAttivita* tabella);

// Stampa report settimanale delle attività
void generaReportSettimanale(TabellaAttivita* tabella);


