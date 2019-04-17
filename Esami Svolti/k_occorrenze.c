#include <stdio.h>
#include <stdlib.h>

/* Cambiare la seguente include con la posizione del vostro file chained_hash.h */
#include "../Algoritmi Base/Hashing/chained_hash.h" // Segue la struttura GitHub

int main(void) {
    int i;
    int n;
    int k;
    
    scanf("%i", &n);
    scanf("%i", &k);
    
    int* a = malloc(n * sizeof(int));
    for(i=0;i<n;i++) {
        scanf("%i", &a[i]);
    }
    
    /* Creazione di una tabella hash lunga 2n posizioni
     * (Questo favorisce un fattore di carico alpha ~ 1/2)
     */
    chained_hash_t* T = new_hash_table(2*n);
    
    for(i=0;i<n;i++) {
        int frequenza;
        
        if(chained_hash_search(T, a[i], &frequenza) != 0) {
            /* Se a[i] è già nella tabella ha una sua frequenza.
             * Rimuoviamo la chiave a[i]
             * e la reinseriamo con frequenza aumentata.
             */
            chained_hash_delete(T, a[i]);
            chained_hash_insert(T, a[i], frequenza + 1);
        }
        else {
            /* Se a[i] non era già stata incontrata
             * la inseriamo con frequenza 1.
             */
            chained_hash_insert(T, a[i], 1);
        }
    }
    
    /* L'output sarà in ordine di apparizione in a
     * Perché effettuiamo le ricerche a partire da una scansione di a
     */
    for(i=0;i<n;i++) {
        int frequenza;
        
        if(chained_hash_search(T, a[i], &frequenza) != 0) {
            /* Cerca a[i] nella tabella e ottiene la sua frequenza */
            if(frequenza >= k) // Stampa la soluzione
                printf("%i ", a[i]);
        }
    }
    
    /* Deallocazione della memoria */
    hash_destroy(T);
    
    free(a);
}
