#include <stdio.h>

#define N 3

void tswap(int *x, int *y, int *z) {
    int temp = *x;
    *x = *z;
    *z = *y;
    *y = temp;
}

int main(void) {
    int numeri[N];
    int i;

    for(i=0;i<N;i++) {
        scanf("%i",numeri+i);
    }

    // Invocazione classica
    tswap(&numeri[0], &numeri[1], &numeri[2]);

    /* Alternativa con i puntatori
    tswap(numeri, numeri+1, numeri+2);
    */

    for(i=0;i<N;i++) {
        printf("%i\n", numeri[i]);
    }

    return 0;
}
