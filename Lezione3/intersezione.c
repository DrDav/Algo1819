#include <stdio.h>
#include <stdlib.h>

/* Cambiare questa define per scegliere quale algoritmo chiamare */
#define INTERSEZIONE(a, dim_a, b, dim_b) intersezione_binsearch(a, dim_a, b, dim_b)

/* Indichiamo con n la dimensione dell'array A (il primo array)
 * e con m la dimensione di B (secondo array).
 * Assumiamo quindi che n ed m siano diversi.
 * La complessità comunque non cambia nel caso che n = m.
 */


/*
 * Tempo: O(n * m)
 * Spazio: O(1)
 * Strategia: cercare uno alla volta gli elementi di a all'interno di b.
 */
int intersezione_quad(int a[], int dim_a, int b[], int dim_b) {
    int i, j;
    int trovato = 0;
    int intersez = 0;

    for(i=0;i<dim_a;i++) {
        j = 0;
        trovato = 0;
        while(!trovato && j < dim_b) {
            if(a[i] == b[j]) {
                trovato = 1;
            }
            j++;
        }

        if(trovato) {
            intersez++;
        }
    }

    return intersez;
}

/* Procedura aggiuntiva necessaria per il sorting, vedere sotto */
int cmp(const void *a, const void *b) {
    return (*(const int*)a) - (*(const int*)b);
}

/*
 * Tempo O(n log n + m log m)
 * Spazio: O(1) perché modifichiamo direttamente l'input.
 *         Sarebbe più corretto farne una copia e ordinare le copie
 *         usando O(n + m) spazio.
 * Strategia: ordinare i due array, quindi cercare l'intersezione
 * scorrendo entrambi (in stile procedura Merge).
 */
int intersezione_merge(int a[], int dim_a, int b[], int dim_b) {
    int i, j;
    int intersez = 0;

    /* Ordinamento dei due array */
    qsort(a, dim_a, sizeof(int), cmp); // O(n logn)
    qsort(b, dim_b, sizeof(int), cmp); // O(m logm)

    /* Ricerca degli elementi nell'intersezione (come Merge) */
    i = 0;
    j = 0;
    while(i < dim_a && j < dim_b) {
        if(a[i] == b[j]) {
            /* Abbiamo trovato un elemento dell'intersezione,
             * quindi possiamo avanzare in entrambi gli array
             */
            intersez++;
            i++;
            j++;
        }
        else if(a[i] < b[j]) {
            /* In questo caso dobbiamo avanzare solo nel primo array */
            i++;
        }
        else { 
            j++; // Altrimenti avanziamo nel secondo.
        }
    }

    return intersez;
}

/* Ricerca Binaria su array di interi, in O(log n) tempo.
 * Serve per la funzione successiva.
 */
int binary_search(int a[], int elem, int sx, int dx) {
    if(sx > dx) { // Caso base: array vuoto.
        return -1;
    }

    /* Divide (questo include anche il caso base dell'array di un solo elemento. */
    int cx = (sx + dx) / 2; // Parte intera inferiore

    if(a[cx] == elem)
        return cx;

    /* Impera */
    if(a[cx] > elem)
        return binary_search(a, elem, sx, cx - 1); // Vado a sinistra

    return binary_search(a, elem, cx + 1, dx); // Vado a destra
}

/* Tempo: O( min{ (m + n) * log m, (m + n) * log n} )
 * Spazio: O(1), come sopra sarebbe più corretto ordinare uno dei due array,
 *               usando O(min{n, m}) spazio.
 * Strategia: Ordinare solo l'array più corto, quindi eseguire una scansione
 * del più lungo, cercando ogni elemento nel più corto con una ricerca binaria.
 */
int intersezione_binsearch(int a[], int dim_a, int b[], int dim_b) {
    /* Usiamo due alias per non dover scrivere due volte lo stesso codice */
    int *array_corto;
    int *array_lungo;
    int dim_corto;
    int dim_lungo;

    int i;
    int intersez = 0;

    if(dim_a < dim_b) {
        array_corto = a;
        dim_corto = dim_a;
        array_lungo = b;
        dim_lungo = dim_b;
    }
    else {
        array_corto = b;
        dim_corto = dim_b;
        array_lungo = a;
        dim_lungo = dim_a;
    }

    /* Ordiniamo l'array più corto */
    qsort(array_corto, dim_corto, sizeof(int), cmp);

    /* Iteriamo sull'array lungo, cercando in quello corto */
    for(i=0;i<dim_lungo;i++) {
        if(binary_search(array_corto, array_lungo[i], 0, dim_corto) != -1) {
            intersez++;
        }
    }

    return intersez;
}

int main(void) {
    int dim_a, dim_b;
    int *a;
    int *b;
    int i;

    /* Allocazione e riempimento del primo array */
    scanf("%i", &dim_a);
    a = malloc(dim_a * sizeof(int));

    for(i=0;i<dim_a;i++) {
        scanf("%i", &a[i]);
    }

    /* Secondo array */
    scanf("%i", &dim_b);
    b = malloc(dim_b * sizeof(int));

    for(i=0;i<dim_b;i++) {
        scanf("%i", &b[i]);
    }

    printf("%i\n", INTERSEZIONE(a, dim_a, b, dim_b));

    /* Free dello spazio occupato dall'input */
    free(a);
    free(b);

    return 0;
}

