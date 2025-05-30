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
#define MAX_ID 100

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
|  Descrizione: Contenitore hash per gestire le attività.
|               Tiene traccia anche degli ID eliminati
|               per poterli riutilizzare.
--------------------------------------------------------
*/
typedef struct {
    Nodo* contenitori[TABELLA_DIM];
    int ultimoID;
    int idDisponibili[MAX_ID];  // Aggiunto per riutilizzare gli ID
} TabellaAttivita;

/*
========================================================
|                   PROTOTIPI FUNZIONI                |
========================================================
*/

// Crea e inizializza una nuova tabella hash vuota
TabellaAttivita* creaTabella();

// Inserisce una nuova attività nella tabella e restituisce l'ID assegnato
int inserisciAttivita(TabellaAttivita* tabella, Attivita nuova);

// Richiede all'utente i dati di una nuova attività e la restituisce
Attivita creaAttivita();

// Visualizza le attività secondo il filtro specificato (0: tutte, 1: in corso, 2: in ritardo, 3: completate)
void visualizzaAttivita(TabellaAttivita* tabella, int filtro);

// Permette all'utente di scegliere interattivamente il filtro per la visualizzazione
void visualizzaInterattiva(TabellaAttivita* tabella);

// Aggiunge ore svolte a un'attività specifica e aggiorna il suo stato
void aggiornaAttivita(TabellaAttivita* tabella, int id, int ore);

// Rimuove un'attività specifica dalla tabella tramite ID
void rimuoviAttivita(TabellaAttivita* tabella, int id);

// Mostra lo stato attuale (completata, in corso, in ritardo) di tutte le attività
void monitoraggioProgresso(TabellaAttivita* tabella);

// Genera un report raggruppando le attività per settimana di scadenza
void generaReportSettimanale(TabellaAttivita* tabella);

// Libera tutta la memoria allocata per la tabella hash
void liberaTabella(TabellaAttivita* tabella);

// Cerca un attività specifica, funge da funzione ausiliaria e viene richiamata in altre per la modifica di specifici parametri di un attività
Attivita* cercaAttivita(TabellaAttivita* tabella, int identificativo);

