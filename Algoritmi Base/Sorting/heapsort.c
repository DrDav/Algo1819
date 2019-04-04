#include <stdio.h>
#include <stdlib.h>

/* Queste semplici funzioni possono essere definite come macro */
#define LEFT(i) (2*i + 1)
#define RIGHT(i) (2*i + 2)
/* +1 e +2 necessari perché gli array partono da 0 */

/* Ripristina la proprietà di (max-)heap, violata nel nodo i.
 * Tempo: O(log n)
 * Spazio: O(log n) per gestire la ricorsione.
 */
void max_heapify(int* a, int i, int heapsize) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int max = i;

    if(l < heapsize && a[l] > a[max])
        max = l;
    if(r < heapsize && a[r] > a[max])
        max = r;
    
    if(max != i) {
        /* Scambiamo a[i] con a[max] */
        int temp = a[i];
        a[i] = a[max];
        a[max] = temp;

        /* Dopo lo scambio violiamo la proprietà di heap nel nodo max,
         * per cui proseguiamo nell'albero con questo nodo.
         */
        max_heapify(a, max, heapsize);
    }
}

/* Costruisce un heap di massimo nell'array a.
 * Restituisce la dimensione dell'heap (heapsize).
 * Tempo: O(n)
 * Spazio: O(log n) per la ricorsione di heapify.
 */
void build_max_heap(int* a, int n) {
    int i;

    int heapsize = n;
    for(i=n/2 - 1;i>=0;i--) { // -1 perché gli array partono da 0
        max_heapify(a, i, heapsize);
    }
}

void heap_sort(int* a, int n) {
    int i;
    int heapsize = n;

    build_max_heap(a, n);

    for(i=n-1;i>=1;i--) { // Partiamo dal fondo fino al secondo elemento
        /* Scambiamo a[0] con a[i]
         * In questo modo la proprietà di heap è violata nella radice (a[0])
         */
        int temp = a[i];
        a[i] = a[0];
        a[0] = temp;

        heapsize--;
        max_heapify(a, 0, heapsize); // ripristiniamo la prop. di heap in a[0]
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

    /* Ordinamento dell'array (passiamo la dimensione) */
    heap_sort(array, n);

    printf("Array Ordinato:\n");

    for(i=0;i<n;i++) {
        printf("%i\n", array[i]);
    }

    /* Deallocazione della memoria occupata dall'array */
    free(array);

    return 0;
}
