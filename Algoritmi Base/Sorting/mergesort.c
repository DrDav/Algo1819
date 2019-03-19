#include <stdio.h>
#include <stdlib.h>
#include <limits.h> /* Per le sentinelle di Merge */

/* Cambiare questa define per scegliere quale delle due versioni di merge usare */
#define MERGE(a, sx, cx, dx) merge_senza_sentinelle(a, sx, cx, dx)

/* Versione di merge con sentinelle, vista a lezione.
 * Tempo: Θ(n)
 * Spazio: Θ(n)
 */
void merge(int *a, int sx, int cx, int dx) {
    int n1 = cx - sx + 1; // Con +1, perché l'estremo cx è incluso [sx, cx]
    int n2 = dx - cx; // Senza +1, perché l'estremo cx è escluso (cx, dx]

    int* l = malloc((n1 + 1) * sizeof(int)); // +1 richiesto per la sentinella
    int* r = malloc((n2 + 1) * sizeof(int));

    int i, j, k;

    /* Riempiamo l ed r con gli elementi provenienti da (porzioni di) a */
    for(i=0;i<n1;i++) {
        l[i] = a[sx + i];
    }

    for(j=0;j<n2;j++) {
        r[j] = a[cx + j + 1];
    }
    
    /* Aggiunta delle sentinelle */
    l[n1] = INT_MAX; // Come +∞ utilizziamo il valore massimo rappresentabile con int
    r[n2] = INT_MAX;

    i = 0;
    j = 0;

    /* Fusione dei due array l ed r all'interno di a.
     * dx è incluso nel ciclo perché è un estremo dell'array
     * e non la sua dimensione!
     */
    for(k=sx;k<=dx;k++) {
        if(l[i] <= r[j]) { /* Copiamo dal primo array e avanziamo solo nel primo */
            a[k] = l[i];
            i++;
        }
        else { /* Copiamo dal secondo array e avanziamo solo nel secondo */
            a[k] = r[j];
            j++;
        }
    }

    /* Avendo le sentinelle in l ed r non abbiamo bisogno di 
     * ulteriori while per esaurire gli array
     */

    /* Deallocazione degli array di supporto utilizzati */
    free(l);
    free(r);

    /* Il risultato è già in a */
}

/* Versione senza sentinelle, stessa complessità in tempo e spazio. */
void merge_senza_sentinelle(int* a, int sx, int cx, int dx) {
    int n1 = cx - sx + 1; // Con +1, perché l'estremo cx è incluso [sx, cx]
    int n2 = dx - cx; // Senza +1, perché l'estremo cx è escluso (cx, dx]

    int* l = malloc(n1 * sizeof(int)); // Nessuno spazio per le sentinelle
    int* r = malloc(n2 * sizeof(int));

    int i, j, k;

    /* Riempiamo l ed r con gli elementi provenienti da (porzioni di) a */
    for(i=0;i<n1;i++) {
        l[i] = a[sx + i];
    }

    for(j=0;j<n2;j++) {
        r[j] = a[cx + j + 1];
    }

    i = 0;
    j = 0;

    /* Fusione senza sentinelle */
    k = sx;

    while(i < n1 && j < n2) {
        if(l[i] <= r[j]) {
            a[k] = l[i];
            i++; // Avanzo nel primo array
        }
        else {
            a[k] = r[j];
            j++; // Avanzo nel secondo array
        }
        k++; // Avanzo in a
    }

    /* Solo uno dei seguenti while verrà eseguito,
     * e copierà il resto di un array in fondo alla parte di a considerata.
     * Questo perché almeno uno dei due array si esaurirà col primo ciclo.
     * Questi due while sono richiesti per via dell'assenza delle sentinelle.
     */
    while(i < n1) {
        a[k] = l[i];
        k++;
        i++;
    }

    while(j < n2) {
        a[k] = r[j];
        k++;
        j++;
    }

    free(l);
    free(r);
}


/* Merge Sort
 * Tempo: Θ(nlogn)
 * Spazio: Θ(n)
 */
void merge_sort(int *a, int sx, int dx) { // Estremi inclusi
    if(sx < dx) { // Caso base della ricorsione incluso in questo if
        /* Divide */
        int cx = (sx + dx) / 2;
        /* Impera */
        merge_sort(a, sx, cx); // Ordiniamo la parte sinistra
        merge_sort(a, cx + 1, dx); // Ordiniamo la parte destra
        /* Ricombina */
        MERGE(a, sx, cx, dx); // Uniamo le due parti ordinate
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
    merge_sort(array, 0, n-1);

    printf("Array Ordinato:\n");

    for(i=0;i<n;i++) {
        printf("%i\n", array[i]);
    }

    /* Deallocazione della memoria occupata dall'array */
    free(array);

    return 0;
}
