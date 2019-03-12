#include <stdio.h>
#include <stdlib.h>

/* Intestazione della funzione: tipo del risultato e
lista delle dichiarazioni dei parametri */
int* FindVal(int a[], int len, int val){
    int i=0;

    /* Variabile locale: inizialmente è a 0, diventa 1 se trovo l'elemento val */
    int trovato=0;

    /* Scorro l'array finché non sono arrivato alla fine e non ho trovato l'elemento */
    while(i<len && !trovato){
        if(a[i]==val)
            /* Elemento trovato: imposto la variabile trovato a 1,
            in modo da non eseguire la prossima iterazione del while */
            trovato=1;
        else
            /* Elemento non trovato: esamino la posizione successiva */
            i++;
    }

    /* Controllo se sono uscito dal while perché ho trovato l'elemento o perché ho scorso tutto l'array */
    if(trovato)
        /* Elemento trovato: restituisco un puntatore alla cella che lo contiene.
            &a[i] -> referenziazione: denota l'indirizzo di memoria di a[i] */
        return &a[i];
    else
        return NULL;
}

int main(void){
    /* Allocazione dinamica della memoria.
        sizeof(type) --> restituisce la lunghezza in byte del tipo type
        La funzione malloc restituisce un puntatore al primo byte del blocco allocato (&a[0]).
        Con un assegnamento il tipo del puntatore viene convertito implicitamente.
     */
    int* a = malloc(10*sizeof(int));
    int i = 0;
    int val;
    
    for(i=0; i<10; i++){
        scanf("%d", &a[i]);
    }
    scanf("%d", &val);

    /* Chiamata della funzione FindVal */
    int* posVal = FindVal(a, 10, val);

    if(posVal!=NULL)
        printf("trovato\n");
    else
        printf("non trovato\n");

    return 0;
}