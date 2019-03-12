#include <stdio.h>
#include <stdlib.h>

int* merge(int a[], int dim_a, int b[], int dim_b) {
    int *fusione = malloc((dim_a + dim_b) * sizeof(int));
    int i = 0, j = 0, k = 0;

    /* Poiché a e b sono già ordinati, basta scorrerli insieme
     * e copiare ogni volta l'elemento più piccolo tra i due,
     * quindi avanzare di un passo nel nuovo array e nell'array da cui abbiamo copiato
     */
    while(i < dim_a && j < dim_b) {
        if(a[i] <= b[j]) {
            fusione[k] = a[i];
            i++; // Avanzo nel primo array
        }
        else {
            fusione[k] = b[j];
            j++; // Avanzo nel secondo array
        }
        k++; // Avanzo nel nuovo array
    }

    /* Solo uno dei seguenti while verrà eseguito,
     * e copierà il resto di un array in fondo al nuovo array creato.
     * Questo perché almeno uno dei due array si esaurirà col primo ciclo.
     */
    while(i < dim_a) {
        fusione[k] = a[i];
        k++;
        i++;
    }

    while(j < dim_b) {
        fusione[k] = b[j];
        k++;
        j++;
    }

    return fusione;
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

    int *fusione = merge(a, dim_a, b, dim_b);

    for(i=0;i<dim_a+dim_b;i++) {
        printf("%i\n",fusione[i]);
    }

    free(fusione); // Free della memoria allocata all'interno della funzione
    free(a); // Free dei due array di input
    free(b);

    return 0;
}
