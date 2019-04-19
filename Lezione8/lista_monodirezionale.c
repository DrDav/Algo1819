#include <stdio.h>
#include <stdlib.h>

/*
 * Questo esercizio può essere risolto in (almeno) due modi:
 * 1) Inserire gli elementi in coda alla lista e poi stampare la lista
 *    utilizzando una procedura ricorsiva;
 * 2) Inserire gli elementi in testa in modo da avere la lista già
 *    al contrario e poi stamparla in maniera classica.
 *    Questa seconda opzione è possibile perché nel testo dell'esercizio
 *    non viene detto niente sul modo in cui inserire gli elementi in lista.
 */

/* Elemento di lista:
 * Contiene l'informazione e un puntatore all'elemento successivo della lista
 */
typedef struct _elemento_di_lista {
    int valore; // Informazione
    struct _elemento_di_lista* next; // Puntatore al prossimo elemento
} list_elem_t;

/* Reminder:
 * list_elem_t è il tipo di un elemento della lista;
 * list_elem_t* è un puntatore ad un elemento di lista, e quindi è una lista;
 * list_elem_t** è l'indirizzo del puntatore alla testa della lista (!)
 *               e va usato nelle funzioni che potrebbero modificarne la testa.
 */

/*
 * (Versione 1) Procedura ricorsiva che stampa la lista al contrario.
 * Funziona perché prima ricorre fino ad arrivare in fondo alla lista,
 * e solo dopo inizia a stampare gli elementi.
 * Se invertissimo l'ordine della ricorsione e della printf()
 * la lista verrebbe stampata normalmente, non al contrario.
 *
 * Tempo: O(n)
 * Spazio: O(n) (implicitamente dovuto alla ricorsione)
 *
 * ATTENZIONE! Per via della ricorsione, all'atto pratico, questa procedura
 * può essere più lenta.
 */
void stampa_ricorsiva(list_elem_t* lista) {
    if(lista != NULL) {
        stampa_ricorsiva(lista->next);
        printf("%i\n", lista->valore);
    }
}

/*
 * (Versione 1) Procedura che inserisce in coda l'elemento passato
 * come secondo parametro.
 * Si noti che la lista è un doppio puntatore e non puntatore singolo.
 * Questo perché quando la lista è vuota dobbiamo modificarne la testa,
 * e questo è possibile solamente avendo in mano il "vero" puntatore alla lista
 * (nel main bisogna quindi passare la lista usando la &)
 */
void inserisci_in_coda(list_elem_t** lista, int elemento) {
    /* Creazione del nuovo elemento da aggiungere alla lista */
    list_elem_t* new = malloc(sizeof(list_elem_t));
    new->valore = elemento;
    new->next = NULL; // Perché sarà sempre l'ultimo elemento della lista
    
    if(*lista == NULL) {
        /* Se la lista è vuota bisogna inserire in testa, modificando quindi
         * il puntatore alla testa, contenuto in *lista.
         */
        *lista = new;
    }
    else {
        /* Se la lista non è vuota dobbiamo arrivare fino in fondo
         * e poi aggiungere il nuovo elemento.
         */
        list_elem_t* current = *lista;
        /* Usiamo current per scorrere la lista, che è un puntatore ausiliario.
         * Altrimenti se avessimo usato *lista avremmo "perso" la testa
         * della lista (e quindi tutta la lista) in maniera irrecuperabile.
         */
        while(current->next != NULL) {
            /* Ci fermiamo a current->next == NULL, cioè sull'ultimo elemento
             * non-NULL della lista, in modo da attaccarci dietro il nuovo.
             */
            current = current->next;
        }
        /* Aggiunta del nuovo elemento in fondo */
        current->next = new;
    }
}

/*
 * (Versione 2) Procedura che inserisce in testa il nuovo elemento.
 * Come sopra, la lista deve essere passata con un * in più,
 * perché vogliamo modificarne la testa.
 */
void inserisci_in_testa(list_elem_t** lista, int elemento) {
    /* Creazione del nuovo elemento di lista */
    list_elem_t* new = malloc(sizeof(list_elem_t));
    new->valore = elemento;
    /* Il nuovo elemento dovrà puntare alla vecchia testa, che in questo momento
     * si trova in *lista.
     */
    new->next = *lista;
    
    /* Inserimento del nuovo elemento (modifica della testa) */
    *lista = new;
}

int main(void) {
    int i;
    int n;
    
    scanf("%i", &n);
    
    list_elem_t* lista = NULL; // Inizialmente la lista è vuota
    
    for(i=0;i<n;i++) {
        int val;
        scanf("%i", &val);
        
        /* Scegliere quale delle due versioni utilizzare */
        
        /* Versione 1 */
        //inserisci_in_coda(&lista, val);
        
        /* Versione 2 */
        inserisci_in_testa(&lista, val);
    }
    
    /* Scegliere quale delle due versioni utilizzare */
    
    /* Versione 1 */
    //stampa_ricorsiva(lista);
    
    /* Versione 2 */
    
    list_elem_t* current = lista;
    while(current != NULL) {
        printf("%i\n", current->valore);
        current = current->next;
    }
    
    
    
    /* Deallocazione della lista */
    list_elem_t* tmp = NULL;
    while(lista != NULL) {
        tmp = lista; // Salviamo il blocco corrente
        lista = lista->next; // Avanziamo nella lista
        free(tmp); // Liberiamo il blocco precedentemente salvato
    }
    
    return 0;
}
