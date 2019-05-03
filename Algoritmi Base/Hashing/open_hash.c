#include <stdio.h> 
#include <stdlib.h>

#include "open_hash.h"


/* Cambiare questa define per scegliere la funzione hash da utilizzare
 * (vedere il file chained_hash.h per vedere le funzioni hash disponibili)
 */

#define hash(k, i, m) double_hash(k, i, m)

/* Alloca una nuova tabella hash di m posizioni e ne restituisce il puntatore. */
open_hash_t* new_hash_table(int m) {
    /* Allocazione della struct contenente la tabella */
    open_hash_t* T = malloc(sizeof(open_hash_t));
    
    /* Allocazione della tabella (array di coppie) */
    T->table = malloc(m * sizeof(hash_elem_t));
    T->m = m;
    
    int i;
    for(i=0;i<m;i++) {
        /* Inizializzazione a NULL di tutta la tabella.
         * È utile per le fasi di inserimento e ricerca
         * (che controllano se una cella è NULL).
         */
        T->table[i] = NULL;
    }
    
    return T;
}

/* Deallocazione di una tabella hash di m posizioni. */
void hash_destroy(open_hash_t* T) {
    int i;
    int m = T->m;
    
    for(i=0;i<m;i++) {
        /* Deallocazione delle coppie contenute nella tabella */
        if(T->table[i] != NULL)
            free(T->table[i]);
    }
    
    /* Deallocazione della tabella */
    free(T->table);
    
    /* Deallocazione della struct che contiene la tabella */
    free(T);
}

/* Inserimento di elem (con chiave k) nella tabella hash T.
 * NON non controlla se la chiave è già presente nella tabella.
 * Tempo: O(1/(1-alpha)) = O(1)
 */
void open_hash_insert(open_hash_t* T, int k, int elem) {
    int i = 0;
    do {
        int pos = hash(k, i, T->m);
        printf("[Chiave %i] Provo la posizione: %i\n", k, pos);
        /* Se troviamo un posto libero o un posto dove c'è stata una cancellazione
         * possiamo inserirci l'elemento.
         */
        if(T->table[pos] == NULL) {
            /* Posto libero */
            hash_elem_t* new = malloc(sizeof(hash_elem_t));
            new->key = k;
            new->val = elem;
            T->table[pos] = new;
            return;
        }
        else if(IS_DELETED(T->table[pos])) {
            free(T->table[pos]); // Rimuove il valore "deleted"
            /* Inserisce il nuovo elemento */
            hash_elem_t* new = malloc(sizeof(hash_elem_t));
            new->key = k;
            new->val = elem;
            T->table[pos] = new;
            return;
        }
        else {
            i++; // Altrimenti procediamo nella sequenza di scansione
        }
    }while(i != T->m);
    
    /* Se arriviamo qua fuori vuol dire che la tabella hash è piena.
     * In questa implementazione non facciamo niente,
     * ma sarebbe opportuno gestire questo caso emettendo un errore
     * oppure effettuando un rehashing dell'intera tabella.
     */
}

/* Ricerca della chiave k nella tabella hash T.
 * Tramite *result si ottiene il valore associato alla chiave (NULL se assente)
 * Restituisce 0 se la chiave non è presente, 1 altrimenti.
 *
 * Tempo O(1/(1-alpha)) = O(1)
 */
int open_hash_search(open_hash_t* T, int k, int* result) {
    int i = 0;
    int pos;
    do {
        pos = hash(k, i, T->m);
        if(T->table[pos] != NULL && T->table[pos]->key == k) {
            /* È necessario controllare prima che la posizione non sia vuota,
             * altrimenti rischiamo un segmentation fault accedendo a key.
             * Se la chiava è uguale, abbiamo trovato l'elemento.
             */
            *result = T->table[pos]->val;
            return 1;
        }
        else {
            i++; // Altrimenti procediamo con la sequenza di scansione
        }
    }while(T->table[pos] != NULL && i != T->m);
    /* Arrivati qui fuori possiamo rispondere che la chiave non è presente. */
    return 0;
}

/* Cancellazione (la prima occorrenza)dell'elemento di chiave k nella tabella hash T.
 * Tempo: O(1/(1-alpha)) = O(1)
 */
void open_hash_delete(open_hash_t* T, int k) {
    int i = 0;
    do {
        int pos = hash(k, i, T->m);
        /* È necessario controllare la chiave, perché in caso di collisioni
         * non è sicuro che la prima posizione trovata sia quella da cancellare
         */
        if(T->table[pos] != NULL && T->table[pos]->key == k) {
            free(T->table[pos]); // Libera la memoria precedentemente occupata
            /* Creazione e inserimento del valore DELETED */
            hash_elem_t* deleted = malloc(sizeof(hash_elem_t));
            deleted->key = INT_MIN;
            deleted->val = INT_MIN;
            T->table[pos] = deleted;
            return;
        }
        else {
            i++; // Altrimenti procediamo nella sequenza di scansione
        }
    }
    while(i != T->m);
    
    /* Arrivati fuori dal while la chiave non era presente in tabella,
     * quindi non c'è bisogno di fare niente.
     */
}

