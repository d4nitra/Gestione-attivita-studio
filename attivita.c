/*
========================================================
|  ATTIVITA.C - Implementazione delle funzioni per la gestione
|               delle attività di studio.
|  Autore: Daniela Lucia Ruocco
|  Data: 17/05/2025
|  Descrizione: Questo file contiene le implementazioni delle
|               funzioni dichiarate nel file header "attivita.h".
========================================================
*/

#include "attivita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
/*
--------------------------------------------------------
|  Funzione: creaLista
|  Scopo: Inizializza una lista di attività vuota.
|  Parametri: Nessuno.
|  Ritorno: Un puntatore a ListaAttivita (NULL).
--------------------------------------------------------
*/
ListaAttivita creaLista() {
    return NULL;
}

/*
--------------------------------------------------------
|  Funzione: aggiungiAttivita
|  Scopo: Aggiunge una nuova attività in testa alla lista.
|  Parametri:
|    - lista: puntatore alla lista di attività.
|    - nuovaAttivita: struttura Attivita da inserire.
|  Ritorno: Nessuno.
--------------------------------------------------------
*/
void aggiungiAttivita(ListaAttivita *lista, Attivita nuovaAttivita) {
    Nodo *nuovoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuovoNodo->attivita = nuovaAttivita;
    nuovoNodo->next = *lista;
    *lista = nuovoNodo;
}

/*
--------------------------------------------------------
|  Funzione: visualizzaAttivita
|  Scopo: Visualizza tutte le attività presenti nella lista.
|  Parametri:
|    - lista: puntatore alla lista di attività.
|  Ritorno: Nessuno.
--------------------------------------------------------
*/
void visualizzaAttivita(ListaAttivita lista) {
    while (lista != NULL) {
        float progresso = (lista->attivita.tempoStimato > 0)
            ? ((float)lista->attivita.oreSvolte / lista->attivita.tempoStimato) * 100.0f
            : 0.0f;

        printf("\nDescrizione dell'attività: %s", lista->attivita.descrizione);
        printf("\nCorso di appartenenza: %s", lista->attivita.corso);
        printf("\nData di scadenza: %s", lista->attivita.dataScadenza);
        printf("\nTempo stimato da dedicare all'attività: %d ore", lista->attivita.tempoStimato);
        printf("\nOre svolte: %d", lista->attivita.oreSvolte);
        printf("\nCompletato: %s", lista->attivita.completato ? "Sì" : "No");
        printf("\nPriorità: %s", lista->attivita.priorita == 2 ? "Alta" : lista->attivita.priorita == 1 ? "Media" : "Bassa");
        printf("\nProgresso: %.2f%%\n", progresso);
        lista = lista->next;
    }
}

/*
--------------------------------------------------------
|  Funzione: ricercaAttivita
|  Scopo: Cerca un'attività nella lista tramite descrizione.
|  Parametri:
|    - lista: puntatore alla lista di attività.
|    - descrizione: stringa con la descrizione dell'attività da cercare.
|  Ritorno: Puntatore al nodo trovato o NULL se non esiste.
--------------------------------------------------------
*/
Nodo* ricercaAttivita(ListaAttivita lista, const char *descrizione) {
    while (lista != NULL) {
        if (strcmp(lista->attivita.descrizione, descrizione) == 0)
            return lista;
        lista = lista->next;
    }
    return NULL;
}
/*
--------------------------------------------------------
|  Funzione: aggiornaAttivita
|  Scopo: Aggiorna le ore svolte per un'attività e calcola il nuovo progresso.
|  Parametri:
|    - lista: lista delle attività.
|    - descrizione: descrizione dell'attività da aggiornare.
|    - oreAggiunte: ore da sommare alle ore già svolte.
|  Ritorno: Nessuno.
--------------------------------------------------------
*/
void aggiornaAttivita(ListaAttivita lista, const char *descrizione, int oreAggiunte) {
    Nodo *attivita = ricercaAttivita(lista, descrizione);
    if (attivita == NULL) {
        printf("Attività non trovata.\n");
        return;
    }

    attivita->attivita.oreSvolte += oreAggiunte;

    if (attivita->attivita.oreSvolte >= attivita->attivita.tempoStimato) {
        attivita->attivita.completato = 1;
        printf("Attività completata!\n");
    } else {
        float progresso = ((float)attivita->attivita.oreSvolte / attivita->attivita.tempoStimato) * 100.0f;
        printf("Progresso aggiornato: %.2f%% completato (%d/%d ore).\n",
               progresso,
               attivita->attivita.oreSvolte,
               attivita->attivita.tempoStimato);
    }
}

/*
--------------------------------------------------------
|  Funzione: monitoraggioProgresso
|  Scopo: Analizza le date di scadenza di ciascuna attività
|         confrontandole con la data corrente e stampa per ognuna
|         se è completata, in corso o in ritardo.
|  Parametri:
|    - lista: puntatore alla testa della lista di attività.
|  Ritorno: Nessuno.
--------------------------------------------------------
*/
void monitoraggioProgresso(ListaAttivita lista) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("\n--- Monitoraggio del Progresso ---\n");

    while (lista != NULL) {
        int giorno, mese, anno;
        sscanf(lista->attivita.dataScadenza, "%d/%d/%d", &giorno, &mese, &anno);
        int giorni_rimanenti = (anno - (tm.tm_year + 1900)) * 365 + (mese - (tm.tm_mon + 1)) * 30 + (giorno - tm.tm_mday);

        printf("\nAttività: %s\n", lista->attivita.descrizione);
        if (lista->attivita.completato) {
            printf("Stato: ✅ Completata\n");
        } else if (giorni_rimanenti >= 0) {
            printf("Stato: ⏳ In corso (%d giorni rimanenti)\n", giorni_rimanenti);
        } else {
            printf("Stato: ❌ In ritardo (%d giorni di ritardo)\n", -giorni_rimanenti);
        }
        lista = lista->next;
    }
}

/*
--------------------------------------------------------
|  Funzione: generaReportSettimanale
|  Scopo: Genera un report suddividendo le attività in tre categorie:
|         completate, in corso e in ritardo, e le stampa su schermo.
|  Parametri:
|    - lista: puntatore alla testa della lista delle attività.
|  Ritorno: Nessuno.
--------------------------------------------------------
*/
void generaReportSettimanale(ListaAttivita lista) {
    printf("\n--- Report Settimanale ---\n");
    printf("\n✅ Attività Completate:\n");
    ListaAttivita temp = lista;
    while (temp != NULL) {
        if (temp->attivita.completato) {
            printf("- %s (%s)\n", temp->attivita.descrizione, temp->attivita.dataScadenza);
        }
        temp = temp->next;
    }

    printf("\n⏳ Attività in Corso:\n");
    temp = lista;
    while (temp != NULL) {
        if (!temp->attivita.completato) {
            int giorno, mese, anno;
            sscanf(temp->attivita.dataScadenza, "%d/%d/%d", &giorno, &mese, &anno);
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            int giorni_rimanenti = (anno - (tm.tm_year + 1900)) * 365 + (mese - (tm.tm_mon + 1)) * 30 + (giorno - tm.tm_mday);
            if (giorni_rimanenti >= 0) {
                printf("- %s (%d giorni rimanenti)\n", temp->attivita.descrizione, giorni_rimanenti);
            }
        }
        temp = temp->next;
    }

    printf("\n❌ Attività in Ritardo:\n");
    temp = lista;
    while (temp != NULL) {
        if (!temp->attivita.completato) {
            int giorno, mese, anno;
            sscanf(temp->attivita.dataScadenza, "%d/%d/%d", &giorno, &mese, &anno);
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            int giorni_rimanenti = (anno - (tm.tm_year + 1900)) * 365 + (mese - (tm.tm_mon + 1)) * 30 + (giorno - tm.tm_mday);
            if (giorni_rimanenti < 0) {
                printf("- %s (%d giorni di ritardo)\n", temp->attivita.descrizione, -giorni_rimanenti);
            }
        }
        temp = temp->next;
    }
}

/*
--------------------------------------------------------
|  Funzione: rimuoviAttivita
|  Scopo: Rimuove un'attività dalla lista tramite descrizione.
|  Parametri:
|    - lista: puntatore alla lista di attività.
|    - descrizione: stringa con la descrizione dell'attività da rimuovere.
|  Ritorno: Nessuno.
--------------------------------------------------------
*/
void rimuoviAttivita(ListaAttivita *lista, const char *descrizione) {
    Nodo *curr = *lista;
    Nodo *prev = NULL;

    while (curr != NULL && strcmp(curr->attivita.descrizione, descrizione) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Attività non trovata!\n");
        return;
    }

    if (prev == NULL) {
        *lista = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(curr);
    printf("Attività rimossa correttamente!\n");
}

/*
--------------------------------------------------------
|  Funzione: liberaMemoria
|  Scopo: Libera tutta la memoria allocata per la lista.
|  Parametri:
|    - lista: puntatore alla lista di attività.
|  Ritorno: Nessuno.
--------------------------------------------------------
*/
void liberaMemoria(ListaAttivita *lista) {
    Nodo *temp;
    while (*lista != NULL) {
        temp = *lista;
        *lista = (*lista)->next;
        free(temp);
    }
}

/*
--------------------------------------------------------
|  Funzione: creaAttivita
|  Scopo: Crea una nuova attività chiedendo i dati all'utente.
|  Parametri: Nessuno.
|  Ritorno: Una struttura Attivita compilata con i dati forniti.
--------------------------------------------------------
*/
Attivita creaAttivita() {
    Attivita nuova;
    printf("Breve descrizione dell'attività(max 100 caratteri): ");
    fgets(nuova.descrizione, MAX_DESC, stdin);
    nuova.descrizione[strcspn(nuova.descrizione, "\n")] = 0;

    printf("Corso: ");
    fgets(nuova.corso, MAX_CORSO, stdin);
    nuova.corso[strcspn(nuova.corso, "\n")] = 0;

    printf("Data di scadenza (gg/mm/aaaa): ");
    fgets(nuova.dataScadenza, MAX_DATE, stdin);
    nuova.dataScadenza[strcspn(nuova.dataScadenza, "\n")] = 0;

    printf("Tempo stimato da dedicare all'attività(in ore): ");
    scanf("%d", &nuova.tempoStimato);

    printf("Priorità (0: Bassa, 1: Media, 2: Alta): ");
    scanf("%d", &nuova.priorita);

    nuova.completato = 0;
     nuova.oreSvolte = 0;
    getchar(); // Pulisce il buffer dello stdin

    return nuova;
}
