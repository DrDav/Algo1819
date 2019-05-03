/*
 * Header File contenente la dichiarazione di una tabella hash
 * (di interi) ad indirizzamento aperto.
 * La tabella contiene coppie (chiave, valore),
 * entrambi di tipo intero.
 * L'operazione di hash viene eseguita solo sulla chiave,
 * mentre "valore" è un dato satellite che a seconda dell'applicazione
 * può essere uguale o diverso dalla chiave.
 *
 * Questa implementazione può essere riutilizzata in altri esercizi.
 * Per farlo bisogna includere questo file con una #include nel file dell'esercizio.
 * Successivamente compilare con:
 * gcc -Wall -pedantic esercizio.c open_hash.c -o esercizio
 * (Quindi il .c nel gcc e il .h nel vostro file)
 *
 */

#ifndef open_hash_h
#define open_hash_h

#include <limits.h>
#include <math.h>

#define IS_DELETED(e) ((e->key == INT_MIN && e->val == INT_MIN) ? 1 : 0)
#define hash_aux(k, m) hash_div(k, m)
#define hash_aux2(k, m) ((1 + k) % (m-1))
#define C1 (0.5)
#define C2 (0.5)

/* Tipo degli elementi contenuti nella tabella hash (coppia <chiave, valore>) */
typedef struct {
    int key; /* Chiave */
    int val; /* Valore associato */
} hash_elem_t;

/* Tipo delle tabelle hash ad indirizzamento aperto */
typedef struct {
    hash_elem_t** table; /* Tabella Hash (array di hash_elem_t) */
    int m; /* Dimensione della tabella */
} open_hash_t;

/* Creazione di una nuova tabella hash di m posizioni */
open_hash_t* new_hash_table(int m);

/* Deallocazione di una tabella hash di m posizioni */
void hash_destroy(open_hash_t* T);

/* Inserimento di elem (con chiave k) nella tabella hash T */
void open_hash_insert(open_hash_t* T, int k, int elem);

/* Ricerca della chiave k nella tabella hash T.
 * Tramite *result si ottiene il valore associato alla chiave.
 * Restituisce 0 se la chiave non è presente, 1 altrimenti.
 */
int open_hash_search(open_hash_t* T, int k, int* result);

/* Cancellazione dell'elemento di chiave k nella tabella hash T */
void open_hash_delete(open_hash_t* T, int k);

/* Funzioni Hash Ausiliarie */

/* Metodo della divisione.
 * Parametri suggeriti: m = numero primo
 */
static inline int hash_div(int key, int m) {
    return (key % m);
}

/*
 * Per chiarimenti riguardo questa seconda funzione hash leggere il file
 * chained_hash.h
 * Parametri consigliati: m = potenza esatta di 2
 */
static inline int hash_xor(int key, int m) {
    /* t è l'esponente di m. Ricordarsi che m deve essere una potenza esatta di 2. */
    int t = (int) log2((double) m);
    
    int h = 0; // L'hash che restituiremo
    while(key > 0) {
        /* Accumuliamo dentro h i valori ottenuti dallo XOR bit a bit.
         * Quello che facciamo è lo XOR bit a bit dell'attuale h con l'attuale
         * gruppo di t bit (3 nel caso di esempio precedente)
         * Tramite l'operazione di modulo m prendiamo i t bit meno significativi
         * della chiave. Questo perché m è una potenza di 2, e gli interi sono
         * codificati in binario.
         */
        h = h ^ (key % (m)); // m = 2^t
        /* "Spostiamo verso destra" di t posizioni i bit della chiave,
         * così che alla prossima iterazione l'operazione di modulo
         * consideri il successivo gruppo di t bit della chiave.
         */
        key = key >> t;
    }
    
    return h;
}

/* Funzioni Hash per l'indirizzamento aperto */

/* Scansione lineare: h(k, i) = (h'(k) + i) mod m */
static inline int linear_scan(int k, int i, int m) {
    return (hash_aux(k, m) + i) % m;
}

/* Scansione quadratica: h(k, i) = (h'(k) + c1*i + c1*i^2) mod m
 * Parametri consigliati: c1 = 1/2, c2 = 1/2, m = potenza di 2
 */
static inline int quadratic_scan(int k, int i, int m) {
    return (int) (hash_aux(k, m) + i*C1 + C2*i*i) % m;
}

/* Doppio hashing: h(k, i) = (h'(k) + i*h''(k)) mod m
 * Parametri consigliati:
 * • m potenza di 2, hash_aux2 che restituisce sempre numeri dispari
 * • m numero primo, hash_aux2 che restituisce sempre numeri < m
 */
static inline int double_hash(int k, int i, int m) {
    return (hash_aux(k, m) + i*hash_aux2(k, m)) % m;
}
#endif /* open_hash_h */
