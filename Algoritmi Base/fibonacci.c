#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Ci sono le funzioni per calcolare il tempo speso in ms

// Successione di fibonacci

// Fibonacci all'interno del suo codice ha una chiamata a se stessa
// con input ridotto.

// Calcolare l'n-esimo numero di fibonacci
int fibonacci(int n) {

    // Controllo che l'input sia positivo
    if(n < 0) return -1;

    // Casi base
    if(n == 0) return 0;
    if(n == 1) return 1;

    // Chiamate ricorsive +  calcolo intermedio (il "+")
    return fibonacci(n-1) + fibonacci(n-2);

    // Si poteva scrivere come

        // Chiamata ricorsiva
    // int f1 = fibonacci(n-1);
    // int f2 = fibonacci(n-2);

        // Calcolo
    // int f = f1 + f2;

    // return f;
}


// Successione di Fibonacci

// Tecnica con memoization

// Costruzione dell'array delle soluzioni parziali, approccio "dal basso", anziché dall'alto
// scendendo a dividere
int memoization_fibonacci(int n) {

    // Controllo che l'input sia positivo
    if(n < 0) return -1;

    // Casi base
    if(n == 0) return 0;
    if(n == 1) return 1;

    // Array 
    int* fibArray = (int*) malloc(sizeof(int) * (n+1));

    fibArray[0] = 0;
    fibArray[1] = 1;

    for(int i=2; i<=n; i++) {
        fibArray[i] = fibArray[i-1] + fibArray[i-2];
    }

    int risultato = fibArray[n];
    free(fibArray);

    return risultato;
}

int main(void) {

    int n = 0;
    
    // Variabili per calcolare il tempo speso
    clock_t start, end;
    double time_fibonacci, time_mem_fibonacci;

    // Input da terminale    
    printf("Inserisci il valore n per fibonacci\n");
    scanf("%d", &n);

    // Calcola fibonacci
    start = clock();
    printf("fibonacci(%d) = %d.\n", n, fibonacci(n));
    end = clock();
    time_fibonacci = ((double) (end - start)) / CLOCKS_PER_SEC;


    // Calcola fibonacci con memoization
    start = clock();
    printf("memoization_fibonacci(%d) = %d.\n", n, memoization_fibonacci(n));
    end = clock();
    time_mem_fibonacci = ((double) (end - start)) / CLOCKS_PER_SEC;


    // Stampa i tempi impiegati
    printf("fibonacci(%d) ha impiegato %f secondi.\n", n, time_fibonacci);
    printf("memoization_fibonacci(%d) ha impiegato %f secondi.\n", n, time_mem_fibonacci);

    return 0;
}