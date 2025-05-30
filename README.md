#  Gestione Attività di Studio

##  Descrizione del progetto

Il progetto **Gestione Attività di Studio** è un’applicazione scritta in linguaggio **C**, progettata per aiutare gli studenti universitari (e non solo) a **monitorare, organizzare e pianificare le proprie attività di studio**. Ogni attività è memorizzata all’interno di una **tabella hash**, che consente di accedere rapidamente alle informazioni attraverso un ID univoco.

Il programma permette di:
- Aggiungere nuove attività accademiche (esami, progetti, ripassi)
- Aggiornare il tempo di studio svolto
- Verificare lo stato di avanzamento
- Rimuovere attività completate o obsolete
- Generare **report settimanali** in base alle date di scadenza
- Visualizzare in modo filtrato lo stato delle attività (in corso, completate, in ritardo)

---

##  Funzionalità principali

- **Inserimento Attività:** descrizione, corso, data di scadenza, tempo stimato, priorità.
- **Aggiornamento Progresso:** aggiunta ore svolte, aggiornamento percentuale e stato completamento.
- **Rimozione Attività:** libera l’ID per il riutilizzo.
- **Visualizzazione filtrata:** tutte, completate, in corso, in ritardo.
- **Monitoraggio avanzato:** stato temporale + progresso percentuale.
- **Report Settimanale:** visualizzazione delle attività raggruppate per settimana/anno.
- **Gestione Date:** parsing, validazione, calcolo settimana ISO e intervallo settimanale.
- **Test automatici:** validazione delle funzioni con output controllato.

---

##  Struttura del progetto

###  Codice Sorgente

| File            | Descrizione |
|-----------------|-------------|
| `main.c`        | Gestisce il menu utente e coordina l’esecuzione delle funzioni principali. |
| `attivita.c`    | Implementazione delle operazioni principali (inserimento, aggiornamento, rimozione, visualizzazione, report). |
| `attivita.h`    | Definisce le strutture dati (`Attivita`, `Nodo`, `TabellaAttivita`) e i prototipi delle funzioni pubbliche. |
| `utile.c`       | Funzioni di supporto per la gestione delle date (validazione, parsing, calcolo settimana). |
| `utile.h`       | Prototipi delle funzioni temporali ausiliarie. |

###  Test

| File            | Descrizione |
|-----------------|-------------|
| `test1.c`       | Test su inserimento e visualizzazione attività. |
| `test2.c`       | Test aggiornamento progresso e verifica stato completato. |
| `test3.c`       | Test generazione del report settimanale. |

###  File di Test I/O

| File                | Scopo |
|---------------------|-------|
| `test1.in/out`      | Input e oracolo per test inserimento attività. |
| `test2.in/out`      | Input e oracolo per test aggiornamento ore svolte. |
| `test3.in/out`      | Input e oracolo per test report settimanale. |
| `*.actual`          | Output generati automaticamente dai test. |

###  Build System

| File        | Descrizione |
|-------------|-------------|
| `Makefile`  | Contiene i comandi per compilare, eseguire e testare il progetto. |

###  Extra

| File        | Descrizione |
|-------------|-------------|
| `README.md` | Documentazione dettagliata del progetto. |
| `.gitignore`| Esclude file binari e temporanei (`.o`, `.exe`, output test...). |

---

##  Requisiti

- Sistema operativo: Linux / macOS / Windows (con GCC o compatibile)
- Compilatore C standard (es: `gcc`)
- Make (facoltativo ma consigliato per uso con `Makefile`)

---

##  Come scaricare e compilare

###  Clona il repository

```bash
git clone https://github.com/tuo-utente/gestione-attivita-studio.git
cd gestione-attivita-studio
```

###  Compilazione

Con `Makefile`:
```bash
make        # Compila main.exe
make test   # Esegue tutti i test automatici
make clean  # Rimuove file oggetto ed eseguibili
```

Oppure manualmente:
```bash
gcc main.c attivita.c utile.c -o main.exe
```

---

## ▶ Come eseguire

```bash
./main.exe
```

Il programma avvierà un **menu interattivo** che guida l’utente attraverso le funzionalità disponibili:

1. Aggiungi nuova attività  
2. Visualizza tutte le attività (filtrabili)  
3. Rimuovi attività tramite ID  
4. Aggiorna ore svolte  
5. Monitoraggio del progresso  
6. Genera report settimanale  
7. Esci

---

##  Esempio di attività

Durante l’inserimento verranno richiesti:

```txt
Descrizione attività: Ripasso Sistemi
Corso: Sistemi Operativi
Data di scadenza (gg/mm/aaaa): 30/05/2025
Tempo stimato (in ore): 5
Priorità (0=bassa, 1=media, 2=alta): 1
```

E il sistema genererà un ID univoco da utilizzare nelle operazioni future (es. aggiornamento o rimozione).

---

##  Output dei test automatici

Al termine di ogni test (`make test`), il sistema genera file `.actual` confrontati con `.out`.

Messaggi esemplificativi:
```txt
TEST 1: PASS ✅
TEST 2: FAIL ❌  (output differente dall’oracolo)
```

---

##  Estendibilità futura

Il progetto è pensato per essere **modulare ed estendibile**, con possibili funzionalità aggiuntive:

- Salvataggio e caricamento delle attività da file CSV
- Esportazione del report in PDF o HTML
- Ordinamento per priorità o scadenza

---

##  Autrice

> Daniela Lucia Ruocco  
> Università degli Studi di Salerno  
> Matricola: 0512122089  

---

##  Licenza

Questo progetto è distribuito con **licenza libera** per uso accademico o personale.

---
