#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

/*
 * Funzione di utilità che crea una nuova lista
 * Head e tail inizialmente sono impostati a NULL in quanto la lista è vuota.
 */
list_t* new_list() {
    list_t* list = malloc(sizeof(list_t));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    
    return list;
}

/*
 * Dealloca la memoria occupata dalla lista passata come parametro
 */
void destroy_list(list_t* list) {
    while(list->head != NULL) {
        list_elem_t* tmp = list->head; // Salva l'elemento corrente
        list->head = list->head->next; // Avanza nella lista
        free(tmp); // Dealloca l'elemento
    }
    
    free(list); // Free della struct che conteneva la lista
}

/*
 * Inserisce l'intero passato come secondo parametro
 * in testa alla lista passata come primo.
 *
 * Tempo: Θ(1)
 */
void head_insert(list_t* list, int elem) {
    list_elem_t* new = malloc(sizeof(list_elem_t));
    new->key = elem;
    new->next = list->head; // La nuova testa ha come successore la vecchia
    list->head = new; // La nuova testa adesso è il nuovo elemento
    /* Se lista era vuota, aggiorniamo anche il puntatore alla coda */
    if(list->size == 0)
        list->tail = new;
    
    (list->size)++; // Aumentiamo la dimensione la lista
}

/*
 * Inserisce l'intero passato come secondo parametro
 * in coda alla lista passata come primo.
 *
 * Tempo: Θ(1)
 */
void tail_insert(list_t* list, int elem) {
    list_elem_t* new = malloc(sizeof(list_elem_t));
    new->key = elem;
    new->next = NULL; // Poiché inseriamo in coda, new non ha successori
    list->tail->next = new; // Appendiamo new in fondo alla lista
    list->tail = new; // Aggiorniamo la coda
    /* Se la lista era vuota, aggiorniamo anche il puntatore alla testa */
    if(list->size == 0)
        list->head = new;
    
    (list->size)++; // Aumentiamo la dimensione della lista
}

/*
 * Rimuove la testa della lista passata come parametro.
 *
 * Tempo: Θ(1)
 */
void head_remove(list_t* list) {
    if(list->size == 1) {
        /* Se la lista contiene un solo elemento basta deallocarlo
         * e resettare i puntatori a testa e coda.
         */
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        (list->size)--;
    }
    else if(list->size > 1) {
        list_elem_t* tmp = list->head; // Salviamo la testa
        list->head = list->head->next; // Cambiamo la testa col successore
        free(tmp); // Deallochiamo la vecchia testa
        (list->size)--;
    }
    /* Altrimenti la dimensione è zero e non dobbiamo fare niente. */
}

/*
 * Rimuove la coda della lista passata come parametro.
 *
 * Tempo: Θ(1)
 */
void tail_remove(list_t* list) {
    if(list->size == 1) {
        /* Se la lista contiene un solo elemento basta deallocarlo
         * e resettare i puntatori a testa e coda.
         */
        free(list->tail);
        list->head = NULL;
        list->tail = NULL;
        
        (list->size)--;
    }
    else if(list->size > 1) {
        /* Poiché la lista non è doppiamente linkata,
         * per cancellare correttamente la coda bisogna partire dalla testa.
         */
        list_elem_t* curr = list->head;
        list_elem_t* prev = NULL;
        while(curr->next != NULL) {
            prev = curr;
            curr = curr->next;
        }
        /* Adesso prev punta al penultimo elemento, dobbiamo cancellare curr */
        prev->next = NULL;
        list->tail = prev; // La nuova coda è il penultimo elemento
        free(curr); // Dealloca l'ultimo elemento
    
        (list->size)--;
    }
    /* Altrimenti la dimensione è zero e non dobbiamo fare niente. */
}

/*
 * Rimuove il primo elemento con chiave uguale al secondo parametro
 * dalla lista passata come primo.
 *
 * Tempo: Θ(p) = O(n) dove p è la posizione di k nella lista.
 */
void key_remove(list_t* list, int k) {
    list_elem_t* prev = NULL;
    list_elem_t* curr = list->head;
    
    while(curr != NULL && curr->key != k) {
        prev = curr;
        curr = curr->next;
    }
    
    if(prev == NULL) {
        /* L'elemento da cancellare è in testa */
        head_remove(list);
    }
    else if(curr != NULL && curr->next == NULL) {
        /* L'elemento da cancellare è in coda */
        tail_remove(list);
    }
    else if(curr != NULL) {
        /* L'elemento da cancellare è in mezzo alla lista */
        prev->next = curr->next;
        free(curr);
        (list->size)--;
    }
    /* Altrimenti k non era presente nella lista */
}

/*
 * Restituisce 1 se l'elemento k è presente nella lista list,
 * 0 altrimenti.
 *
 * Tempo: O(n)
 */
int contains(list_t* list, int k) {
    list_elem_t* curr = list->head;
    while(curr != NULL && curr->key != k) {
        curr = curr->next;
    }
    
    if(curr != NULL) // Se curr != NULL allora abbiamo trovato k
        return 1;
    
    return 0; // Altrimenti k non era presente
}

/*
 * Funzione di utilità per stampare una lista.
 */
void print_list(list_t* list) {
    list_elem_t* curr = list->head;
    
    printf("Contenuto della lista:\n");
    while(curr != NULL) {
        printf("%i ", curr->key);
        curr = curr->next;
    }
    printf("\n");
}
