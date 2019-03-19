#include <stdio.h>
#include <stdlib.h>

/* Insertion Sort come visto a lezione.
 * Tempo: O(n^2)
 *        Si noti che se l'array è già ordinato (caso ottimo), il tempo scende a Θ(n).
 * Spazio: O(1)
 */
void insertion_sort(int* a, int dim) {
    int j, i;

    for(j=1;j<dim;j++) { // Si parte dal secondo elemento dell'array
        int key = a[j];
        i = j-1;
        /* Spostiamo "indietro" l'elemento a[j] in modo che alla sua destra
         * ci siano solo elementi maggiori di lui.
         */
        while(i >= 0 && a[i] > key) {
            a[i+1] = a[i];
            i--;
        }

        a[i+1] = key; // Nuova posizione di a[j] (cioè key)
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
    insertion_sort(array, n);

    printf("Array Ordinato:\n");

    for(i=0;i<n;i++) {
        printf("%i\n", array[i]);
    }

    /* Deallocazione della memoria occupata dall'array */
    free(array);

    return 0;
}

