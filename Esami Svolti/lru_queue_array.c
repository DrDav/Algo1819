/*
 * Esame del 09/09/2016
 *
 * (Versione con ARRAY)
 *
 * Testo dell'esame completo:
 * http://dijkstra.di.unipi.it/#/task/LezEsami_2015-2016Esame20160909c1/statement
 */

#include <stdio.h>
#include <stdlib.h>

#define min(a, b) ((a < b) ? a : b)

/*
 * Coda di interi.
 */
typedef struct {
    int* queue; /* La coda */
    int capacity; /* Capacità massima della coda */
    int size; /* Numero di elementi attualmente presenti in coda */
} queue_t;

/* Crea e restituisce una nuova coda vuota, con capacità c. */
queue_t* new_queue(int c) {
    queue_t* q = malloc(sizeof(queue_t));
    
    q->queue = malloc(c * sizeof(int));
    q->capacity = c;
    q->size = 0;
    
    return q;
}

/* Inserimento di un elemento in testa.
 * Se l'elemento era già presente, la sua vecchia istanza viene cancellata
 * spostando tutti gli elementi verso destra, sovrascrivendola.
 * Tempo: O(n)
 */
void queue_insert(queue_t* q, int k) {
    int tmp1 = q->queue[0]; // Vecchio elemento in testa
    int tmp2;
    int i;
    int inserito = 1;
    /* Se il primo elemento della coda è già quello che vogliamo inserire
     * possiamo terminare subito senza fare niente.
     */
    if(q->size > 0 && q->queue[0] == k)
        return;
    
    /* Altrimenti inseriamo k in testa (posizione 0) */
    q->queue[0] = k;
    /* E spostiamo verso destra tutti gli altri elementi.
     * In questo modo rimuoviamo automaticamente la coda.
     */
    for(i=1;i<min(q->size+1,q->capacity);i++) {
        /* Tramite tmp1 e tmp2 effettuiamo degli scambi progressivi
         * fino alla fine della coda.
         */
        tmp2 = q->queue[i];
        q->queue[i] = tmp1;
        if(tmp2 == k) {
            /* Se abbiamo trovato k in coda vuol dire che gli elementi
             * successivi (cioè più vecchi) non devono essere espulsi
             * dal momento che stiamo solo "spostando" k in cima
             * e non inserendo un elemento nuovo. Quindi usciamo dal ciclo.
             */
            inserito = 0;
            break;
        }
        tmp1 = tmp2;
    }
    /* Se abbiamo inserito un numero mai inserito finora
     * e se la coda non conteneva già il numero massimo di elementi,
     * aumentiamo il contatore del numero di elementi in coda.
     * (Si noti che questo contatore non diminuisce mai in questo esercizio).
     */
    if(inserito && q->size < q->capacity)
        q->size++;
}

/* Stampa degli elementi in coda, terminata dal carattere $. */
void print_queue(queue_t* q) {
    int i;
    for(i=0;i<q->size;i++) {
        printf("%i ",q->queue[i]);
    }
    printf("$\n");
}

int main(void) {
    int n;
    
    scanf("%i", &n);
    
    queue_t* queue = new_queue(n);
    int op, element;
    
    do {
        /* Lettura dell'operazione */
        scanf("%i",&op);
        switch(op) {
            case 1:
                /* Lettura dell'elemento da inserire */
                scanf("%i", &element);
                queue_insert(queue, element);
                break;
            case 2:
                print_queue(queue);
                break;
            default:
                /* Non è necessario fare niente in questo caso */
                break;
        }
    }
    while(op != 0);
    
    /* Deallocazione della lista */
    free(queue->queue);
    free(queue);
}
