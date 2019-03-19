#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Partition
 * Tempo: O(dx - sx) = O(n)
 * Spazio: O(1)
 */
int partition(int* a, int sx, int dx, int pos_pivot) {
    int i, j;

    int pivot = a[pos_pivot];
    /* Spostiamo il pivot in fondo alla porzione di array considerata */
    a[pos_pivot] = a[dx];
    a[dx] = pivot;

    i = sx - 1;
    for(j=sx;j<dx;j++) { // dx è escluso dal ciclo, perché contiene il pivot
        if(a[j] <= pivot) {
            i++;
            /* Scambiamo a[i] con a[j] */
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    /* Scambiamo a[i+1] con a[dx], cioè spostiamo il pivot al posto "giusto"
     * nell'array, e ne restituiamo la sua nuova posizione, cioè i+1
     */
    int temp = a[i+1];
    a[i+1] = a[dx];
    a[dx] = temp;

    return i+1;
}

/* QuickSort (classico)
 * Tempo: O(n^2) al caso pessimo, O(nlogn) al caso medio.
 * Spazio: O(log n) dovuto implicitamente alla ricorsione.
 */
void quicksort(int* a, int sx, int dx) {
    if(sx < dx) { // Caso base della ricorsione incluso in questo if
        /* Divide */
        int rnd = rand() % (dx - sx + 1) + sx; // Numero casuale tra sx e dx
        int pivot = partition(a, sx, dx, rnd); // Randomized Quicksort
        /* Commentare le due righe sopra e decommentare questa per usare 
         * Quicksort NON randomizzato (scegliendo come pivot l'ultimo elemento)
         */
        //int pivot = partition(a, sx, dx, dx);


        /* Impera
         * NB: Il pivot viene escluso perché si trova già al posto giusto!
         */
        quicksort(a, sx, pivot - 1); 
        quicksort(a, pivot + 1, dx);

        /* Nessun procedimento di ricombinazione necessario */
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

    /* Ordinamento dell'array (estremi inclusi!) */
    srand(time(NULL)); // Per la versione randomizzata di QS
    quicksort(array, 0, n-1);

    printf("Array Ordinato:\n");

    for(i=0;i<n;i++) {
        printf("%i\n", array[i]);
    }

    /* Deallocazione della memoria occupata dall'array */
    free(array);

    return 0;
}

