#include <stdio.h>
#include <stdlib.h>

/* Counting Sort come visto a lezione.
 * Tempo: Θ(n + k)
 * Spazio: Θ(n + k)
 * NB: Se k = O(n), il tempo è lineare Θ(n)!
 */
int* counting_sort(int*a, int dim, int k) {
    int* c = calloc(k+1, sizeof(int)); // Come la malloc ma azzera la memoria
    int* b = malloc(dim * sizeof(int)); // Sarà l'array ordinato
    int i;

    /* Conteggio degli elementi */
    for(i=0;i<dim;i++)
        c[a[i]]++;

    /* c[i] = numero di elementi (in a) <= i */
    for(i=1;i<=k;i++)
        c[i] = c[i-1] + c[i];

    /* c[a[i]]-1 è la posizione finale di a[i] nell'ordinamento */
    for(i=dim-1;i>=0;i--) {
        b[c[a[i]]-1] = a[i]; // Questo -1 serve perché gli array partono da 0
        c[a[i]]--;
    }

    /* Deallochiamo la memoria utilizzata per l'array ausiliario */
    free(c);

    return b;

}

int main(void) {
    int *array;
    int max = -1; // Supponiamo di ordinare interi positivi
    int n;
    int i;

    printf("Quanti elementi nell'array? ");
    scanf("%i", &n);

    /* Creazione dell'array */
    array = malloc(n * sizeof(int));

    /* Aggiunta degli elementi nell'array e memorizzazione del massimo */
    for(i=0;i<n;i++) {
        scanf("%i", &array[i]);
        if(array[i] > max)
            max = array[i];
    }

    /* Ordinamento dell'array (passiamo la dimensione) */
    int* array_ordinato = counting_sort(array, n, max);

    printf("Array Ordinato:\n");

    for(i=0;i<n;i++) {
        printf("%i\n", array_ordinato[i]);
    }

    /* Deallocazione della memoria occupata dall'array di input */
    free(array);
    /* E dall'array ordinato restituito dalla funzione */
    free(array_ordinato);

    return 0;
}


