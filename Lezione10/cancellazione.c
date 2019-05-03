#include <stdio.h>
#include <stdlib.h>

/* Elemento di lista:
 * Contiene l'informazione e un puntatore all'elemento successivo della lista
 */
typedef struct _elemento_di_lista {
    int val; // Informazione
    struct _elemento_di_lista* next; // Puntatore al prossimo elemento
} list_elem_t;

/* Reminder:
 * list_elem_t è il tipo di un elemento della lista;
 * list_elem_t* è un puntatore ad un elemento di lista, e quindi è una lista;
 * list_elem_t** è l'indirizzo del puntatore alla testa della lista (!)
 *               e va usato nelle funzioni che potrebbero modificarne la testa.
 */


/* Restituisce la media di una lista di interi lunga n */
int mean(list_elem_t* list, int n) {
    int sum = 0;
    list_elem_t* curr = list;
    while(curr != NULL) {
        sum = sum + curr->val;
        curr = curr->next;
    }
    
    return sum / n; // L'arrotondamento per difetto viene fatto automaticamente
}

/* Cancella dalla lista tutti gli elementi minori o uguali al secondo parametro.
 * La lista viene passata con un doppio puntatore, in quanto potremmo
 * dover cancellare in testa.
 * Tempo: Θ(n)
 */
void cancellazione(list_elem_t** list, int mean) {
    list_elem_t* prev = NULL;
    list_elem_t* curr = *list;
    
    while(curr != NULL) {
        if(curr->val <= mean) { // curr va cancellato?
            if(prev == NULL) { // Stiamo cancellando in testa
                *list = (*list)->next; // Modifichiamo la testa della lista
                free(curr); // Deallochiamo la memoria dell'elem. rimosso
                curr = *list; // Cambia il puntatore di curr con la nuova testa
                /* Non dobbiamo avanzare nella lista, in quanto adesso
                 * dobbiamo esaminare la nuova testa della lista
                 */
            }
            else { // Stiamo cancellando "in mezzo" alla lista
                list_elem_t* tmp = curr; // Salviamo l'elemento corrente
                curr = curr->next; // Avanziamo nella lista
                prev->next = curr; // Rimuoviamo l'elemento dalla lista ("saltandolo")
                free(tmp); // Deallochiamo l'elemento rimosso
            }
        }
        else {
        /* Se non dobbiamo cancellare proseguiamo col prossimo elemento */
            prev = curr;
            curr = curr->next;
        }
    }
}

/*
 * Procedura che inserisce in coda l'elemento passato come secondo parametro.
 * Si noti che la lista è un doppio puntatore e non puntatore singolo.
 * Questo perché quando la lista è vuota dobbiamo modificarne la testa,
 * e questo è possibile solamente avendo in mano il "vero" puntatore alla lista
 * (nel main bisogna quindi passare la lista usando la &)
 */
void inserisci_in_coda(list_elem_t** list, int elem) {
    /* Creazione del nuovo elemento da aggiungere alla lista */
    list_elem_t* new = malloc(sizeof(list_elem_t));
    new->val = elem;
    new->next = NULL; // Perché sarà sempre l'ultimo elemento della lista
    
    if(*list == NULL) {
        /* Se la lista è vuota bisogna inserire in testa, modificando quindi
         * il puntatore alla testa, contenuto in *list.
         */
        *list = new;
    }
    else {
        /* Se la lista non è vuota dobbiamo arrivare fino in fondo
         * e poi aggiungere il nuovo elemento.
         */
        list_elem_t* curr = *list;
        /* Usiamo current per scorrere la lista, che è un puntatore ausiliario.
         * Altrimenti se avessimo usato *lista avremmo "perso" la testa
         * della lista (e quindi tutta la lista) in maniera irrecuperabile.
         */
        while(curr->next != NULL) {
            /* Ci fermiamo a current->next == NULL, cioè sull'ultimo elemento
             * non-NULL della lista, in modo da attaccarci il nuovo.
             */
            curr = curr->next;
        }
        /* Aggiunta del nuovo elemento in fondo */
        curr->next = new;
    }
}

/* Stampa la lista passata come parametro */
void print_list(list_elem_t* list) {
    list_elem_t* curr = list;
    while(curr != NULL) {
        printf("%i ", curr->val);
        curr = curr->next;
    }
}

int main(void) {
    int i;
    int n;
    
    scanf("%i", &n);
    
    /* È importante inizializzare a NULL, alcuni Sistemi Operativi
     * potrebbero dare errori in fase di inserimento
     */
    list_elem_t* lista = NULL;
    
    /* Inserimento dei valori nella lista */
    for(i=0;i<n;i++) {
        int tmp;
        scanf("%i", &tmp);
        inserisci_in_coda(&lista, tmp);
    }
    
    /* Calcola e stampa la media */
    int media = mean(lista, n);
    printf("%i\n", media);
    
    /* Stampa la lista intera */
    print_list(lista);
    printf("\n");
    
    /* Cancella gli elementi <= media */
    cancellazione(&lista, media);
    
    /* Stampa la nuova lista */
    print_list(lista);
    
    /* Deallocazione della memoria */
    while(lista != NULL) {
        list_elem_t* tmp = lista;
        lista = lista->next;
        free(tmp);
    }
    
    return 0;
}
