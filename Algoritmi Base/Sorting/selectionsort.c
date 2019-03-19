#include <stdio.h>
#include <stdlib.h>

/* Selection Sort come visto a lezione.
 * Tempo: O(n^2)
 * Spazio: O(1)
 */
void selection_sort(int* a, int dim) {
    int i, j;

    for(i=0;i<dim-1;i++) { // L'ultimo elemento sarà già al posto giusto
        int pos_minimo = i;
        
        /* Cerchiamo il minimo dell'array e lo portiamo
         * alla fine della porzione di array già ordinata
         * (inizialmente vuota)
         */
        for(j=i+1;j<dim;j++) {
            if(a[j] < a[pos_minimo]) {
                pos_minimo = j;
            }
        }
        
        /* Scambiamo a[i] con a[pos_minimo] */
        int temp = a[i];
        a[i] = a[pos_minimo];
        a[pos_minimo] = temp;
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
    selection_sort(array, n);

    printf("Array Ordinato:\n");

    for(i=0;i<n;i++) {
        printf("%i\n", array[i]);
    }

    /* Deallocazione della memoria occupata dall'array */
    free(array);

    return 0;
}

