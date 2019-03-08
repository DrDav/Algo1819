#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 10;
    int i;
    int *array = malloc(n * sizeof(int)); /* Creo un array di n elementi */

    /* Primi due numeri di Fibonacci */
    array[0] = 1;
    array[1] = 1;

    printf("#0: %i\n#1: %i\n", array[0], array[1]); 
    
    /* Numeri di fibonacci */
    for(i=2;i<=n;i++) {
        array[i] = array[i-1] + array[i-2];
        printf("#%i: %i\n", i, array[i]);
    }

    free(array);

    return 0;
}

