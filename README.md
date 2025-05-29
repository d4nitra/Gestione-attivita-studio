#  Gestione Attività di Studio

##  Obiettivo
Il progetto ha lo scopo di aiutare uno studente a monitorare e gestire le proprie attività accademiche, come studio, ripasso, esercitazioni e progetti. Ogni attività viene registrata in una **tabella hash** tramite un **ID univoco** che la identifica per successive ricerche e modifiche che possono riguardarla.

---

##  Struttura dei file

###  File di Implementazione (C)

| File             | Descrizione |
|------------------|-------------|
| `main.c`         | Contiene il **menu interattivo** e gestisce l'interazione con l'utente. È il punto di ingresso del programma. |
| `attivita.c`     | Implementa tutte le **funzioni relative alla gestione delle attività**, inclusi inserimento, aggiornamento, rimozione, monitoraggio e report settimanale. |
| `utile.c`        | Contiene **funzioni di supporto** come la validazione delle date, il calcolo della settimana e conversioni da stringhe a `struct tm`. |

---

###  Header File (H)

| File             | Descrizione |
|------------------|-------------|
| `attivita.h`     | Dichiara le strutture dati (`Attivita`, `Nodo`, `TabellaAttivita`) e i **prototipi delle funzioni** pubbliche per gestire la tabella hash. |
| `utile.h`        | Dichiara le **funzioni ausiliarie** usate da `attivita.c` per la gestione delle date e operazioni temporali. |

---

###  File di Test

| File             | Descrizione |
|------------------|-------------|
| `test1.c`        | Verifica l’inserimento corretto di più attività e confronta l’output generato ovvero `test1.actual` con l’oracolo `test1.out`e visualizza a video messaggio di successo o fallimento . |
| `test2.c`        | Testa l’aggiornamento del progresso di un’attività e verifica la corretta gestione delle ore confrontando l’output generato ovvero `test2.actual` con l’oracolo `test2.out`e visualizza a video messaggio di successo o fallimento . |
| `test3.c`        | Controlla la corretta generazione del **report settimanale**, inclusi i raggruppamenti per settimana l’output generato ovvero `test3.actual` con l’oracolo `test3.out` e visualizza a video messaggio di successo o fallimento . |

---

###  File di Test I/O

| File             | Scopo |
|------------------|-------|
| `test1.in/out`   | Input e output atteso per test inserimento. |
| `test2.in/out`   | Input e output atteso per test aggiornamento progresso. |
| `test3.in/out`   | Input e output atteso per test report settimanale. |

---

###  Makefile

| Target        | Descrizione |
|---------------|-------------|
| `make`        | Compila `main.exe` |
| `make run`    | Esegue il programma principale |
| `make clean`  | Rimuove i file oggetto ed eseguibili |
| `make test`   | Esegue tutti i test (`test1`, `test2`, `test3`) |

---

##  ADT utilizzato
Il progetto utilizza una **tabella hash** per l’efficienza nella ricerca, aggiornamento e rimozione delle attività, garantendo tempo costante (O(1)) nelle operazioni medie.

---

##  Estendibilità
Il progetto è facilmente estendibile per includere:
- Salvataggio su file CSV
- Ordinamento personalizzato
- Visualizzazione per corso, priorità o scadenza
Esso si presta inoltre a successive modifiche per ottimizzazioni future, come possibili riutilizzi di chiavi appartenenti ad attività rimosse.

---
##  Report PDF

All'interno del progetto è incluso un **report PDF** che documenta:

-  **Motivazione della scelta dell'ADT** (Tabella Hash)
-  **Progettazione** modulare e struttura del codice
-  **Razionale dei Casi di Test** con risultati `PASS/FAIL`
-  **Specifica Sintattica e Semantica** delle funzioni

Il report segue le linee guida formattive (font, margini, intestazioni) consigliate ed è stato realizzato per supportare una **valutazione completa e professionale** del progetto.

##  Autrice
**Daniela Lucia Ruocco Matricola 0512122089** – Università degli Studi di Salerno

