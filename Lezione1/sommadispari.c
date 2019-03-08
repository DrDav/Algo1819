#include <stdio.h>

int somma_dispari(int n) {
    /* Caso Base */
    if(n == 1) {
        return 1;
    }

    /* L'n-esimo numero dispari è 2n - 1,
     * ad esempio il secondo numero dispari è 3 = 2*2 - 1.
     * Lo accumuliamo sfruttando le chiamate ricorsive.
     */
    return (2 * n - 1) + somma_dispari(n-1); // Caso ricorsivo
}

int main(void) {
    int n;

    scanf("%i", &n);
    printf("%i", somma_dispari(n));

    return 0;
}
