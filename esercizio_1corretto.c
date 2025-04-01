#include <stdio.h>
#include <string.h>

struct prodotto {
    char codice[15];
    char fornitore[11];
    float prezzo;
    int quantita;
};

// Funzioni di acquisizione
void acq_str(char *str) {
    scanf("%s", str);
}

int acq_quantita() {
    int x;
    do {
        printf("Inserisci la quantita: ");
        scanf("%d", &x);
    } while (x < 0);
    return x;
}

float acq_prezzo() {
    float x;
    do {
        printf("Inserisci il prezzo: ");
        scanf("%f", &x);
    } while (x <= 0);
    return x;
}

// Aggiunta
void aggiungi(struct prodotto *S, int *n) {
    printf("Codice prodotto: ");
    acq_str(S[*n].codice);
    printf("Fornitore: ");
    acq_str(S[*n].fornitore);
    S[*n].prezzo = acq_prezzo();
    S[*n].quantita = acq_quantita();
    (*n)++;
}

// Modifica
void modifica(struct prodotto *S, int n) {
    char codice[15];
    int i, trovato = 0, scelta;
    printf("Inserisci codice prodotto: ");
    acq_str(codice);
    for (i = 0; i < n; i++) {
        if (strcmp(S[i].codice, codice) == 0) {
            trovato = 1;
            printf("1) Prezzo\n2) Quantita\n3) Entrambi\nScelta: ");
            scanf("%d", &scelta);
            if (scelta == 1 || scelta == 3)
                S[i].prezzo = acq_prezzo();
            if (scelta == 2 || scelta == 3) {
                int incr;
                printf("Incremento quantita: ");
                scanf("%d", &incr);
                S[i].quantita += incr;
            }
            printf("Modifica completata.\n");
            break;
        }
    }
    if (!trovato) printf("Prodotto non trovato.\n");
}

// Cancellazione
void cancella(struct prodotto *S, int *n) {
    char codice[15];
    int i, j;
    printf("Codice da cancellare: ");
    acq_str(codice);
    for (i = 0; i < *n; i++) {
        if (strcmp(S[i].codice, codice) == 0) {
            if (S[i].quantita < 10) {
                for (j = i; j < *n - 1; j++)
                    S[j] = S[j + 1];
                (*n)--;
                printf("Prodotto cancellato.\n");
            } else {
                printf("Quantita >= 10. Non cancellato.\n");
            }
            return;
        }
    }
    printf("Prodotto non trovato.\n");
}

// Percentuale
void percentuale(struct prodotto *S, int n) {
    int i, count = 0;
    for (i = 0; i < n; i++) {
        if (S[i].prezzo > 30)
            count++;
    }
    if (n > 0)
        printf("Percentuale prodotti >30 euro: %.2f%%\n", (count * 100.0) / n);
    else
        printf("Nessun prodotto presente.\n");
}

// Media prezzi
float media_prezzi_quantita_alta(struct prodotto *S, int n) {
    int i, count = 0;
    float somma = 0;
    for (i = 0; i < n; i++) {
        if (S[i].quantita > 150) {
            somma += S[i].prezzo;
            count++;
        }
    }
    return (count == 0) ? 0.0 : somma / count;
}

// Visualizzazione prodotti per fornitore
void visualizza_prodotti_fornitore(struct prodotto *prodotti, int numero_prodotti) {
    char fornitore_ricercato[11];
    int i, trovati = 0;
    printf("Fornitore da cercare: ");
    acq_str(fornitore_ricercato);
    for (i = 0; i < numero_prodotti; i++) {
        if (strcmp(prodotti[i].fornitore, fornitore_ricercato) == 0) {
            printf("Codice: %s, Quantita: %d\n", prodotti[i].codice, prodotti[i].quantita);
            trovati++;
        }
    }
    if (!trovati)
        printf("Nessun prodotto per il fornitore %s.\n", fornitore_ricercato);
}

// Prezzo massimo con quantita > riferimento
void trova_prezzo_massimo(struct prodotto *prodotti, int numero_prodotti) {
    int riferimento, i;
    float max = -1;
    printf("Quantita riferimento: ");
    scanf("%d", &riferimento);
    for (i = 0; i < numero_prodotti; i++) {
        if (prodotti[i].quantita > riferimento && prodotti[i].prezzo > max)
            max = prodotti[i].prezzo;
    }
    if (max < 0) {
        printf("Nessun prodotto trovato.\n");
        return;
    }
    printf("Prodotti con prezzo massimo %.2f:\n", max);
    for (i = 0; i < numero_prodotti; i++) {
        if (prodotti[i].quantita > riferimento && prodotti[i].prezzo == max)
            printf("Codice: %s\n", prodotti[i].codice);
    }
}

int main() {
    struct prodotto S[MAX];
    int n = 0, scelta;
    do {
        printf("\n--- MENU ---\n");
        printf("1) Aggiunta\n2) Ordine\n3) Modifiche\n4) Cancellazione\n5) Percentuale\n6) Media\n7) Codici/Quantita per fornitore\n8) Prezzo massimo\n9) Fine\nScelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                if (n < MAX) aggiungi(S, &n);
                else printf("Spazio esaurito.\n");
                break;
            case 2: {
                int rif, i, mod = 0;
                printf("Quantita riferimento: ");
                scanf("%d", &rif);
                for (i = 0; i < n; i++) {
                    if (S[i].quantita < rif) {
                        printf("Codice: %s, Quantita: %d\n", S[i].codice, S[i].quantita);
                        mod = 1;
                    }
                }
                if (!mod) printf("Nessun prodotto con quantita inferiore al riferimento.\n");
                break;
            }
            case 3:
                modifica(S, n);
                break;
            case 4:
                cancella(S, &n);
                break;
            case 5:
                percentuale(S, n);
                break;
            case 6:
                printf("Media: %.2f\n", media_prezzi_quantita_alta(S, n));
                break;
            case 7:
                visualizza_prodotti_fornitore(S, n);
                break;
            case 8:
                trova_prezzo_massimo(S, n);
                break;
            case 9:
                printf("Fine programma.\n");
                break;
            default:
                printf("Scelta non valida.\n");
        }
    } while (scelta != 9);
    return 0;
}
