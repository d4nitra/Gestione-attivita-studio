# 📘 Gestione Attività di Studio

## 🎯 Obiettivo
Il progetto ha lo scopo di aiutare uno studente a monitorare e gestire le proprie attività accademiche, come studio, ripasso, esercitazioni e progetti. Ogni attività viene registrata in una **tabella hash** tramite un **ID univoco**.

---

## 📁 Struttura dei file

### 🔧 File di Implementazione (C)

| File             | Descrizione |
|------------------|-------------|
| `main.c`         | Contiene il **menu interattivo** e gestisce l'interazione con l'utente. È il punto di ingresso del programma. |
| `attivita.c`     | Implementa tutte le **funzioni relative alla gestione delle attività**, inclusi inserimento, aggiornamento, rimozione, monitoraggio e report settimanale. |
| `utile.c`        | Contiene **funzioni di supporto** come la validazione delle date, il calcolo della settimana e conversioni da stringhe a `struct tm`. |

---

### 🧠 Header File (H)

| File             | Descrizione |
|------------------|-------------|
| `attivita.h`     | Dichiara le strutture dati (`Attivita`, `Nodo`, `TabellaAttivita`) e i **prototipi delle funzioni** pubbliche per gestire la tabella hash. |
| `utile.h`        | Dichiara le **funzioni ausiliarie** usate da `attivita.c` per la gestione delle date e operazioni temporali. |

---

### 🧪 File di Test

| File             | Descrizione |
|------------------|-------------|
| `test1.c`        | Verifica l’inserimento corretto di più attività e confronta l’output generato con l’oracolo `test1.out`. |
| `test2.c`        | Testa l’aggiornamento del progresso di un’attività e verifica la corretta gestione delle ore. |
| `test3.c`        | Controlla la generazione del **report settimanale**, inclusi i raggruppamenti per settimana. |

---

### 📄 File di Test I/O

| File             | Scopo |
|------------------|-------|
| `test1.in/out`   | Input e output atteso per test inserimento. |
| `test2.in/out`   | Input e output atteso per test aggiornamento progresso. |
| `test3.in/out`   | Input e output atteso per test report settimanale. |

---

### 🛠 Makefile

| Target        | Descrizione |
|---------------|-------------|
| `make`        | Compila `main.exe` |
| `make run`    | Esegue il programma principale |
| `make clean`  | Rimuove i file oggetto ed eseguibili |
| `make test`   | Esegue tutti i test (`test1`, `test2`, `test3`) |

---

## 🗃 ADT utilizzato
Il progetto utilizza una **tabella hash** per l’efficienza nella ricerca, aggiornamento e rimozione delle attività, garantendo tempo costante (O(1)) nelle operazioni medie.

---

## 🧩 Estendibilità
Il progetto è facilmente estendibile per includere:
- Salvataggio su file CSV
- Ordinamento personalizzato
- Visualizzazione per corso, priorità o scadenza

---

## 👩‍💻 Autrice
**Daniela Lucia Ruocco** – Università degli Studi

