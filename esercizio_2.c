/*Si supponga di voler simulare la gestione degli abbonati ad un servizio televisivo a pagamento, 
avendo per ciascun abbonamento le seguenti informazioni:
 
codice di abbonamento (15 caratteri)
tipo di pagamento ("trimestrale" o "annuale")
Importo
anni di rinnovo
data inizio abbonamento (aaaa/mm/gg)
                                                                 
Si richiede di gestire alcune delle operazioni fondamentali impostando un menù ripetibile con le seguenti opzioni:
 
1. Nuovo abbonamento 
2. Cancellazione abbonamento                                                                                        
3. Gestione rinnovo                                                                                              
4. Vettore abbonati fedeli                                                                              
5. Elaborazioni                                                                                         
6. Fine
 
La prima richiesta prevede di aggiungere i dati di un nuovo abbonamento chiedendo all’utente le sole informazioni necessarie.
La cancellazione di un abbonamento prevede l’eliminazione di tutte le informazioni ad esso relative: viene fornito il codice.

La gestione del rinnovo prevede di rinnovare un abbonamento annuale di cui viene dato il codice: si deve aggiornare il numero 
di anni di rinnovo e consentire all’utente di modificare il tipo di pagamento e/o l’importo.

Il quarto punto prevede la costruzione di un vettore che contiene i codici e gli anni di rinnovo per gli abbonamenti precedenti 
ad una data di riferimento. Dopo averlo costruito, si deve visualizzare il vettore.

Il punto 5 prevede di visualizzare tutti i codici degli abbonamenti con importo massimo e la percentuale dei nuovi abbonati (0 anni di rinnovo).

Si richiede l’impostazione di un programma in C scritto in base alle regole della programmazione strutturata. 
Si devono scrivere almeno 7 funzioni di cui 3 con il return e 3 con il passaggio parametri per indirizzo.*/

#include <stdio.h>
#include <string.h>

struct abbonamento{
    char codice[16], tipo[10], data[11];
    float importo;
    int anni_di_rinnovo;
};

void acq_stringa(char *X){
    printf("fornisci stringa");
    scanf("%s", X);
}

float acq_importo (){
    float x;
    do {
        printf("fornisci l'importo");
        scanf("%f", &x);
    } while (x<=0);
    return x;
}

int acq_anni (){
    int x;
    do {
        printf("fornisci il numero di anni di rinnovo");
        scanf("%d", &x);
    } while (x<0);
    return x;
}

void aggiungi(struct abbonamento *a, int *n){
    printf("fornisci il codice");
    acq_stringa(a[*n].codice);
    printf("tipo");
    acq_stringa(a[*n].tipo);
    printf("data di iscrizione");
    acq_stringa(a[*n].data);
    a[*n].importo = acq_importo();
    a[*n].anni_di_rinnovo = acq_anni();
    (*n)++;
}

void cancella(struct abbonamento *a, int *n){
    char codice_eliminato[16];

    printf("fornisci il codide da cancellare");
    acq_stringa(codice_eliminato);

    for(int i=0; i<*n; i++){
        if (strcmp(a[i].codice, codice_eliminato)==0){
            for(int j=0; j<*n-1; j++){
                a[j] = a[j + 1];
            }
            (*n)--;
        }
    }
}

void modifica (struct abbonamento *a, int *n){
    int trovato=0;
    char codice_modifica[16];
    acq_stringa(codice_modifica);

    for (int i=0; i<n; i++){
        if (strcmp(a[i].codice, codice_modifica)==0){
            if (strcmp(a[i].tipo, "annuale")==0){ //mettere le virgolette sua annuale
                a[i].anni_di_rinnovo++;
                printf("Rinnovo effettuato. Anni di rinnovo attuali: %d\n", a[i].anni_di_rinnovo);

                                // Modifica tipo pagamento
                char scelta;
                printf("Vuoi modificare il tipo di pagamento? (s/n): ");
                scanf(" %c", &scelta);  // lo spazio prima di %c serve a ignorare eventuali newline

                if (scelta == 's' || scelta == 'S') {
                    printf("Nuovo tipo di pagamento (annuale/trimestrale): ");
                    scanf("%s", a[i].tipo);
                }

                // Modifica importo
                printf("Vuoi modificare l'importo? (s/n): ");
                scanf(" %c", &scelta);

                if (scelta == 's' || scelta == 'S') {
                    printf("Nuovo importo: ");
                    scanf("%f", &a[i].importo);
                }

            } else {
                printf("L’abbonamento non è di tipo annuale. Nessun rinnovo effettuato.\n");
            }
        }
    }

    if (!trovato) {
        printf("Codice non trovato.\n");
    }
}

void costruisci_vettore(struct abbonamento *a, int n){
    char data_riferimento[11];
    char codici [16];
    int anni;
    int k=0;

    printf("fornire la data di riferimento");
    acq_stringa(data_riferimento);

    for (int i=0; i<n; i++){
        if (strcmp(a[i].data, data_riferimento)<0){
            strcpy(codici[k], a[i].codice);
            anni[k] = a[i].anni_di_rinnovo;
            k++;
        }
    }
    if (k == 0) {
        printf("Nessun abbonato fedele trovato.\n");
    } else {
        printf("Abbonati fedeli trovati prima della data %s:\n", data_riferimento);
        for (int i = 0; i < k; i++) {
            printf("- Codice: %s, Anni di rinnovo: %d\n", codici[i], anni[i]);
        }
    }
}

float percentuale (int contp, int n, float perc){
    perc = contp/n*100;
    return perc;
}

void visualizzazione_case_5 (struct abbonamento *a, int *n){
    float max=0;

    for(int i = 0; i<n; i++){
        if(a[i].importo>max){
            max = a[i].importo;
        }
    }

    for (int i=0; i<n; i++){
        if (a[i].importo == max){
            printf("%s", a[i].codice);
        }
    }

    int contp=0;

    for (int i=0; i<n; i++){
        if (a[i].anni_di_rinnovo == 0){
            contp++;
        }
    }
    float perc = calcola_percentuale(contp, n);
}

int main (){
    int n=0, scelta;
    struct abbonamento a[10];

    do{
        printf("--MENU--");
        printf("fare scelta");
        scanf("%d", &scelta);

        switch(scelta){
            case 1:{
                printf("--PRIMO PROGRAMMA--");
                if (n<10){
                    aggiungi(a,&n);
                } else printf("full");
            }break;
            
            case 2:{
                printf("--SECONDO PROGRAMMA--");
                cancella (a,&n);
            }break;
            
            case 3:{
                printf("--TERZO PROGRAMMA--");
                modifica (a, &n);
            }break;

            case 4:{
                printf("--QUARTO PROGRAMMA--");
                costruzione_vettore(a, &n);
            }break;

            case 5:{
                printf("--QUINTO PROGRAMMA--");
                visualizza_case_5(a, &n);
            }break;

            default:printf("fine programma");
        }
    }while (scelta!=5);
    return 0;
}