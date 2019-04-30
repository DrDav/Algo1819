/*
 * Header File contenente la dichiarazione di una tabella hash
 * con liste di trabocco. La tabella contiene coppie (chiave, valore)
 * entrambi di tipo intero. L'operazione di hash viene eseguita solo sulla chiave,
 * mentre "valore" è un dato satellite che a seconda dell'applicazione
 * può essere uguale o diverso dalla chiave.
 *
 * Questa implementazione può essere riutilizzata in altri esercizi.
 * Per farlo bisogna includere questo file con una #include nel file dell'esercizio.
 * Successivamente compilare con:
 * gcc -Wall -pedantic esercizio.c chained_hash.c -o esercizio
 * (Quindi il .c nel gcc e il .h nel vostro file)
 *
 */


#ifndef chained_hash_h
#define chained_hash_h

#include <math.h> /* Necessaria solo per l'ultima funzione hash */

/* Elemento contenuto nella tabella hash (elemento di lista)
 * Contiene chiave e valore.
 * Spesso chiave e valore coincidono, ma per essere più generali
 * le manteniamo separate
 */
typedef struct _list_elem {
    int key;
    int val;
    struct _list_elem* next;
} list_elem_t;

/* Tipo delle tabelle hash con liste di trabocco */
typedef struct {
    list_elem_t** table; /* Tabella Hash (array di liste) */
    int m; /* Dimensione della tabella */
} chained_hash_t;

/* Creazione di una nuova tabella hash di m posizioni */
chained_hash_t* new_hash_table(int m);

/* Deallocazione di una tabella hash di m posizioni */
void hash_destroy(chained_hash_t* T);

/* Inserimento di elem (con chiave k) nella tabella hash T */
void chained_hash_insert(chained_hash_t* T, int k, int elem);

/* Ricerca della chiave k nella tabella hash T.
 * Tramite *result si ottiene il valore associato alla chiave
 * Restituisce 0 se la chiave non è presente, 1 altrimenti.
 */
int chained_hash_search(chained_hash_t* T, int k, int* result);

/* Cancellazione dell'elemento di chiave k nella tabella hash T */
void chained_hash_delete(chained_hash_t* T, int k);

/*
 * Funzione hash di base: (key modulo m)
 * m conviene sceglierlo come numero primo e distante da una potenza di 2.
 * Es = 19, 37, 41...
 *
 *
 *
 * Static = evita che la funzione venga esportata nella tabella dei simboli
 * (in parole povere limite l'utilizzo di questa funzione a questa libreria,
 * ed è utile quando più file hanno all'interno una dichiarazione di funzione
 * con lo stesso nome)
 *
 * Inline = ottimizzazione del compilatore per cui eviterà l'overhead
 * di chiamata di funzione ogni volta, in pratica rende questa funzione molto
 * simile ad una macro.
 *
 */
static inline int hash_div(int key, int m) {
    return (key % m);
}

/*
 * Funzione hash più avanzata/complicata:
 * Posto m = 2^t, questa funzione hash suddivide in blocchi di t bit
 * la chiave, e poi ne calcola lo XOR (eXclusive OR) bit a bit.
 * NB: è importante che m sia una potenza di 2.
 *
 * Ad esempio: m = 8 = 2^3 (t = 3), key = 310 = 100110110 in binario
 * Dividiamo in blocchi di tre i bit di key (aggiungendo 0 a sinistra se necessario)
 * key = 100 | 110 | 110 e poi si calcola lo xor dei bit corrispondenti:
 * primo bit a sinistra = 1 xor 1 xor 1 = 1
 * secondo bit = 0 xor 1 xor 1 = 0
 * terzo bit = 0 xor 0 xor 0 = 0
 * Risultato = 100 (base 2) => 4 (base 10) Quindi l'hash di 310 è 4.
 * (Ricordiamo che 1 xor 0 = 0 xor 1 = 1, mentre 0 xor 0 = 1 xor 1 = 0)
 *
 * Questa funzione è "facoltativa", nel senso che non è assolutamente
 * necessaria per l'esame e vuole essere solamente un esempio di funzione hash
 * più complessa e diversa da quella precedente.
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


#endif /* hash_liste_h */
