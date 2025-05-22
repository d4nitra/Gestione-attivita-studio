/*
========================================================
|  ATTIVITA.H - Header File per la gestione delle Attività di Studio
|  Autore: Daniela Lucia Ruocco
|  Data: 17/05/2025
|  Descrizione: Questo file definisce le strutture dati e i prototipi
|               delle funzioni per la gestione di una lista di attività.
========================================================
*/
 // Dichiarazioni delle costanti riguardanti la massima lunghezza di caratteri che possono costituire le variabili riguardanti il corso, la descrizione e le attività
#define MAX_DESC 100
#define MAX_CORSO 50
#define MAX_DATE 11

/*
--------------------------------------------------------
|  Struttura dati 'Attivita'
|  Descrizione: Rappresenta un'attività di studio con:
|    - Descrizione dell'attività
|    - Corso di appartenenza
|    - Data di scadenza
|    - Tempo stimato di completamento (in ore)
|    - Priorità dell'attività (0: Bassa, 1: Media, 2: Alta)
|    - Stato di completamento (0: Non completato, 1: Completato)
|    - Ore svolte (per calcolare il progresso)
--------------------------------------------------------
*/
typedef struct {
    char descrizione[MAX_DESC];   // Testo descrittivo dell'attività
    char corso[MAX_CORSO];        // Corso universitario di riferimento
    char dataScadenza[MAX_DATE];  // Data di scadenza nel formato gg/mm/aaaa
    int tempoStimato;             // Ore stimate per completare l'attività
    int priorita;                 // Priorità dell'attività (0, 1, 2)
    int completato;               // Stato di completamento (0 o 1)
    int oreSvolte;                // Ore già svolte per monitoraggio progresso
} Attivita;
/*
--------------------------------------------------------
|  Struttura dati 'Nodo'
|  Descrizione: Nodo della lista concatenata, contiene:
|    - Un'attività di tipo 'Attivita'
|    - Un puntatore al prossimo nodo della lista
--------------------------------------------------------
*/
typedef struct Nodo {
    Attivita attivita;            // Informazioni sull'attività
    struct Nodo *next;            // Puntatore al prossimo nodo
} Nodo;

// Definizione di un puntatore alla lista di attività
typedef Nodo* ListaAttivita;

/*
--------------------------------------------------------
|  Dichiarazione delle Funzioni
|  Descrizione: Prototipi delle funzioni che gestiscono
|               le operazioni principali sulla lista.
--------------------------------------------------------
*/

// Crea una lista di attività vuota
ListaAttivita creaLista();

// Aggiunge una nuova attività alla lista
void aggiungiAttivita(ListaAttivita *lista, Attivita nuovaAttivita);

// Visualizza tutte le attività presenti nella lista
void visualizzaAttivita(ListaAttivita lista);

// Cerca un'attività nella lista tramite la descrizione
Nodo* ricercaAttivita(ListaAttivita lista, const char *descrizione);

// Rimuove un'attività dalla lista tramite la descrizione
void rimuoviAttivita(ListaAttivita *lista, const char *descrizione);

// Libera la memoria allocata per la lista
void liberaMemoria(ListaAttivita *lista);

// Crea una nuova attività richiedendo i dati all'utente
Attivita creaAttivita();

// Monitora il progresso delle attività in base a scadenze e stato
void monitoraggioProgresso(ListaAttivita lista);

// Genera un report settimanale delle attività in tre categorie
void generaReportSettimanale(ListaAttivita lista);

// Aggiorna le ore svolte e lo stato di completamento di un'attività
void aggiornaAttivita(ListaAttivita lista, const char *descrizione, int oreAggiunte);
