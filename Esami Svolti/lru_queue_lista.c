/*
 * Esame del 09/09/2016
 *
 * (Versione con LISTA MONODIREZIONALE)
 *
 * Testo dell'esame completo:
 * http://dijkstra.di.unipi.it/#/task/LezEsami_2015-2016Esame20160909c1/statement
 */

#include <stdio.h>
#include <stdlib.h>

/* Questo percorso è relativo alle cartelle di GitHub.
 * Da cambiare con il percorso al vostro file linked_list.h
 */
#include "../Algoritmi Base/Liste/linked_list.h"

/*
 * Inserimento di element nella coda (rappresentata come lista) queue.
 * Se l'elemento è già presente questo viene rimosso e poi reinserito.
 * Se la coda è piena viene rimossa la coda.
 */
void queue_insert(list_t* queue, int element, int max_size) {
    if(contains(queue, element)) {
        /* Se l'elemento era già presente, va rimosso */
        key_remove(queue, element);
    }
    else if(queue->size == max_size){
        /* Se la coda è piena e non contiene già l'elemento,
         * si rimuove l'elemento più vecchio (quindi si rimuove in coda)
         */
        tail_remove(queue);
    }
    
    /* Inserimento di element */
    head_insert(queue, element);
}

/*
 * Stampa della coda (cioè della lista), formattata come richiesto dal testo. */
void print_queue(list_t* queue) {
    list_elem_t* curr = queue->head;
    while(curr != NULL) {
        printf("%i ", curr->key);
        curr = curr->next;
    }
    printf("$\n");
}

int main(void) {
    int n;
    
    scanf("%i", &n);
    
    list_t* queue = new_list(n);
    int op, element;
    
    do {
        /* Lettura dell'operazione */
        scanf("%i",&op);
        switch(op) {
            case 1:
                /* Lettura dell'elemento da inserire */
                scanf("%i", &element);
                queue_insert(queue, element, n);
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
    destroy_list(queue);
}
