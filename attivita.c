/*
========================================================
|  ATTIVITA.C - Implementazione gestione tabella hash attività
|  Autore: Daniela Lucia Ruocco
|  Data: 21/05/2025
|  Descrizione: Gestione delle operazioni su una tabella hash
|               contenente attività di studio.
========================================================
*/
#include "attivita.h"
#include "utile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
--------------------------------------------------------
|  Funzione: funzioneHash
|  Scopo: Calcola l'indice della tabella hash a partire da un ID.
|  Parametri:
|    - id: ID numerico dell'attività.
|  Ritorno: Indice della tabella hash corrispondente.
--------------------------------------------------------
*/
int funzioneHash(int identificativo) {
    return identificativo % TABELLA_DIM;
}

/*
--------------------------------------------------------
|  Funzione: creaTabella
|  Scopo: Inizializza una nuova tabella hash.
|  Parametri: Nessuno.
|  Ritorno: Puntatore alla nuova struttura HashTableAttivita.
--------------------------------------------------------
*/
TabellaAttivita* creaTabella() {
    TabellaAttivita* tabella = malloc(sizeof(TabellaAttivita));
    if (tabella) {
        for (int i = 0; i < TABELLA_DIM; i++) tabella->contenitori[i] = NULL;
        tabella->ultimoID = 1;
        for (int i = 0; i < MAX_ID; i++) tabella->idDisponibili[i] = 0;
    }
    return tabella;
}

/*
--------------------------------------------------------
|  Funzione: inserisciAttivita
|  Scopo: Inserisce una nuova attività nella tabella hash.
|  Parametri:
|    - tabella: puntatore alla struttura HashTableAttivita.
|    - nuova: struttura Attivita da inserire.
|  Ritorno: ID assegnato all'attività.
--------------------------------------------------------
*/
int inserisciAttivita(TabellaAttivita* tabella, Attivita nuova) {
    int nuovoID = -1;
    for (int i = 1; i < MAX_ID; i++) {
        if (tabella->idDisponibili[i]) {
            nuovoID = i;
            tabella->idDisponibili[i] = 0;
            break;
        }
    }
    if (nuovoID == -1) nuovoID = tabella->ultimoID++;

    nuova.id = nuovoID;
    int indice = funzioneHash(nuova.id);

    Nodo* nuovoNodo = malloc(sizeof(Nodo));
    nuovoNodo->attivita = nuova;
    nuovoNodo->successivo = tabella->contenitori[indice];
    tabella->contenitori[indice] = nuovoNodo;

    return nuova.id;
}


/*
--------------------------------------------------------
|  Funzione: visualizzaAttivita
|  Scopo: Mostra le attività filtrate della tabella hash
|  Parametri:
|    - tabella: puntatore alla TabellaAttivita
|    - filtro: 0 tutte, 1 completate, 2 in corso, 3 in ritardo
|  Ritorno: Nessuno
--------------------------------------------------------
*/
void visualizzaAttivita(TabellaAttivita* tabella, int filtro) {
    if (!tabella) {
        printf("Tabella non inizializzata.\n");
        return;
    }

    time_t ora = time(NULL);
    struct tm oggi = *localtime(&ora);

    for (int i = 0; i < TABELLA_DIM; i++) {
        Nodo* nodo = tabella->contenitori[i];
        while (nodo != NULL) {
            Attivita a = nodo->attivita;
            struct tm scadenza = convertiData(a.dataScadenza);
            int giorni = difftime(mktime(&scadenza), mktime(&oggi)) / (60 * 60 * 24);
            int mostra = 0;

            if (filtro == 1) mostra = 1;
            else if (filtro == 2 && a.completato) mostra = 1;
            else if (filtro == 3 && !a.completato && giorni >= 0) mostra = 1;
            else if (filtro == 4 && !a.completato && giorni < 0) mostra = 1;

            if (mostra) {
                float progresso = (a.tempoStimato > 0) ? ((float)a.oreSvolte / a.tempoStimato) * 100 : 0;
                printf("\nID: %d\nDescrizione: %s\nCorso: %s\nScadenza: %s\nOre stimate da dedicare all'attività in totale: %d\nOre Svolte: %d\nPriorità: %s\nCompletato: %s\nProgresso percentuale: %.2f%%\n",
                       a.id, a.descrizione, a.corso, a.dataScadenza,
                       a.tempoStimato, a.oreSvolte,
                       a.priorita >= 2 ? "Alta" : a.priorita == 1 ? "Media" : "Bassa",
                       a.completato ? "Sì" : "No",
                       progresso);
            }
            nodo = nodo->successivo;
        }
    }
}

/*
--------------------------------------------------------
|  Funzione: visualizzaInterattiva
|  Scopo: Permette all'utente di scegliere il tipo di attività da visualizzare
|  Parametri:
|    - tabella: puntatore alla TabellaAttivita
|  Ritorno: Nessuno
--------------------------------------------------------
*/
void visualizzaInterattiva(TabellaAttivita* tabella) {
    int scelta;
    do {
        printf("\n--- Visualizzazione Attività ---\n");
        printf("1. Tutte le attività\n");
        printf("2. Solo completate\n");
        printf("3. Solo in corso\n");
        printf("4. Solo in ritardo\n");
        printf("Scelta: ");
        if (scanf("%d", &scelta) != 1 || scelta < 0 || scelta > 4) {
            printf("Input non valido. Inserire un numero tra 0 e 3.\n");
            while (getchar() != '\n'); // svuota il buffer
        }
    } while (scelta < 0 || scelta > 3);

    getchar(); // Pulisce il buffer dopo scanf
    visualizzaAttivita(tabella, scelta);
}


/*
--------------------------------------------------------
|  Funzione: cercaAttivita
|  Scopo: Ricerca un'attività nella tabella tramite il suo ID.
|  Parametri:
|    - tabella: puntatore alla struttura HashTableAttivita.
|    - id: identificatore numerico dell'attività.
|  Ritorno: Puntatore all'attività se trovata, NULL altrimenti.
--------------------------------------------------------
*/
Attivita* cercaAttivita(TabellaAttivita* tabella, int identificativo) {
    int indice = funzioneHash(identificativo);
    Nodo* corrente = tabella->contenitori[indice];
    while (corrente) {
        if (corrente->attivita.id == identificativo) return &corrente->attivita;
        corrente = corrente->successivo;
    }
    return NULL;
}

/*
--------------------------------------------------------
|  Funzione: aggiornaAttivita
|  Scopo: Permette all'utente di aggiornare le ore svolte
|         per una specifica attività, identificata tramite ID.
|         Verifica l'input e aggiorna lo stato e il progresso.
|  Parametri:
|    - tabella: struttura TabellaAttivita.
|    - id: identificativo della specifica attività
|    - ore: ore svolte da aggiungere per aggiornare l'attività
|  Ritorno: Nessuno.
--------------------------------------------------------
*/
void aggiornaAttivita(TabellaAttivita* tabella, int identificativo, int ore) {
    Attivita* att = cercaAttivita(tabella, identificativo);
    if (!att) {
        printf("Attività con ID %d non trovata.\n", identificativo);
        return;
    }
    att->oreSvolte += ore;
    if (att->oreSvolte >= att->tempoStimato) {
        att->completato = 1;
    }
    float progresso = att->tempoStimato > 0 ? (float)att->oreSvolte / att->tempoStimato * 100 : 0;
    printf("Progresso aggiornato: %.2f%% (%d/%d ore)\n", progresso, att->oreSvolte, att->tempoStimato);
}

/*
--------------------------------------------------------
|  Funzione: rimuoviAttivita
|  Scopo: Rimuove un'attività dalla tabella hash
|         utilizzando il suo identificativo (ID).
|         L'ID viene segnato come disponibile per un
|         futuro riutilizzo.
|  Parametri:
|    - tabella: puntatore alla struttura TabellaAttivita.
|    - identificativo: intero che rappresenta l'ID
|                      dell'attività da rimuovere.
|  Ritorno: Nessuno.
--------------------------------------------------------
*/
void rimuoviAttivita(TabellaAttivita* tabella, int identificativo) {
    int indice = funzioneHash(identificativo);
    Nodo* corrente = tabella->contenitori[indice];
    Nodo* precedente = NULL;

    // Ricerca del nodo da eliminare
    while (corrente && corrente->attivita.id != identificativo) {
        precedente = corrente;
        corrente = corrente->successivo;
    }

    // Se l'attività non è stata trovata
    if (!corrente) {
        printf("  Attività con ID %d non trovata.\n", identificativo);
        return;
    }

    // Rimozione del nodo dalla lista
    if (!precedente) {
        // Primo elemento della lista
        tabella->contenitori[indice] = corrente->successivo;
    } else {
        precedente->successivo = corrente->successivo;
    }

    // Libera la memoria e segna l'ID come disponibile
    free(corrente);
    if (identificativo >= 1 && identificativo < MAX_ID)
        tabella->idDisponibili[identificativo] = 1;

    printf(" Attività con ID %d rimossa con successo. ID ora riutilizzabile.\n", identificativo);
}

/*
--------------------------------------------------------
|  Funzione: liberaTabella
|  Scopo: Dealloca tutta la memoria usata dalla tabella hash.
|  Parametri:
|    - tabella: struttura da liberare.
|  Ritorno: Nessuno.
--------------------------------------------------------
*/
void liberaTabella(TabellaAttivita* tabella) {
    for (int i = 0; i < TABELLA_DIM; i++) {
        Nodo* corrente = tabella->contenitori[i];
        while (corrente) {
            Nodo* temp = corrente;
            corrente = corrente->successivo;
            free(temp);
        }
    }
    free(tabella);
}

/*
--------------------------------------------------------
|  Funzione: creaAttivita
|  Scopo: Crea un'attività acquisendo dati dall'utente.
|  Parametri: Nessuno.
|  Ritorno: Una nuova struttura Attivita.
--------------------------------------------------------
*/
Attivita creaAttivita() {
   Attivita nuova;
    do {
        printf("Breve descrizione dell'attività (max %d caratteri): ", MAX_DESC - 1);
        fgets(nuova.descrizione, MAX_DESC, stdin);
        nuova.descrizione[strcspn(nuova.descrizione, "\n")] = 0; // Rimuove il newline
        if (strlen(nuova.descrizione) >= MAX_DESC - 1) {
            printf(" Descrizione troppo lunga. Riprova.\n");
            // Svuota il buffer di input
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    } while (strlen(nuova.descrizione) >= MAX_DESC - 1);

    do {
        printf("Corso (max %d caratteri): ", MAX_CORSO - 1);
        fgets(nuova.corso, MAX_CORSO, stdin);
        nuova.corso[strcspn(nuova.corso, "\n")] = 0; // Rimuove il newline
        if (strlen(nuova.corso) >= MAX_CORSO - 1) {
            printf(" Nome del corso troppo lungo. Riprova.\n");
            // Svuota il buffer di input
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    } while (strlen(nuova.corso) >= MAX_CORSO - 1);

    printf(" Inserisci data di scadenza (gg/mm/aaaa)(anni supportati dal 1900 al 2100): ");
        fgets(nuova.dataScadenza, MAX_DATA, stdin);
        nuova.dataScadenza[strcspn(nuova.dataScadenza, "\n")] = 0;
    while (!dataValida(nuova.dataScadenza))
    {
        printf("Data inserita non valida! Inserisci una nuova data di scadenza (gg/mm/aaaa)(anni supportati dal 1900 al 2100): ");
        fgets(nuova.dataScadenza, MAX_DATA, stdin);
        nuova.dataScadenza[strcspn(nuova.dataScadenza, "\n")] = 0;
    }
    getchar();

    while (1) {
        printf("Tempo stimato da dedicare all'attività (in ore): ");
        char buffer[50];
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &nuova.tempoStimato) == 1 && nuova.tempoStimato > 0) {
            break;
        } else {
            printf(" Inserisci un numero intero positivo valido.\n");
        }
    }
   // Inserimento priorità con controllo di validità
    while (1) {
        printf("Priorità (0: Bassa, 1: Media, 2 o superiore: Alta): ");
        char buffer[20];
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &nuova.priorita) == 1 && nuova.priorita >= 0) {
            break;
        } else {
        printf(" Inserisci un numero intero valido maggiore o uguale a 0.\n");
        }
}

    nuova.oreSvolte = 0;
    nuova.completato = 0;
    return nuova;
}

/*
--------------------------------------------------------
|  Funzione: monitoraggioProgresso
|  Scopo: Verifica lo stato temporale di ogni attività rispetto alla data attuale. 
|  Restituisce inoltre la percentuale di progresso rispetto al completamento dell'attività
|  Parametri:
|    - tabella: struttura TabellaAttivita
|  Ritorno: Nessuno
--------------------------------------------------------
*/
void monitoraggioProgresso(TabellaAttivita* tabella) {
    time_t ora = time(NULL);
    struct tm oggi = *localtime(&ora);
    for (int i = 0; i < TABELLA_DIM; i++) {
        Nodo* nodo = tabella->contenitori[i];
        while (nodo != NULL) {
            Attivita a = nodo->attivita;
            struct tm scadenza = convertiData(a.dataScadenza);
            int giorni = difftime(mktime(&scadenza), mktime(&oggi)) / (60*60*24);
            float progresso = (a.tempoStimato > 0) ? 100.0f * a.oreSvolte / a.tempoStimato : 0;
            printf("\nAttività: %s\nProgresso: %.2f%%\n", a.descrizione, progresso);
            if (a.completato) printf("Stato: ✅ Completata\n");
            else if (giorni >= 0) printf("Stato: ⏳ In corso (%d giorni rimanenti)\n", giorni);
            else printf("Stato: ❌ In ritardo (%d giorni di ritardo)\n", -giorni);
            nodo = nodo->successivo;
        }
    }
}
/*
--------------------------------------------------------
|  Funzione: generaReportSettimanale
|  Scopo: Stampa un report settimanale delle attività presenti nella tabella
|         contestualizzando l'attività nella settimana precisa di scadenza
|         con data di inizio e fine settimana, differenziata anche per anno.
|  Parametri:
|    - tabella: struttura TabellaAttivita
|  Ritorno: Nessuno
--------------------------------------------------------
*/
void generaReportSettimanale(TabellaAttivita* tabella) {
    if (!tabella) {
        printf("⚠️ Errore: tabella non inizializzata.\n");
        return;
    }

    #define ANNO_MINIMO 1900
    #define ANNO_MASSIMO 2100
    #define MAX_SETTIMANE 54

    int stampate[ANNO_MASSIMO - ANNO_MINIMO + 1][MAX_SETTIMANE] = {0};

    for (int i = 0; i < TABELLA_DIM; i++) {
        Nodo* nodo = tabella->contenitori[i];
        while (nodo != NULL) {
            if (!dataValida(nodo->attivita.dataScadenza)) {
                nodo = nodo->successivo;
                continue;
            }

            struct tm scad = convertiData(nodo->attivita.dataScadenza);
            mktime(&scad); // normalizza la struct tm

            int sett = calcolaSettimana(scad);
            int anno = scad.tm_year + 1900;
            if (anno < ANNO_MINIMO || anno > ANNO_MASSIMO || sett < 0 || sett >= MAX_SETTIMANE) {
                nodo = nodo->successivo;
                continue;
            }

            int annoIdx = anno - ANNO_MINIMO;

            if (!stampate[annoIdx][sett]) {
                stampate[annoIdx][sett] = 1;

                struct tm inizio, fine;
                calcolaIntervalloSettimana(scad, &inizio, &fine);
                char dataI[11], dataF[11];
                strftime(dataI, sizeof(dataI), "%d/%m/%Y", &inizio);
                strftime(dataF, sizeof(dataF), "%d/%m/%Y", &fine);
                printf("\n📅 Settimana dal %s al %s\n", dataI, dataF);

                for (int j = 0; j < TABELLA_DIM; j++) {
                    Nodo* scan = tabella->contenitori[j];
                    while (scan != NULL) {
                        if (!dataValida(scan->attivita.dataScadenza)) {
                            scan = scan->successivo;
                            continue;
                        }

                        struct tm sc = convertiData(scan->attivita.dataScadenza);
                        mktime(&sc);

                        int annoScan = sc.tm_year + 1900;
                        int settScan = calcolaSettimana(sc);

                        if (annoScan == anno && settScan == sett) {
                            printf("- %s (Scadenza: %s) [%s]\n",
                                   scan->attivita.descrizione,
                                   scan->attivita.dataScadenza,
                                   scan->attivita.completato ? "✅ Completata" : 
                                   (scan->attivita.oreSvolte > 0 ? "⏳ In corso" : "❌ Non avviata"));
                        }
                        scan = scan->successivo;
                    }
                }
            }
            nodo = nodo->successivo;
        }
    }
}

