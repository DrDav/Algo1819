/*
 * Header file contenente la dichiarazione di una lista di interi
 * linkata singolarmente, con operazioni di inserimento, cancellazione
 * e altre utility.
 *
 * Per utilizzarla nei nei vostri programmi includete questo file
 * con #include "linked_list.h" e compilate il vostro file con:
 * gcc -Wall -pedantic linked_list.c vostro_esercizio.c -o vostro_esercizio.
 *
 */

#ifndef linked_list_h
#define linked_list_h

/*
 * Elemento di lista (di interi).
 * val è il valore contenuto nell'elemento (intero).
 * next è il puntatore all'elemento successivo.
 */
typedef struct _list_element {
    int key;
    struct _list_element* next;
} list_elem_t;

/*
 * Tipo delle liste (di interi)
 * head è un puntatore alla testa della lista.
 * tail è un puntatore alla coda della lista.
 * size è la dimensione della lista.
 *
 * tail è presente in modo da poter fare inserimenti in coda in tempo costante.
 */
typedef struct {
    list_elem_t* head;
    list_elem_t* tail;
    int size;
} list_t;

/*
 * Funzione di utilità che crea una nuova lista
 * Head e tail inizialmente sono impostati a NULL in quanto la lista è vuota.
 */
list_t* new_list();

/*
 * Dealloca la memoria occupata dalla lista passata come parametro
 */
void destroy_list(list_t* list);

/*
 * Inserisce l'intero passato come secondo parametro
 * in testa alla lista passata come primo.
 *
 * Tempo: Θ(1)
 */
void head_insert(list_t* list, int elem);

/*
 * Inserisce l'intero passato come secondo parametro
 * in coda alla lista passata come primo.
 *
 * Tempo: Θ(1)
 */
void tail_insert(list_t* list, int elem);

/*
 * Rimuove la testa della lista passata come parametro.
 *
 * Tempo: Θ(1)
 */
void head_remove(list_t* list);

/*
 * Rimuove la coda della lista passata come parametro.
 *
 * Tempo: Θ(1)
 */
void tail_remove(list_t* list);

/*
 * Rimuove il primo elemento con chiave uguale al secondo parametro
 * dalla lista passata come primo.
 *
 * Tempo: Θ(p) = O(n) dove p è la posizione di k nella lista.
 */
void key_remove(list_t* list, int k);

/*
 * Restituisce 1 se l'elemento k è presente nella lista list,
 * 0 altrimenti.
 *
 * Tempo: Θ(p) = O(n) dove p è la posizione di k nella lista.
 */
int contains(list_t* list, int k);

/*
 * Funzione di utilità per stampare una lista.
 */
void print_list(list_t* list);

#endif /* linked_list_h */
