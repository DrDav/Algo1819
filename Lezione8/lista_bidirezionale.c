#include <stdio.h>
#include <stdlib.h>

/*
 * Per comprendere al meglio l'implementazione di questo esercizio
 * si consiglia di leggere prima il file lista_monodirezionale.c
 * che contiene molti commenti utili alla comprensione di questo codice.
 */

/* Elemento di una lista doppiamente linkata:
 * Contiene l'informazione, un puntatore all'elemento successivo
 * e un puntatore all'elemento precedente della lista.
 */
typedef struct _elemento_di_lista {
    int valore; // Informazione
    struct _elemento_di_lista* next; // Puntatore al prossimo elemento
    struct _elemento_di_lista* prev; // Puntatore all'elemento precedente
} list_elem_t;

/*
 * Inserimento in coda in una lista doppiamente linkata.
 * In questo caso basta ricevere il puntatore alla coda
 * e collegarci il nuovo elemento, sistemando anche il puntatore al predecessore.
 *
 * Come procedimento è simile ad un inserimento in testa in una lista monodirezionale.
 *
 * La coda della lista deve essere passata con la & dal main, perché questa
 * potrebbe cambiare (in particolare cambia se la lista è vuota)
 */
void inserisci_in_coda(list_elem_t** coda, int elemento) {
    /* Creazione del nuovo elemento */
    list_elem_t* new = malloc(sizeof(list_elem_t));
    new->valore = elemento;
    new->next = NULL; // Il nuovo elemento non ha un successore
    new->prev = *coda; // L'elemento precedente al nuovo è la vecchia coda
    
    *coda = new;
}

int main(void) {
    int i;
    int n;
    
    scanf("%i", &n);
    
    /* Per questo esercizio basta tenere un puntatore alla coda della lista */
    list_elem_t* coda_della_lista = NULL;
    
    for(i=0;i<n;i++) {
        int val;
        scanf("%i", &val);
        /* Inserimento dell'elemento in coda alla lista */
        inserisci_in_coda(&coda_della_lista, val);
    }
    
    /* Stampa la lista al contrario e al contempo dealloca la memoria */
    while(coda_della_lista != NULL) {
        /* Salva l'elemento in coda alla lista */
        list_elem_t* tmp = coda_della_lista;
        /* Stampa l'elemento in coda */
        printf("%i\n", coda_della_lista->valore);
        /* Indietreggia nella lista */
        coda_della_lista = coda_della_lista->prev;
        /* Dealloca l'elemento salvato */
        free(tmp);
    }
    
    return 0;
}
