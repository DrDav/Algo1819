#include <stdio.h>
#include <stdlib.h>

#define BASE 10 /* Base in cui sono rappresentati i numeri da ordinare */

/*
 * Counting Sort adattato per ordinare sulle cifre.
 */
int* counting_sort_cifre(int* a, int dim, int cifra) {
    /* Conosciamo già a priori il valore massimo degli elementi,
     * perché stiamo ordinando delle cifre
     */
    int c[BASE] = {0}; // Già inizializzato a zero  
    int* b = malloc(dim * sizeof(int)); // Sarà l'array ordinato
    int i;

    /* Conteggio degli elementi */
    for(i=0;i<dim;i++)
        /* La cifra effettiva è ottenuta tramite l'operazione di modulo BASE
         * dopo aver diviso per la potenza giusta della base
         */
        c[a[i] / cifra % BASE]++; 

    /* c[i] = numero di elementi (in a) <= i (in questo caso in base alla cifra)
     * Questa operazione è uguale al counting sort classico,
     * ma si ferma a BASE perché ordina sulle cifre
     * */
    for(i=1;i<BASE;i++)
        c[i] = c[i-1] + c[i];

    /* c[a[i]]-1 è la posizione finale di a[i] nell'ordinamento */
    for(i=dim-1;i>=0;i--) {
        b[c[a[i] / cifra % BASE] - 1] = a[i]; // -1 perché gli array partono da 0
        c[a[i] / cifra % BASE]--; // Decrementa come Counting Sort classico
    }

    return b;
}

/* LSD (Least Significant Digit) Radix Sort:
 * Ordina gli interi in base alle cifre che li compongono, 
 * dalla meno alla più significativa.
 * L'algoritmo che usa al suo interno deve essere stabile.
 *
 * Tempo: O(dn + dt) con d = #cifre, t = valore della massima cifra
 *        In base 10 => t = 10 = O(n) (dobbiamo ordinare almeno 10 numeri)
 *        Se il numero di cifre è costante questo algoritmo richiede tempo Θ(n).
 *        Altrimenti richiede tempo Θ(nd).
 * Spazio: O(n) dovutoeall'utilizzo di Counting Sort.
 */
void radix_sort(int* a, int dim) {
    /* Ricerca del massimo nell'array:
     * Serve per conoscere il numero massimo di cifre
     * degli elementi di a
     */
    int i;

    int max = a[0];
    for(i=0;i<dim;i++) {
        if(a[i] > max)
            max = a[i];
    }

    /* Potenza della base utilizzata per scegliere la cifra su cui ordinare */
    int cifra = 1;
    while(max / cifra > 0) {

        int* semi_sorted = counting_sort_cifre(a, dim, cifra);

        /* Aggiornamento dell'array col sorting parziale ottenuto */
        for(i=0;i<dim;i++)
            a[i] = semi_sorted[i];

        free(semi_sorted); // Allocato da counting sort

        cifra *= BASE; // Avanzamento alla cifra più significativa
    }
}

int main(void) {
    int *array;
    int n;
    int i;

    printf("Quanti elementi nell'array? ");
    scanf("%i", &n);

    /* Creazione dell'array */
    array = malloc(n * sizeof(int));

    /* Aggiunta degli elementi nell'array */
    for(i=0;i<n;i++) {
        scanf("%i", &array[i]);
    }

    /* Radix Sort */
    radix_sort(array, n);

    printf("Array Ordinato:\n");

    for(i=0;i<n;i++) {
        printf("%i\n", array[i]);
    }

    /* Deallocazione della memoria occupata dall'array */
    free(array);

    return 0;
}

