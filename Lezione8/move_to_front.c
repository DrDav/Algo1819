#include <stdio.h>
#include <stdlib.h>

/*
 * Per comprendere maggiormente il funzionamento delle liste,
 * si consiglia di leggere il file "lista_monodirezionale.c".
 */

typedef struct _list_elem {
    int val;
    struct _list_elem* next;
} list_elem_t;

/*
 * Move To Front: Presa una lista e un elemento,
 * sposta l'elemento in testa alla lista e restituisce la sua vecchia posizione.
 *
 * La lista deve essere passata con & dal main, perché la testa viene modificata
 * da questa funzione.
 */
int move_to_front(list_elem_t** head, int elem) {
    int posizione = 0;
    
    list_elem_t* curr = *head;
    list_elem_t* prev = NULL;
    
    while(curr != NULL && curr->val != elem) {
        posizione++;
        /* È necessario salvarsi il puntatore all'elemento precedente,
         * per poter aggiustare i collegamenti qualora l'elemento si trovi
         * in mezzo alla lista
         */
        prev = curr;
        curr = curr->next;
    }
    
    if(curr == NULL) {
        /* La lista è vuota oppure l'elemento non era nella lista */
        return -1;
    }
    else {
        if(prev == NULL) {
            /* L'elemento è stato trovato ed è già in testa,
             * quindi non è necessario fare niente.
             */
            return posizione;
        }
        
        /* L'elemento è stato trovato in mezzo alla lista
         * e la sua posizione è stata salvata.
         * Bisogna quindi spostare l'elemento in testa alla lista.
         */
        
        /* Collega il predecessore al successore, "scavalcando" quindi curr. */
        prev->next = curr->next;
        /* Adesso curr è "fuori" dalla lista. Poiché curr deve essere la nuova
         * testa, il suo successore sarà la vecchia testa.
         */
        curr->next = *head;
        /* Infine assegniamo a head il puntatore a curr, cioè la nuova testa. */
        *head = curr;
        
        return posizione; // Vecchia posizione di curr
    }
}

/* Inserimento in coda alla lista puntata da head.
 * Poiché, se la lista è vuota, la testa verrà modificata, è necessario
 * usare il doppio puntatore ed utilizzare la & nel main.
 */
void tail_insert(list_elem_t** head, int elem) {
    /* Creazione del nuovo elemento da aggiungere alla lista */
    list_elem_t* new = malloc(sizeof(list_elem_t));
    new->val = elem;
    new->next = NULL; // Perché sarà sempre l'ultimo elemento della lista
    
    if(*head == NULL) {
        /* Se la lista è vuota bisogna inserire in testa, modificando quindi
         * il puntatore alla testa, contenuto in *head.
         */
        *head = new;
    }
    else {
        list_elem_t* current = *head;
        /* Usiamo current per scorrere la lista, che è un puntatore ausiliario.
         * Altrimenti se avessimo usato *head avremmo "perso" la testa
         * della lista (e quindi tutta la lista) in maniera irrecuperabile.
         */
        while(current->next != NULL) {
            current = current->next;
        }
        /* Aggiunta del nuovo elemento in fondo */
        current->next = new;
    }
}

int main(void) {
    int i;
    int n;
    
    scanf("%i", &n);
    
    list_elem_t* list = NULL; // Inizialmente la lista è vuota
    
    for(i=0;i<n;i++) {
        int val;
        
        scanf("%i", &val);
        /* Inserisce il nuovo elemento in coda alla lista */
        tail_insert(&list, val);
    }
    
    int output = 0;
    
    while(output != -1) {
        int search;
        
        scanf("%i", &search);
        
        output = move_to_front(&list, search);
        
        printf("%i\n", output);
    }
    
    /* Deallocazione della lista */
    while(list != NULL) {
        list_elem_t* tmp = list;
        list = list->next;
        free(tmp);
    }
    
    return 0;
}
