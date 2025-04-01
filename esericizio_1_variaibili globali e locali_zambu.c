/*Per un supermercato si vogliono gestire le informazioni relative ai prodotti in vendita.

Ciascun prodotto è descritto dalle informazioni:

Codice (14 caratteri)
Prezzo unitario
Quantità 
Fornitore (10 caratteri)

Quindi si deve impostare un menù ripetibile con le seguenti richieste:
1) Aggiunta: si devono inserire tutte le informazioni in fondo al vettore, chiedendo all'utente le sole informazioni necessarie, per un prodotto. 
2) Ordine: si devono visualizzare i codici dei prodotti con quantità inferiore ad un riferimento. 
3) Modifiche: si devono modificare per un prodotto, di cui viene fornito il codice, il prezzo (a sostituzione) e/o la quantità (a incremento)
4) Cancellazione: si devono cancellare tutte le informazioni di un prodotto di cui è fornito il codice solo se la quantità è inferiore a 10
5) Percentuale: dei prodotti con prezzo superiore a 30 euro
6) Media: dei prezzi dei prodotti con quantità > 150
7) Vettore dei codici e delle quantità dei prodotti di un fornitore specificato dall'utente. Si deve poi visualizzare il vettore costruito
8) Massimo dei prezzi per i prodotti con una quantità maggiore di un riferimento. Si visualizzino i codici dei prodotti con tale massimo
9) Fine

Si deve impostare un programma con almeno 6 funzioni, di cui 3 con il return e 3 con il passaggio parametri per indirizzo.
*/

#include <stdio.h>
#include <string.h>

//variabili locali: struct
struct prodotto{
    char COD[15], F[11];
    float P;
    int Q;
};

struct prodottof{
    char COD[15];
    float P;
};


//funzioni
void acq_stringa (char *X) {
    printf("Fornisci stringa\n");
    scanf("%s", X);
}

float acq_prezzo () {
    float X;

    do{
        printf("Fornisci prezzo prodotto\n");
        scanf("%f", &X);
    }while(X<=0);

    return X;
}

int acq_quantita () {
    int X;

    do{
        printf("Fornisci quantita` prodotto\n");
        scanf("%d", &X);
    }while(X<=0 || X>=32000);

    return X;
}

void acq_prod (struct prodotto *P, int *n) {
    printf("Fornisci codice prodotto (14 caratteri)\n");
    acq_stringa(P[*n].COD);

    printf("Fornisci fornitore prodotto (11 caratteri)\n");
    acq_stringa(P[*n].F);

    P[*n].P=acq_prezzo();
    P[*n].Q=acq_quantita();

    (*n)++;
}

void view_code (char *code, int pos) {
    printf("Codice prodotto n %d: %s\n", pos, code);
}

void mod_P (float *P) {
    float new;
    
    do{
        printf("Fornisci nuovo valore\n");
        scanf("%f", &new);
    }while(new<=0 || new==*P);
    
    *P=new;
}

void mod_Q (int *Q) {
    int incr;
    
    do{
        printf("Fornisci incremento\n");
        scanf("%d", &incr);
    }while(incr<=0);
    
    *Q+=incr;
}

int contr_canc_case4 (struct prodotto *P, int *n, char *COD_rif) {
    int k=0;
    
    for(int i=0; i<*n; i++){
        if(strcmp(P[i].COD, COD_rif)==0){
            if(P[i].Q<10){
                for(int j=i; j<*n-1; j++){
                        P[j]=P[j+1];
                }
                (*n)--;
                k++;
            }
        }
    }
    
    return k;
}

void contr_media_case6 (struct prodotto *P, int *contm, float *somma, int n) {
    for(int i=0; i<n; i++){
        if(P[i].Q>150){
            (*contm)++;
            *somma+=P[i].P;
        }
    }
}

int build_prodF (struct prodotto *P, struct prodottof *PF, char *F_rif, int n) {
    int j=0;
    
    for(int i=0; i<n; i++){
        if(strcmp(P[i].F, F_rif)==0){
            strcpy(PF[j].COD, P[i].COD);
            PF[j].P=P[i].P;
            j++;
        }
    }
    
    return j;
}

void view_struct (struct prodottof *PF, int n) {
    printf("Vettore:\n");
    
    for(int i=0; i<n; i++){
        printf("Dati prodotto n %d:\ncodice: %s\nprezzo: %f", i+1, PF[i].COD, PF[i].P);
    }
}

int find_max (struct prodotto *P, float *max, int rif, int n) {
    int f=0;
    
    for(int i=0; i<n; i++){
        if(P[i].Q>rif){
            if(f==0){
                f=1;
                *max = P[i].P;
            }
            else if(*max<P[i].P){
                *max = P[i].P;
            }
        }
    }
    
    return f;
}


//programma int main()
int main(){
    struct prodotto P[500];
    int scelta, n=0;

    do{
        printf("Menu`\n");
        printf("Quale scelta?\n");
        scanf("%d", &scelta);

        switch(scelta){
            case 1:{
                if(n<500)
                    acq_prod(P, &n);
                else
                    printf("Full\n");
            }break;

            case 2:{
                int rif, k=0;

                printf("Riferimento:\n");
                rif=acq_quantita();

                for(int i=0; i<n; i++){
                    if(P[i].Q<rif){
                        view_code(P[i].COD, i+1);
                        k++;
                    }
                }

                if(k==0)
                    printf("Nessuna quantita` minore del riferimento\n");
            }break;

            case 3:{
                char COD_rif[15];
                int scelta1, scelta2;
                
                printf("Codice prodotto di riferimento:\n");
                acq_stringa(COD_rif);

                for(int i=0; i<n; i++){
                    if(strcmp(P[i].COD, COD_rif)==0){
                        do{
                            do{
                                printf("Scegli cosa modificare:\n1. prezzo\n2. quantita`\n");
                                scanf("%d", &scelta1);
                            }while(scelta1!=1 && scelta1!=2);
                            
                            if(scelta1==1)
                                mod_P(&P[i].P);
                            else
                                mod_Q(&P[i].Q);
                            
                            do{
                                printf("Vuoi modificare ancora il prodotto %s ?\n1. si\n2. no\n", P[i].COD);
                                scanf("%d", &scelta2);
                            }while(scelta2!=1 && scelta2!=2);
                        }while(scelta2==1);
                    }  //chiudo if(strcmp)
                }  //chiudo for
            }break;
            
            case 4:{
                char COD_rif[15];
                int k;  //k facoltativa: serve per visualizzare un messaggio finale di buona/cattiva riuscita della cancellazione
                
                printf("Codice prodotto di riferimento:\n");
                acq_stringa(COD_rif);
                
                k=contr_canc_case4(P, &n, COD_rif);
                
                if(k==0)
                    printf("Cancellazione avvenuta con successo!\n");
                else
                    printf("Cancellazione non avvenuta: condizioni non verificate\n");
            }break;
            
            case 5:{
                int contp=0;
                
                for(int i=0; i<n; i++){
                    if(P[i].P<30)
                        contp++;
                }
                
                printf("Percentuale = %d\n", contp*100/n); //N.B! non viene richiesta la visualizzazione
            }break;
            
            case 6:{
                int contm=0;
                float somma=0;
                
                contr_media_case6 (P, &contm, &somma, n);
                
                if(contm==0) //N.B! non viene richiesta la visualizzazione
                    printf("Media impossibile: nessun prodotto con quantita maggiore di 150\n");
                else
                    printf("Media = %f\n", somma/contm);
            }break;
            
            case 7:{
                struct prodottof PF[500];
                char F_rif[12];
                int n2;
                
                printf("Fornitore di riferimento:\n");
                acq_stringa(F_rif);
                
                n2=build_prodF(P, PF, F_rif, n);
                
                if(n2==0)
                    printf("Vettore vuoto: nessun prodotto con fornitore %s\n", F_rif);
                else
                    view_struct(PF, n2);
            }break;
            
            case 8:{
                int rif, flag;
                float max;
                
                printf("Riferimento\n");
                rif=acq_quantita();
                
                flag=find_max(P, &max, rif, n);
                
                if(flag==0)
                    printf("Nessun massimo: nessun prodotto con quantita maggiore di %d\n", rif);
                else{
                    printf("Codici prodotti con prezzo max:\n");
                    for(int i=0; i<n; i++){
                        printf("prodotto n %d: %s\n", i+1, P[i].COD);
                    }
                }
            }break;
            
            case 9:{
                printf("Fine programma\n");
            }break;
            
            default:{
                printf("Scelta non ammessa\n");
            }
        }
    }while(scelta!=9);
    return 0;
}